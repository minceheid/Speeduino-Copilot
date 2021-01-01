////////////////////////////
// Public functions
void mgvlgInit();
void writeRecord(byte *d);


////////////////////////////
// These are really all private definitions and structures, so perhps oughtn't be
// in the header file. Seems to make sense to keep them separate though.

#define MGVLG_DATATYPE_U08 0x00
#define MGVLG_DATATYPE_S08 0x01
#define MGVLG_DATATYPE_U16 0x02
#define MGVLG_DATATYPE_S16 0x03
#define MGVLG_DATATYPE_F32 0x07

#define MGVLG_STYLE_FLOAT 0x00
extern "C" {
typedef struct {
  unsigned int offset;
  byte type;
  char name[34];
  char units[10];
  byte style;
  union {
    struct {
      float scale;
      float transform;
      byte digits;
    };
    struct {
       byte fieldstyle;
       byte fieldname;
       unsigned int fieldnameindex;
       byte bits;
    };
  };
} mgvlgFieldType;


const int MGVLG_FIELD_COUNT=53;
mgvlgFieldType mgvlg_fields[MGVLG_FIELD_COUNT]= {
//{Offset,Type,Name,Units,Display Style,scale,transform,digits,},
{0,MGVLG_DATATYPE_U08,"SecL", "sec",  MGVLG_STYLE_FLOAT,  1,  0,  0},
{1, MGVLG_DATATYPE_U08, "Status", "bits", MGVLG_STYLE_FLOAT,  1,  0,  0},
{2, MGVLG_DATATYPE_U08, "Engine", "bits", MGVLG_STYLE_FLOAT,  1,  0,  0},
{3, MGVLG_DATATYPE_U08, "Dwell",  "ms", MGVLG_STYLE_FLOAT,  10,  0,  1},
{4, MGVLG_DATATYPE_U16, "MAP",  "kpa",  MGVLG_STYLE_FLOAT,  1,  0,  0},
{6, MGVLG_DATATYPE_U08, "IAT",  "°C", MGVLG_STYLE_FLOAT,  1,  -40,  0},
{7, MGVLG_DATATYPE_U08, "CLT",  "°C", MGVLG_STYLE_FLOAT,  1,  -40,  0},
{8, MGVLG_DATATYPE_U08, "Gbattery", "%",  MGVLG_STYLE_FLOAT,  1,  0,  0},
{9, MGVLG_DATATYPE_U08, "Battery V",  "V",  MGVLG_STYLE_FLOAT,  0.1,  0,  1},
{10,  MGVLG_DATATYPE_U08, "AFR",  "O2", MGVLG_STYLE_FLOAT,  0.1,  0,  3},
{11,  MGVLG_DATATYPE_U08, "Gego", "%",  MGVLG_STYLE_FLOAT,  1,  0,  0},
{12,  MGVLG_DATATYPE_U08, "Gair", "%",  MGVLG_STYLE_FLOAT,  1,  0,  0},
{13,  MGVLG_DATATYPE_U08, "Gwarm",  "%",  MGVLG_STYLE_FLOAT,  1,  0,  0},
{14,  MGVLG_DATATYPE_U16, "RPM",  "rpm",  MGVLG_STYLE_FLOAT,  1,  0,  0},
{16,  MGVLG_DATATYPE_U08, "Accel Enrich", "%",  MGVLG_STYLE_FLOAT,  2,  0,  0},
{17,  MGVLG_DATATYPE_U08, "Gammae", "%",  MGVLG_STYLE_FLOAT,  1,  0,  0},
{18,  MGVLG_DATATYPE_U08, "VE", "%",  MGVLG_STYLE_FLOAT,  1,  0,  0},
{19,  MGVLG_DATATYPE_U08, "AFR Target",  "",  MGVLG_STYLE_FLOAT,  1,  0,  0},
{20,  MGVLG_DATATYPE_U16, "Pulse Width",  "ms",  MGVLG_STYLE_FLOAT,  10,  0,  1},
{22,  MGVLG_DATATYPE_U08, "TPS DOT",  "%/s",  MGVLG_STYLE_FLOAT,  10, 0,  0},
{23,  MGVLG_DATATYPE_S08, "Advance",  "deg",  MGVLG_STYLE_FLOAT,  1,  0,  0},
{24,  MGVLG_DATATYPE_U08, "TPS",  "%",  MGVLG_STYLE_FLOAT,  1,  0,  0},
{25,  MGVLG_DATATYPE_U16, "Loops per second", "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{27,  MGVLG_DATATYPE_U16, "Speeduino Free RAM", "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{29,  MGVLG_DATATYPE_U08, "Boost Target", "kPa",  MGVLG_STYLE_FLOAT,  2,  0,  0},
{30,  MGVLG_DATATYPE_U08, "Boost Duty", "%",  MGVLG_STYLE_FLOAT,  1,  0,  0},
{31,  MGVLG_DATATYPE_U08, "Spark Bits", "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{32,  MGVLG_DATATYPE_S16, "RPM DOT",  "rpm/s",  MGVLG_STYLE_FLOAT,  1,  0,  0},
{34,  MGVLG_DATATYPE_U08, "Ethanol %",  "%",  MGVLG_STYLE_FLOAT,  1,  0,  0},
{35,  MGVLG_DATATYPE_U08, "Flex Fuel Correction", "%",  MGVLG_STYLE_FLOAT,  1,  0,  0},
{36,  MGVLG_DATATYPE_U08, "Flex Ignition Correction", "%",  MGVLG_STYLE_FLOAT,  1,  0,  0},
{37,  MGVLG_DATATYPE_U08, "Idle Load",  "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{38,  MGVLG_DATATYPE_U08, "Test Outputs", "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{39,  MGVLG_DATATYPE_U08, "O2_2", "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{40,  MGVLG_DATATYPE_U08, "Baro Pressure",  "kpa",  MGVLG_STYLE_FLOAT,  1,  0,  0},
{41,  MGVLG_DATATYPE_U16, "Aux0", "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{43,  MGVLG_DATATYPE_U16, "Aux1", "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{45,  MGVLG_DATATYPE_U16, "Aux2", "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{47,  MGVLG_DATATYPE_U16, "Aux3", "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{49,  MGVLG_DATATYPE_U16, "Aux4", "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{51,  MGVLG_DATATYPE_U16, "Aux5", "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{53,  MGVLG_DATATYPE_U16, "Aux6", "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{55,  MGVLG_DATATYPE_U16, "Aux7", "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{57,  MGVLG_DATATYPE_U16, "Aux8", "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{59,  MGVLG_DATATYPE_U16, "Aux9", "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{61,  MGVLG_DATATYPE_U16, "Aux10",  "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{63,  MGVLG_DATATYPE_U16, "Aux11",  "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{65,  MGVLG_DATATYPE_U16, "Aux12",  "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{67,  MGVLG_DATATYPE_U16, "Aux13",  "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{69,  MGVLG_DATATYPE_U16, "Aux14",  "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{71,  MGVLG_DATATYPE_U16, "Aux16",  "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{73,  MGVLG_DATATYPE_U08, "TPS ADC",  "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{74,  MGVLG_DATATYPE_U08, "Error",  "", MGVLG_STYLE_FLOAT,  1,  0,  0},
};

/*

Serial 0 fields...

mgvlgFieldType mgvlg_fields[MGVLG_FIELD_COUNT]= {
//{Offset,Type,Name,Units,Display Style,scale,transform,digits,},
{0,  MGVLG_DATATYPE_U08, "SecL", "sec",  MGVLG_STYLE_FLOAT,  1,  0,  0},
{1, MGVLG_DATATYPE_U08, "Status", "bits", MGVLG_STYLE_FLOAT,  1,  0,  0},
{2, MGVLG_DATATYPE_U08, "Engine", "bits", MGVLG_STYLE_FLOAT,  1,  0,  0},
{3, MGVLG_DATATYPE_U08, "Sync Loss",  "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{4, MGVLG_DATATYPE_U16, "MAP",  "kpa",  MGVLG_STYLE_FLOAT,  1,  0,  0},
{6, MGVLG_DATATYPE_U08, "IAT",  "°C", MGVLG_STYLE_FLOAT,  1,  -40,  0},
{7, MGVLG_DATATYPE_U08, "CLT",  "°C", MGVLG_STYLE_FLOAT,  1,  -40,  0},
{8, MGVLG_DATATYPE_U08, "Gbattery", "%",  MGVLG_STYLE_FLOAT,  1,  0,  0},
{9, MGVLG_DATATYPE_U08, "Battery V",  "V",  MGVLG_STYLE_FLOAT,  0.1,  0,  1},
{10,  MGVLG_DATATYPE_U08, "AFR",  "O2", MGVLG_STYLE_FLOAT,  0.1,  0,  3},
{11,  MGVLG_DATATYPE_U08, "Gego", "%",  MGVLG_STYLE_FLOAT,  1,  0,  0},
{12,  MGVLG_DATATYPE_U08, "Gair", "%",  MGVLG_STYLE_FLOAT,  1,  0,  0},
{13,  MGVLG_DATATYPE_U08, "Gwarm",  "%",  MGVLG_STYLE_FLOAT,  1,  0,  0},
{14,  MGVLG_DATATYPE_U16, "RPM",  "rpm",  MGVLG_STYLE_FLOAT,  1,  0,  0},
{16,  MGVLG_DATATYPE_U08, "Accel Enrich", "%",  MGVLG_STYLE_FLOAT,  2,  0,  0},
{17,  MGVLG_DATATYPE_U16, "Gammae", "%",  MGVLG_STYLE_FLOAT,  1,  0,  0},
{19,  MGVLG_DATATYPE_U08, "VE1",  "%",  MGVLG_STYLE_FLOAT,  1,  0,  0},
{20,  MGVLG_DATATYPE_U08, "VE2",  "%",  MGVLG_STYLE_FLOAT,  1,  0,  0},
{21,  MGVLG_DATATYPE_U08, "AFR Target", "O2", MGVLG_STYLE_FLOAT,  0.1,  0,  3},
{22,  MGVLG_DATATYPE_U08, "TPS DOT",  "%/s",  MGVLG_STYLE_FLOAT,  10, 0,  0},
{23,  MGVLG_DATATYPE_S08, "Advance",  "deg",  MGVLG_STYLE_FLOAT,  1,  0,  0},
{24,  MGVLG_DATATYPE_U08, "TPS",  "%",  MGVLG_STYLE_FLOAT,  1,  0,  0},
{25,  MGVLG_DATATYPE_U16, "Loops per second", "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{27,  MGVLG_DATATYPE_U16, "Speeduino Free RAM", "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{29,  MGVLG_DATATYPE_U08, "Boost Target", "kPa",  MGVLG_STYLE_FLOAT,  2,  0,  0},
{30,  MGVLG_DATATYPE_U08, "Boost Duty", "%",  MGVLG_STYLE_FLOAT,  1,  0,  0},
{31,  MGVLG_DATATYPE_U08, "Spark Bits", "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{32,  MGVLG_DATATYPE_S16, "rpm/s",  "rpm/s",  MGVLG_STYLE_FLOAT,  1,  0,  0},
{34,  MGVLG_DATATYPE_U08, "Eth %",  "%",  MGVLG_STYLE_FLOAT,  1,  0,  0},
{35,  MGVLG_DATATYPE_U08, "Flex Fuel Correction", "%",  MGVLG_STYLE_FLOAT,  1,  0,  0},
{36,  MGVLG_DATATYPE_U08, "Flex Ignition Correction", "%",  MGVLG_STYLE_FLOAT,  1,  0,  0},
{37,  MGVLG_DATATYPE_U08, "Idle Load",  "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{38,  MGVLG_DATATYPE_U08, "Test Outputs", "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{39,  MGVLG_DATATYPE_U08, "O2_2", "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{40,  MGVLG_DATATYPE_U08, "Baro Pressure",  "kpa",  MGVLG_STYLE_FLOAT,  1,  0,  0},
{41,  MGVLG_DATATYPE_U16, "Aux0", "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{43,  MGVLG_DATATYPE_U16, "Aux1", "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{45,  MGVLG_DATATYPE_U16, "Aux2", "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{47,  MGVLG_DATATYPE_U16, "Aux3", "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{49,  MGVLG_DATATYPE_U16, "Aux4", "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{51,  MGVLG_DATATYPE_U16, "Aux5", "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{53,  MGVLG_DATATYPE_U16, "Aux6", "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{55,  MGVLG_DATATYPE_U16, "Aux7", "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{57,  MGVLG_DATATYPE_U16, "Aux8", "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{59,  MGVLG_DATATYPE_U16, "Aux9", "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{61,  MGVLG_DATATYPE_U16, "Aux10",  "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{63,  MGVLG_DATATYPE_U16, "Aux11",  "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{65,  MGVLG_DATATYPE_U16, "Aux12",  "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{67,  MGVLG_DATATYPE_U16, "Aux13",  "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{69,  MGVLG_DATATYPE_U16, "Aux14",  "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{71,  MGVLG_DATATYPE_U16, "Aux16",  "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{73,  MGVLG_DATATYPE_U08, "TPS ADC",  "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{74,  MGVLG_DATATYPE_U08, "Error",  "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{75,  MGVLG_DATATYPE_U16, "PW1",  "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{77,  MGVLG_DATATYPE_U16, "PW2",  "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{79,  MGVLG_DATATYPE_U16, "PW3",  "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{81,  MGVLG_DATATYPE_U16, "PW4",  "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{83,  MGVLG_DATATYPE_U08, "Status3",  "bits", MGVLG_STYLE_FLOAT,  1,  0,  0},
{84,  MGVLG_DATATYPE_U08, "nchannels",  "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{85,  MGVLG_DATATYPE_U16, "Fuel Load",  "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{87,  MGVLG_DATATYPE_U16, "Ignition Load",  "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{89,  MGVLG_DATATYPE_U16, "Dwell",  "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{91,  MGVLG_DATATYPE_U08, "Idle Target RPM",  "RPM",  MGVLG_STYLE_FLOAT,  10, 0,  0},
{92,  MGVLG_DATATYPE_U08, "MAP DOT",  "", MGVLG_STYLE_FLOAT,  10, 0,  0},
{93,  MGVLG_DATATYPE_S08, "VVT Angle",  "deg",  MGVLG_STYLE_FLOAT,  1,  0,  0},
{94,  MGVLG_DATATYPE_U08, "VVT Target Angle", "deg",  MGVLG_STYLE_FLOAT,  1,  0,  0},
{95,  MGVLG_DATATYPE_U08, "VVT Duty", "%",  MGVLG_STYLE_FLOAT,  1,  0,  0},
{96,  MGVLG_DATATYPE_U16, "Flex Boost Correction",  "", MGVLG_STYLE_FLOAT,  1,  0,  0},
{98,  MGVLG_DATATYPE_U08, "Gbaro",  "%",  MGVLG_STYLE_FLOAT,  1,  0,  0},
{99,  MGVLG_DATATYPE_U08, "Current VE", "%",  MGVLG_STYLE_FLOAT,  1,  0,  0},
{100, MGVLG_DATATYPE_U08, "ASE",  "%",  MGVLG_STYLE_FLOAT,  1,  0,  0},
{101, MGVLG_DATATYPE_U16, "VSS (Speed)",  "km/h", MGVLG_STYLE_FLOAT,  1,  0,  0},
{103, MGVLG_DATATYPE_U08, "Gear", "", MGVLG_STYLE_FLOAT,  1,  0,  0},
}; 
*/
} // extern C
