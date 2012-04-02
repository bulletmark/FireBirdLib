#include "FBLib_av.h"
#include "../libFireBird.h"

void VideoToBMP(TYPE_VideoFrame VideoFrame, int BMPwidth, int BMPheight, byte *BMPPixelBuffer, int DstX, int DstY, int DstWidth, int DstHeight)
{
  dword                *VideoData;
  dword                *SrcPixel;
  byte                 *DstPixel;
  int                   SX, SY;
  register int          x, y;

#ifdef DEBUG_FIREBIRDLIB
  CallTraceEnter("VideoToBMP");
#endif

  VideoData = (dword*)VideoFrame.data;
  for(y = DstY; y < (DstY + DstHeight); y++)
  {
    SY =  (y - DstY) * VideoFrame.height / DstHeight;
    for(x = DstX; x < (DstX + DstWidth); x++)
    {
      SX =  (x - DstX) * VideoFrame.width / DstWidth;
      SrcPixel = (dword*)&VideoData[SX + SY * VideoFrame.width];

      DstPixel = &BMPPixelBuffer[((BMPheight - y - 1) * BMPwidth + x) * 3];
      DstPixel[0] = B8888(*SrcPixel);
      DstPixel[1] = G8888(*SrcPixel);
      DstPixel[2] = R8888(*SrcPixel);
    }
  }

#ifdef DEBUG_FIREBIRDLIB
  CallTraceExit(NULL);
#endif

}
