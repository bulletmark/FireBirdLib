#include "tap.h"

byte _Button_list_Cpm[] =
{
  0x00, 0x08, 0x1B, 0x90, 0xFF, 0xFF, 0x00, 0x01, 0x00, 0x01, 
  0x02, 0x9A, 0xBC, 0x42, 0xFF, 0xFF, 0x0C, 0x80, 
  0x01, 0xFE, 0x62, 0x9A, 0xF7, 0xBA, 0xB4, 0xB2, 0xCF, 0xC0, 0x97, 0x67, 0x65, 0xA6, 0x45, 0xAB, 
  0x08, 0xED, 0x9D, 0xAC, 0xE8, 0x88, 0x84, 0xB4, 0x51, 0x48, 0x46, 0xD2, 0x25, 0xB6, 0x25, 0x77, 
  0xB6, 0xD9, 0x77, 0x9C, 0x29, 0x58, 0xD1, 0x1B, 0x0E, 0x95, 0xBC, 0x89, 0x0E, 0x9A, 0x75, 0xA4, 
  0xA0, 0x91, 0x89, 0xD2, 0xD0, 0x5C, 0x34, 0x49, 0x4C, 0x95, 0x71, 0x51, 0x25, 0x22, 0xC8, 0xD7, 
  0x4C, 0x44, 0x51, 0x4B, 0xC3, 0x51, 0xFD, 0xBF, 0xFF, 0x6B, 0xD9, 0x2D, 0x19, 0x4D, 0xA2, 0x78, 
  0x2E, 0xBB, 0x97, 0x41, 0x70, 0x3C, 0x0F, 0x24, 0x17, 0xC2, 0x8B, 0x8E, 0xE1, 0x41, 0xDC, 0x1F, 
  0x56, 0xE9, 0xD8, 0x74, 0xE4, 0x6F, 0x21, 0x42, 0x84, 0x3F, 0xF3, 0x39, 0xF3, 0xF1, 0x04, 0x10, 
  0x1A, 0xD2, 0x43, 0xF0, 0x20, 0x40, 0x1A, 0xD2, 0x43, 0xEF, 0x5E, 0xBD, 0x1A, 0xD2, 0x43, 0xE7, 
  0x9E, 0x78, 0x95, 0x36, 0xF0, 0x0F, 0x17, 0x16, 0xA7, 0x87, 0x96, 0x5A, 0x36, 0xCA, 0x78, 0xEF, 
  0xCF, 0x1C, 0xAB, 0x97, 0x63, 0x8C, 0xFB, 0x3E, 0x9B, 0xC7, 0x87, 0x84, 0x20, 0x9E, 0x2F, 0xEF, 
  0x5D, 0x8E, 0x7D, 0xE3, 0xB1, 0x05, 0xFE, 0x7D, 0xBB, 0x4B, 0x38, 0xF9, 0xFF, 0x79, 0xE4, 0x41, 
  0xFB, 0x76, 0x72, 0x1F, 0x38, 0xE3, 0x84, 0xA9, 0xCD, 0xCA, 0xB1, 0x1F, 0x2F, 0x45, 0x88, 0xB2, 
  0x77, 0xA3, 0x6C, 0xA7, 0xBB, 0x86, 0xE8, 0xD7, 0xF0, 0x2F, 0x5C, 0x1B, 0x9E, 0xCD, 0xE1, 0xC3, 
  0x33, 0x1A, 0xC0, 0xD4, 0xD1, 0x9F, 0x8F, 0x9E, 0xC4, 0x62, 0x60, 0xB9, 0x35, 0xF7, 0xEF, 0x9B, 
  0xC9, 0xB7, 0x2A, 0x72, 0x31, 0x1D, 0x4C, 0xEC, 0xE4, 0x3E, 0xCD, 0x9B, 0x31, 0x2A, 0x7D, 0xF9, 
  0x31, 0xFB, 0x5B, 0x76, 0xCD, 0x04, 0xBB, 0xFD, 0xB8, 0xA7, 0x1A, 0xFF, 0x42, 0x15, 0x71, 0xB9, 
  0xFB, 0x18, 0x0D, 0x8D, 0xCF, 0x8F, 0xD9, 0x70, 0x21, 0xDD, 0x56, 0x88, 0xBC, 0xEA, 0xF1, 0x9D, 
  0x95, 0x1F, 0xA1, 0xDD, 0x5A, 0xF0, 0x83, 0x96, 0xED, 0x06, 0x15, 0xF5, 0x79, 0xA5, 0x1D, 0xBF, 
  0x57, 0x8D, 0xD4, 0x8A, 0x7C, 0xB4, 0x2B, 0x66, 0x76, 0x72, 0x1F, 0x62, 0xC5, 0x88, 0x95, 0x28, 
  0x8F, 0xB5, 0x66, 0xC8, 0x4B, 0xBF, 0xDA, 0xE9, 0x57, 0x1A, 0xFC, 0x4B, 0xA6, 0x86, 0xE7, 0xF3, 
  0x62, 0xC7, 0xF4, 0x7F, 0x8B, 0x69, 0x59, 0x23, 0x0E, 0xFE, 0xF1, 0xAC, 0x62, 0xF3, 0x85, 0xDD, 
  0xB3, 0x39, 0x3B, 0x6F, 0xAC, 0xEB, 0x0D, 0x97, 0x97, 0x1B, 0x4E, 0x5F, 0x5B, 0xFA, 0x49, 0x0F, 
  0xED, 0x57, 0xAF, 0x13, 0xB3, 0xB3, 0xB2, 0x67, 0xD9, 0xE4, 0x8F, 0xDB, 0xE8, 0xE8, 0x93, 0xE8, 
  0x5B, 0x29, 0xE8, 0xF2, 0x77, 0x66, 0xBF, 0xC4, 0x73, 0x1F, 0x6E, 0xF9, 0x0D, 0xD1, 0xB9, 0xF3, 
  0xB2, 0x9C, 0x8E, 0xB4, 0x4A, 0xA1, 0xC1, 0xDF, 0xA9, 0x09, 0xD3, 0x25, 0x99, 0xB7, 0xBC, 0xA9, 
  0xD9, 0x1B, 0x2F, 0xC3, 0xD7, 0xAC, 0x99, 0x7D, 0x19, 0x21, 0x72, 0x1F, 0x5F, 0x51, 0x51, 0xA8, 
  0x3F, 0x45, 0x42, 0x98, 0x78, 0x30, 0xEA, 0xE4, 0xFC, 0x53, 0xF5, 0xE3, 0x9C, 0x2E, 0x5F, 0x6E, 
  0x3F, 0x63, 0xE4, 0x2E, 0x43, 0xEB, 0x97, 0x2E, 0xD4, 0x1F, 0x46, 0x77, 0xCC, 0x14, 0x08, 0x97, 
  0x0C, 0x06, 0x5F, 0x71, 0xAC, 0x82, 0x77, 0xEF, 0x36, 0xD3, 0x47, 0xC8, 0x5C, 0x87, 0xF6, 0x8B, 
  0x56, 0xE9, 0x8F, 0xEC, 0x35, 0xE9, 0x8D, 0xFB, 0x7A, 0xEB, 0xEA, 0x56, 0x5C, 0xE5, 0x87, 0xDE, 
  0xEA, 0x70, 0x26, 0x8F, 0x90, 0xB9, 0x0F, 0xAD, 0x58, 0xB3, 0x4C, 0x7D, 0x34, 0xF2, 0x41, 0xEE, 
  0xC8, 0x70, 0x3E, 0x19, 0x96, 0x03, 0x6E, 0xBE, 0x8E, 0x46, 0x1B, 0x56, 0x2A, 0x4D, 0x87, 0x8B, 
  0xD3, 0x65, 0x34, 0x7C, 0x85, 0xC8, 0x7D, 0x65, 0x3D, 0x3E, 0x90, 0xFF, 0x7F, 0x0A, 0xAC, 0x63, 
  0x60, 0xB2, 0x93, 0x34, 0x13, 0xE9, 0x74, 0x3D, 0xDF, 0x87, 0x6D, 0xB9, 0x36, 0x7F, 0xB7, 0xCA, 
  0xDC, 0x45, 0xE6, 0x6F, 0x47, 0x57, 0x9B, 0x54, 0x33, 0x72, 0x5C, 0x9A, 0x9F, 0x0D, 0xC5, 0x44, 
  0xD1, 0xF2, 0x17, 0x21, 0xF5, 0x6A, 0xD5, 0xE9, 0x0F, 0xCB, 0x9D, 0x75, 0x04, 0xF6, 0x80, 0xFC, 
  0xFA, 0x74, 0xA2, 0x1D, 0xBB, 0x03, 0x7D, 0xBF, 0x47, 0x1F, 0xD3, 0xE2, 0x6C, 0x2E, 0xE0, 0x54, 
  0x84, 0x89, 0x3F, 0x5F, 0x47, 0xC8, 0x5C, 0x87, 0xD5, 0x2A, 0x55, 0xF8, 0xC7, 0xFC, 0xCA, 0x54, 
  0xA9, 0x02, 0xD5, 0x34, 0x23, 0x67, 0x49, 0x3F, 0xA9, 0xD2, 0xC8, 0x5C, 0x87, 0xD4, 0xA9, 0x53, 
  0xFC, 0x1F, 0xFE, 0xC9, 0x0B, 0x90, 0xFD, 0x35, 0x35, 0x36, 0xA8, 0xF9, 0x0B, 0x90, 0xFA, 0x85, 
  0x0A, 0x35, 0x47, 0xC8, 0x5D, 0x1F, 0xED, 0x0E, 0x96, 0x96, 0x94, 0x6C, 0x69, 0x29, 0x3F, 0xD2, 
  0x41, 0xE8, 0x8D, 0x80, 
};

TYPE_GrData _Button_list_Gd =
{
  1,                              //version
  0,                              //reserved
  OSD_8888,                       //data format
  COMPRESS_Tfp,                   //compressed method
  _Button_list_Cpm,               //data
  3200,                           //size
    40,                           //width
    20                            //height
};
