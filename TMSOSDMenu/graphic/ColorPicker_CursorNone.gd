#include "tap.h"

byte _ColorPicker_CursorNone_Cpm[] =
{
  0x00, 0x08, 0x1B, 0x90, 0xFF, 0xFF, 0x00, 0x01, 0x00, 0x01, 
  0x00, 0x16, 0xAA, 0xE5, 0xFF, 0xFF, 0x01, 0xB0, 
  0x00, 0x06, 0x30, 0x04, 0x6D, 0x7F, 0x81, 0x4C, 0x61, 0x44, 0xAF, 0x0F, 0xE0, 0x21, 0xBE, 0x80, 
};

TYPE_GrData _ColorPicker_CursorNone_Gd =
{
  1,                              //version
  0,                              //reserved
  OSD_8888,                       //data format
  COMPRESS_Tfp,                   //compressed method
  _ColorPicker_CursorNone_Cpm,      //data
   432,                           //size
    12,                           //width
     9                            //height
};

