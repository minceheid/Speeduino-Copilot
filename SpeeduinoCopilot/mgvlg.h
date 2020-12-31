#include "speeduino.h"

////////////////////////////
// Public functions
void mgvlgInit();
void writeRecord(speeduinoDataPacket *d);


////////////////////////////
// These are really all private definitions and structures, so perhps oughtn't be
// in the header file. Seems to make sense to keep them separate though.

#define MGVLG_DATATYPE_U08 0x00
#define MGVLG_DATATYPE_S08 0x01
#define MGVLG_DATATYPE_U16 0x02
#define MGVLG_DATATYPE_S16 0x03
#define MGVLG_DATATYPE_F32 0x07

#define MGVLG_STYLE_FLOAT 0x00

typedef struct {
  byte type;
  char name[34];
  char units[34];
  byte style;
  float scale;
  float transform;
  byte digits;
  int offset;
} MGVLG_FIELD_SCALAR;


const int MGVLG_SCALAR_COUNT=52;
MGVLG_FIELD_SCALAR mgvlg_fields[MGVLG_SCALAR_COUNT]= {
//{Type,Name,4Units,3Display Style,4scale,5transform,6digits,offset},
{MGVLG_DATATYPE_U08,"SecL","sec",MGVLG_STYLE_FLOAT,1,0,0,               0},
{MGVLG_DATATYPE_U08,"Status","bits",MGVLG_STYLE_FLOAT,1,0,0,            1},
{MGVLG_DATATYPE_U08,"Engine","bits",MGVLG_STYLE_FLOAT,1,0,0,            2},
// 3 = Dwell
{MGVLG_DATATYPE_U16,"MAP","kpa",MGVLG_STYLE_FLOAT,1,0,0,                4},
{MGVLG_DATATYPE_U08,"IAT","°C",MGVLG_STYLE_FLOAT,1,-40,0,               6},
{MGVLG_DATATYPE_U08,"CLT","°C",MGVLG_STYLE_FLOAT,1,-40,0,               7},
{MGVLG_DATATYPE_U08,"Gbattery","%",MGVLG_STYLE_FLOAT,1,0,0,             8},
{MGVLG_DATATYPE_U08,"Battery V","V",MGVLG_STYLE_FLOAT,0.1,0,1,          9},
{MGVLG_DATATYPE_U08,"AFR","O2",MGVLG_STYLE_FLOAT,0.1,0,3,               10},
{MGVLG_DATATYPE_U08,"Gego","%",MGVLG_STYLE_FLOAT,1,0,0,                 11},
{MGVLG_DATATYPE_U08,"Gair","%",MGVLG_STYLE_FLOAT,1,0,0,                 12},
{MGVLG_DATATYPE_U08,"Gwarm","%",MGVLG_STYLE_FLOAT,1,0,0,                13},
{MGVLG_DATATYPE_U16,"RPM","rpm",MGVLG_STYLE_FLOAT,1,0,0,                14},
{MGVLG_DATATYPE_U08,"Accel Enrich","%",MGVLG_STYLE_FLOAT,2,0,0,         16},
{MGVLG_DATATYPE_U08,"Gammae","%",MGVLG_STYLE_FLOAT,1,0,0,               17},
{MGVLG_DATATYPE_U08,"Current VE","%",MGVLG_STYLE_FLOAT,1,0,0,           18},
{MGVLG_DATATYPE_U08,"AFR Target","O2",MGVLG_STYLE_FLOAT,0.1,0,3,        19},
{MGVLG_DATATYPE_U16,"PW","ms",MGVLG_STYLE_FLOAT,0.001,0,3,              20},
{MGVLG_DATATYPE_U08,"TPS DOT","%/s",MGVLG_STYLE_FLOAT,10,0,0,           22},
{MGVLG_DATATYPE_S08,"Advance","deg",MGVLG_STYLE_FLOAT,1,0,0,            23},
{MGVLG_DATATYPE_U08,"TPS","%",MGVLG_STYLE_FLOAT,1,0,0,                  24},
//25 U16 Loops per second
//27 U16 Free RAM
{MGVLG_DATATYPE_U08,"Boost Target","kPa",MGVLG_STYLE_FLOAT,2,0,0,       29},
{MGVLG_DATATYPE_U08,"Boost Duty","%",MGVLG_STYLE_FLOAT,1,0,0,           30},
//31 U08 Spark related bitfield
{MGVLG_DATATYPE_S16,"rpm/s","rpm/s",MGVLG_STYLE_FLOAT,1,0,0,            32},
{MGVLG_DATATYPE_U08,"Eth %","%",MGVLG_STYLE_FLOAT,1,0,0,                34},
//35 U08 Flex fuel correction
//36 U08 Flex ignition correction
//37 U08 idleLoad
//38 U08 testOutputs
//39 U08 O2_2
{MGVLG_DATATYPE_U08,"Baro Pressure","kpa",MGVLG_STYLE_FLOAT,1,0,0,      40},
{MGVLG_DATATYPE_U16,"Aux0","",MGVLG_STYLE_FLOAT,1,0,0,                41},
{MGVLG_DATATYPE_U16,"Aux1","",MGVLG_STYLE_FLOAT,1,0,0,                43},
{MGVLG_DATATYPE_U16,"Aux2","",MGVLG_STYLE_FLOAT,1,0,0,                45},
{MGVLG_DATATYPE_U16,"Aux3","",MGVLG_STYLE_FLOAT,1,0,0,                47},
{MGVLG_DATATYPE_U16,"Aux4","",MGVLG_STYLE_FLOAT,1,0,0,                49},
{MGVLG_DATATYPE_U16,"Aux5","",MGVLG_STYLE_FLOAT,1,0,0,                51},
{MGVLG_DATATYPE_U16,"Aux6","",MGVLG_STYLE_FLOAT,1,0,0,                53},
{MGVLG_DATATYPE_U16,"Aux7","",MGVLG_STYLE_FLOAT,1,0,0,                55},
{MGVLG_DATATYPE_U16,"Aux8","",MGVLG_STYLE_FLOAT,1,0,0,                57},
{MGVLG_DATATYPE_U16,"Aux9","",MGVLG_STYLE_FLOAT,1,0,0,                59},
{MGVLG_DATATYPE_U16,"Aux10","",MGVLG_STYLE_FLOAT,1,0,0,               61},
{MGVLG_DATATYPE_U16,"Aux11","",MGVLG_STYLE_FLOAT,1,0,0,               63},
{MGVLG_DATATYPE_U16,"Aux12","",MGVLG_STYLE_FLOAT,1,0,0,               65},
{MGVLG_DATATYPE_U16,"Aux13","",MGVLG_STYLE_FLOAT,1,0,0,               67},
{MGVLG_DATATYPE_U16,"Aux14","",MGVLG_STYLE_FLOAT,1,0,0,               69},
{MGVLG_DATATYPE_U16,"Aux16","",MGVLG_STYLE_FLOAT,1,0,0,               71},
//73 U08 tpsADC
//74 getNextError

// following have not yet been implemented
{MGVLG_DATATYPE_U08,"VVT Target Angle","deg",MGVLG_STYLE_FLOAT,1,0,0,-1},
{MGVLG_DATATYPE_U08,"VVT Duty","%",MGVLG_STYLE_FLOAT,1,0,0,-1},
{MGVLG_DATATYPE_S08,"VVT Angle","deg",MGVLG_STYLE_FLOAT,1,0,0,-1},
{MGVLG_DATATYPE_U08,"Gbaro","%",MGVLG_STYLE_FLOAT,1,0,0,-1},
{MGVLG_DATATYPE_U08,"Sync Loss #","",MGVLG_STYLE_FLOAT,1,0,0,-1},
{MGVLG_DATATYPE_U08,"Gear","",MGVLG_STYLE_FLOAT,1,0,0,-1},
{MGVLG_DATATYPE_U08,"Idle Target RPM","RPM",MGVLG_STYLE_FLOAT,10,0,0,-1},
{MGVLG_DATATYPE_U16,"VSS (Speed)","km/h",MGVLG_STYLE_FLOAT,1,0,0,-1},
{MGVLG_DATATYPE_U08,"VE1","%",MGVLG_STYLE_FLOAT,1,0,0,-1},
{MGVLG_DATATYPE_U08,"VE2","%",MGVLG_STYLE_FLOAT,1,0,0,-1},
}; 
