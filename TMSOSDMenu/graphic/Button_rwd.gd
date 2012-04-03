#include "tap.h"

byte _Button_rwd_Cpm[] =
{
  0x00, 0x08, 0x1B, 0x90, 0xFF, 0xFF, 0x00, 0x01, 0x00, 0x01, 
  0x00, 0xF2, 0xE7, 0x01, 0xFF, 0xFF, 0x07, 0x80, 
  0x00, 0xAC, 0x5A, 0x71, 0xC3, 0x54, 0xDD, 0x5A, 0xF0, 0x1D, 0x18, 0xCC, 0x16, 0x82, 0x22, 0xAA, 
  0xB9, 0xAE, 0xE0, 0x1B, 0x11, 0x8A, 0xC2, 0xA3, 0x15, 0x88, 0xC5, 0x62, 0x3C, 0x35, 0xBC, 0x0B, 
  0xA7, 0xFB, 0xEC, 0x6F, 0x60, 0xF2, 0x0E, 0x81, 0x83, 0x60, 0xB8, 0x1B, 0x0E, 0xC0, 0x60, 0x30, 
  0x2D, 0x27, 0xE8, 0x76, 0x0A, 0x1E, 0xCA, 0x10, 0x0E, 0x10, 0x05, 0xDD, 0xED, 0xEC, 0x30, 0xC1, 
  0x3C, 0xDD, 0xDF, 0x1E, 0xBE, 0xFB, 0xD1, 0x94, 0x3F, 0x75, 0xD7, 0x23, 0x28, 0x7E, 0xDB, 0x6D, 
  0x46, 0x50, 0xFD, 0x96, 0x58, 0x8C, 0xA1, 0xFA, 0xEB, 0xAD, 0x33, 0xBC, 0xF9, 0x71, 0xF1, 0xAC, 
  0x3F, 0x55, 0x55, 0x27, 0x4A, 0x77, 0xCB, 0xAE, 0xB2, 0x87, 0xE9, 0xA6, 0x94, 0xFC, 0xAA, 0xEF, 
  0x97, 0x4D, 0x6A, 0xA1, 0xFF, 0x5A, 0x28, 0x46, 0xDB, 0x6F, 0xE6, 0xB8, 0xE3, 0x9E, 0xF5, 0x7D, 
  0xF2, 0xAB, 0x3F, 0x4D, 0x6B, 0x06, 0x17, 0x0F, 0xD1, 0xC3, 0x86, 0x27, 0xDA, 0x69, 0xAF, 0xAE, 
  0xF9, 0x4C, 0xF9, 0xEB, 0x58, 0x30, 0xB8, 0x7E, 0x79, 0xE7, 0xC4, 0xFA, 0xAE, 0x40, 0xFB, 0x6B, 
  0x55, 0x0B, 0x87, 0xFD, 0x26, 0x9B, 0xEF, 0x7E, 0x41, 0xF4, 0xD6, 0x50, 0xB8, 0x7E, 0x69, 0x65, 
  0xFD, 0x3E, 0xB0, 0xFA, 0xEB, 0x0B, 0x87, 0xE5, 0x92, 0x4F, 0xE3, 0xEA, 0x0F, 0xAE, 0xB0, 0xB8, 
  0x7E, 0x38, 0xE3, 0xEA, 0x7F, 0xBD, 0x0B, 0x87, 0xE2, 0x8A, 0x2D, 0x8F, 0x85, 0xC3, 0xF0, 0xC3, 
  0x0E, 0xC7, 0xC2, 0xE1, 0xF8, 0x20, 0x83, 0x63, 0xE1, 0x70, 0xFB, 0xCF, 0x3D, 0xB1, 0xF0, 0xBA, 
  0xBF, 0x61, 0xBE, 0xFB, 0xE9, 0xBD, 0xD7, 0x7F, 0xE8, 0x3D, 0x46, 0xC0, 
};

TYPE_GrData _Button_rwd_Gd =
{
  1,                              //version
  0,                              //reserved
  OSD_8888,                       //data format
  COMPRESS_Tfp,                   //compressed method
  _Button_rwd_Cpm,                //data
  1920,                           //size
    24,                           //width
    20                            //height
};
