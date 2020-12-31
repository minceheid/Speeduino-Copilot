#include "SdFat.h"
#include "sdios.h"
// Create a Serial output stream.
ArduinoOutStream cout(Serial);
// SD_FAT_TYPE = 0 for SdFat/File as defined in SdFatConfig.h,
// 1 for FAT16/FAT32, 2 for exFAT, 3 for FAT16/FAT32 and exFAT.
#define SD_FAT_TYPE 3
/*
  Change the value of SD_CS_PIN if you are using SPI and
  your hardware does not use the default value, SS.
  Common values are:
  Arduino Ethernet shield: pin 4
  Sparkfun SD shield: pin 8
  Adafruit SD shields and modules: pin 10
*/

// SDCARD_SS_PIN is defined for the built-in SD on some boards.
#ifndef SDCARD_SS_PIN
const uint8_t SD_CS_PIN = SS;
#else  // SDCARD_SS_PIN
// Assume built-in SD is used.
const uint8_t SD_CS_PIN = SDCARD_SS_PIN;
#endif  // SDCARD_SS_PIN

// Try to select the best SD card configuration.
#if HAS_SDIO_CLASS
#define SD_CONFIG SdioConfig(FIFO_SDIO)
#elif ENABLE_DEDICATED_SPI
#define SD_CONFIG SdSpiConfig(SD_CS_PIN, DEDICATED_SPI)
#else  // HAS_SDIO_CLASS
#define SD_CONFIG SdSpiConfig(SD_CS_PIN, SHARED_SPI)
#endif  // HAS_SDIO_CLASS
//------------------------------------------------------------------------------

#if SD_FAT_TYPE == 0
SdFat sd;
File file;
#elif SD_FAT_TYPE == 1
SdFat32 sd;
File32 file;
#elif SD_FAT_TYPE == 2
SdExFat sd;
ExFile file;
#elif SD_FAT_TYPE == 3
SdFs sd;
FsFile file;
#endif  // SD_FAT_TYPE

// Filename pattern and filenumber defines the filename sequence that will be used for 
// creating new files. Old files will be overwritten. This behaviour may change when I 
// get a GPS/RTC facility to experiment with
#define FILENAME_PATTERN "test_%04d.mlg"
int filenumber=0;

// character buffer for storing data pending SD 
//  offset = pointer into the current location in the active (unwritten) buffer
//  fileoffset = the current committed bytes in the file (for debugging purposes)
//  mgvlgRecord = the logical record number within the file

#define BUFFERSIZE 8192
byte buffer[BUFFERSIZE];
unsigned long offset=0;
unsigned long long fileoffset=0;
unsigned long mgvlgRecord=0;

#define MAX_FILE_LENGTH_KB 100

//////////////////////////
// Init - used to set up the environment
void mgvlgInit() {
  Serial.println("MGVLG Init");
  // Initialize the SD card.
  if (!sd.begin(SD_CONFIG)) {
    Serial.println("SD Card Failed to initialise");
    sd.initErrorHalt(&Serial);
  }

  // Open a Logfile
  _openFile(1);
 
  // generate headers and write into the buffer, 
  // then flush the buffer to disk
  _buildHeaders();
  _flushBuffer();
}


//////////////////////////
// File handling functions

void _getFilename(int filenumber,char* filename) {
  sprintf(filename,FILENAME_PATTERN,filenumber);
}

void _openFile(int filenumber) {
  char filename[64];
  _getFilename(filenumber++,filename);
  
  //open file
  Serial.print("Opening: ");
  Serial.println(filename);

  // Create a file using a path.
  if (!file.open(filename, O_WRONLY | O_CREAT)) {
    char errormsg[128];
    sprintf(errormsg,"Create %s failed",filename);
    sd.errorHalt(errormsg);
  }
  mgvlgRecord=0;
  fileoffset=0;
}

void _closeFile() {
  file.close();
  Serial.println("File closed\n");
}

//////////////////////////
// Write values to the buffer, taking care of endian conversion where necessary
// Note that the MGVLG format expects Big Endian, and Teensy uses Little Endian

void _writeU8(int offset,unsigned short value) {
  buffer[offset+0]=value & 0xff; 
}
void _writeU16(int offset,unsigned long value) {
  buffer[offset+0]=value/256 & 0xff;
  buffer[offset+1]=value & 0xff; 
}

void _writeU32(int offset,unsigned long long value) {
  buffer[offset]=value/256/256/256 & 0xff ;
  buffer[offset+1]=value/256/256 & 0xff;
  buffer[offset+2]=value/256 & 0xff;
  buffer[offset+3]=value & 0xff; 
}

void _writeF32(int offset,float value) {
  byte *p;
  p=(byte*)&value;
    
  buffer[offset]=p[3];
  buffer[offset+1]=p[2];
  buffer[offset+2]=p[1];
  buffer[offset+3]=p[0]; 
}

//////////////////////////
// Build MGVLG headers and write them to the buffer
// This is the main reason for having a sizable (wasteful) buffer, as it makes the population of the "data begin" index
// trivial, though admittedly it could be calculated to fully eliminate the buffer. As this is the only thing running
// on the Teensy, this isn't a big issue right now though.
//  http://www.efianalytics.com/TunerStudio/docs/MLG_Binary_LogFormat_1.0.pdf

int _buildHeaders() {
  Serial.println("Building Headers");
  strcpy((char*)buffer,"MLVLG\0");

  // calculate record length
  int recordLength=0;
  for (int i=0;i<MGVLG_SCALAR_COUNT;i++) {
    switch (mgvlg_fields[i].type) {
      case MGVLG_DATATYPE_U08:
      case MGVLG_DATATYPE_S08:
        recordLength++;
        break;
      case MGVLG_DATATYPE_U16:
      case MGVLG_DATATYPE_S16:
        recordLength+=2;
        break;
      case MGVLG_DATATYPE_F32:
        recordLength+=4;
        break;
      default:
        errorHalt("Unknown datatype");
    }
  }
  _writeU16(0x06,0x0001);      // Format Version
  _writeU32(0x08,0x00000000);  // Timestamp
  _writeU16(0x0c,0);           // Info Data Start - this field appears to be too short to store the address, so don't populate
  _writeU32(0x0e,0);           // Data Begin Index
  _writeU16(0x12,recordLength);         // Record Length
  _writeU16(0x14,MGVLG_SCALAR_COUNT);          // Num Logger Fields

  cout << "record length: "<<recordLength << " num fields:" <<MGVLG_SCALAR_COUNT<< "\n";
  offset=0x16;

  for (int i=0;i<MGVLG_SCALAR_COUNT;i++) {
//   Serial.println(mgvlg_fields[i].name);
   _writeU8(offset,mgvlg_fields[i].type);
   strncpy((char*)buffer+offset+1,mgvlg_fields[i].name,34);
   strncpy((char*)buffer+offset+35,mgvlg_fields[i].units,10); 

   _writeU8(offset+45,mgvlg_fields[i].style);
   _writeF32(offset+46,mgvlg_fields[i].scale);
   _writeF32(offset+50,mgvlg_fields[i].transform);
   _writeU8(offset+54,mgvlg_fields[i].digits);
   offset=offset+55;
  }

  // MMS: Bit Fields not yet implemented
  // Info Data - not really required.
  strncpy((char*)buffer+offset,"Speeduino\0",10);
  offset+=10;

  _writeU32(0x0e,offset);           // Data Begin Index

  return(0);
}


//////////////////////////
// Flush the buffer out to SD

int _flushBuffer() {

#ifdef DEBUG
  int j=offset;
  if (j>32) { j=32; }
  for (int i=0; i<j; i++) {
    cout << hex << (int)buffer[i] << ":";  
  }
  cout << "\n";
#endif // DEBUG
  // file.write only commits to the internal sd buffer (512 bytes, I think)
  if (offset!=file.write(buffer,offset)) {
    errorHalt("write failed.\n");
  }
  // Flushing should see that written to SD, but doesn't really need
  // to be done every record, if it causes a problem it could be backed off
  // to once a second perhaps. Though, hopefully the current implmentation
  // also gives it a level of atomicity on the records written to file
  file.flush();
  // reset buffer pointers
  fileoffset+=offset;
  offset=0;

  return(true);
}


//////////////////////////
// writeRecord - the main calling point for writing data from Speeduino into the buffer (and onto the SD)
// This accepts a DataPacket (from the "A" command over speeduino serial line), as defined in speeduino.h
// and uses the mgvlg_fields structure (defined in mgvlg.h) to write all the records from the data packet
// Not all fields are fully implemented yet. Notable exceptions:  SyncLoss, Time - all bit fields (which
// might require a bit of restructuring of the data structures. Need to more fully understand how that is
// being laid out in the MGVLG

void writeRecord(speeduinoDataPacket *d) {

  _writeU8(offset++,0x00);//Block Type - always 0
  _writeU8(offset++,(byte)(mgvlgRecord%256)); // Rolling Counter
  _writeU16(offset,(unsigned long)mgvlgRecord%65536); // Timestamp 10us/bit Note fudge for not having RTC
  offset+=2;
  
  int crc=0;
  // loop around each scalar in order
  for (int i=0; i<MGVLG_SCALAR_COUNT; i++) {
 // for (int i=0; i<2; i++) {

    switch (mgvlg_fields[i].type) {
      case MGVLG_DATATYPE_U08:
      case MGVLG_DATATYPE_S08:
        if (mgvlg_fields[i].offset>=0) {
          char *dd=(char *)d;

          _writeU8(offset,dd[mgvlg_fields[i].offset]);
          crc=(crc+dd[mgvlg_fields[i].offset])%256;
         }
        offset++;
        break;
          
      case MGVLG_DATATYPE_U16:
      case MGVLG_DATATYPE_S16:

        if (mgvlg_fields[i].offset>=0) {
          char *dd=(char *)d;

          _writeU8(offset,dd[mgvlg_fields[i].offset+1]);
          _writeU8(offset+1,dd[mgvlg_fields[i].offset]);

          crc=(crc+dd[mgvlg_fields[i].offset])%256;
          }
        offset+=2;
        
        break;

/* NOT YET IMPLEMENTED 
      case MGVLG_DATATYPE_F32:
        if (mgvlg_fields[i].offset>=0) {
          cout << "#" << mgvlgRecord  <<"\n";

          _writeF32(offset,1); // not implemented yet
          crc=(crc+buffer[offset+3])%256;
          cout << "buffer " << " " << (int)buffer[offset] << ":" << (int)buffer[offset+1] << (int)buffer[offset+2] << ":" << (int)buffer[offset+3] << "\n";

          }
        offset+=4;
        break;
 */

      default:
        errorHalt("Unknown datatype");
    }
  }

  buffer[offset++]=crc ; //CRC 
  // increment our record counter
  mgvlgRecord++;

  // flush the buffer at the end of the record
  _flushBuffer();  

  // if we have gone over the maximum file size limit, then we start a new file
  if (fileoffset>MAX_FILE_LENGTH_KB*1024) {
    filenumber++;
    cout << "NOTE: Reopening new file at fileoffset " << (fileoffset/1024) <<"KB\n";
    _closeFile();
    _openFile(filenumber);
    _buildHeaders();
    _flushBuffer();
  }
}
