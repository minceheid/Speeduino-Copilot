#ifndef SPEEDUINO_H
#define SPEEDUINO_H

typedef struct {
  byte secl;           //0
  byte status1;        //1
  byte engine;         //2
  byte dwell;          //3
  byte maplo;          //4
  byte maphi;          //5
  byte iat;            //6
  byte clt;            //7
  byte batcorrection;  //8
  byte batteryv;       //9
  byte o2;             //10
  byte egocorrection;  //11
  byte iatcorrection;  //12
  byte wue;            //13
  byte rpmlo;          //14
  byte rpmhi;          //15
  byte taeamount;      //16
  byte gammae;         //17
  byte ve;             //18
  byte afrtarget;      //19  
  byte pw1lo;          //20
  byte pw1hi;          //21
  byte tpsdot;         //22
  byte advance;        //23
  byte tps;            //24
  byte loopslo;        //25
  byte loopshi;        //26
  byte freeramlo;      //27
  byte freeramhi;      //28
  byte boosttarget;    //29
  byte boostduty;      //30
  byte spark;          //31
  byte rpmdotlo;       //32
  byte rpmdothi;       //33
  byte ethanolpct;     //34
  byte flexcorrection; //35
  byte flexigncorrection; //36
  byte idleload;       //37
  byte testoutputs;    //38
  byte o2_2;           //39
  byte baro;           //40
  byte candata[32];    //41-72
  byte tpsadc;         //73
  byte errors;         //74
} speeduinoDataPacket;
const int PACKETLENGTH=sizeof(speeduinoDataPacket);

#endif // SPEEDUINO_H
