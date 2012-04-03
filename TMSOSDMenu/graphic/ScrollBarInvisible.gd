#include "tap.h"

byte _ScrollBarInvisible_Cpm[] =
{
  0x00, 0x08, 0x1B, 0x90, 0xFF, 0xFF, 0x00, 0x01, 0x00, 0x01, 
  0x00, 0x6E, 0x1F, 0xCF, 0xFF, 0xFF, 0x5C, 0x00, 
  0x00, 0x65, 0x3B, 0x68, 0x61, 0xAF, 0xF5, 0xC7, 0xC4, 0x6C, 0x70, 0x42, 0x87, 0x34, 0x15, 0xE7, 
  0x00, 0x80, 0x0C, 0x92, 0xF3, 0xB9, 0xB5, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7E, 0xFD, 0xFB, 0xF7, 
  0xEF, 0xDF, 0xBF, 0x7E, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7E, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 
  0xBF, 0x7E, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7E, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7E, 
  0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7E, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7E, 0xFD, 0xFB, 
  0xF7, 0xEF, 0xDF, 0xBF, 0x7E, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7E, 0xFD, 0xFB, 0xF7, 0xEF, 
  0xDF, 0xBF, 0x7E, 0xFD, 0xFB, 0xF7, 0xFF, 0xF8, 
};

TYPE_GrData _ScrollBarInvisible_Gd =
{
  1,                              //version
  0,                              //reserved
  OSD_8888,                       //data format
  COMPRESS_Tfp,                   //compressed method
  _ScrollBarInvisible_Cpm,        //data
  23552,                           //size
    16,                           //width
   368                            //height
};
