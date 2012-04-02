#include                "FBLib_FontManager.h"

//#define NEWBLEND  1

#ifndef NEWBLEND

dword FM_AlphaBlendRGB(byte Alpha, dword FG, dword BG, float AntiAliasFactor)
{
  dword              red, green, blue;

  red = FM_AlphaBlend(Alpha, (FG >> 16) & 0xff, (BG >> 16) & 0xff, AntiAliasFactor);
  green = FM_AlphaBlend(Alpha, (FG >> 8) & 0xff, (BG >> 8) & 0xff, AntiAliasFactor);
  blue = FM_AlphaBlend(Alpha, FG & 0xff, BG & 0xff, AntiAliasFactor);

  return ARGB(0, red, green, blue);
}

#else

//uint32 Blend(uint32 s, uint32 d, uint32 a)
dword FM_AlphaBlendRGB(byte Alpha, dword FG, dword BG)
{
  const dword dstrb = FG & 0xFF00FF;
  const dword dstg = FG & 0x00FF00;

  const dword srcrb = BG & 0xFF00FF;
  const dword srcg = BG & 0x00FF00;

  dword drb = srcrb - dstrb, rb, g;
  dword dg = srcg - dstg;

  drb *= Alpha;
  dg *= Alpha;
  drb >>= 8;
  dg >>= 8;

  rb = (drb + dstrb) & 0xFF00FF;
  g = (dg + dstg) & 0x00FF00;

  return rb | g;
}

#endif
