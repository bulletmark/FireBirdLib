#include "FBLib_av.h"
#include "../libFireBird.h"

void OSDToBMP(TYPE_OsdBaseInfo OsdBaseInfo, int BMPwidth, int BMPheight, byte *BMPPixelBuffer, int Alpha)
{
  dword                *pixel;
  register int          pos, x, y;
  int                   n1, n2, nR, nG, nB;

  (void)Alpha;

#ifdef DEBUG_FIREBIRDLIB
  CallTraceEnter("OSDToBMP");
#endif

  pixel = OsdBaseInfo.frameBuffer;
  for(y = 0; y < BMPheight; y++)
  {
    for(x = 0; x < BMPwidth; x++ )
    {
      pos = ((BMPheight - y - 1) * BMPwidth + x) * 3;

      //if((R8888(*pixel) > 7) || (G8888(*pixel) > 7) || (B8888(*pixel) > 7))
      //{

      //TODO: Alpha parameter
      n1 = A8888(*pixel) / 2.55;
      n2 = 100 - n1;

      //TODO: Alpha calculation
      nR = (n2 * BMPPixelBuffer[pos + 2] + n1 * R8888(*pixel)) / 100;
      nG = (n2 * BMPPixelBuffer[pos + 1] + n1 * G8888(*pixel)) / 100;
      nB = (n2 * BMPPixelBuffer[pos]     + n1 * B8888(*pixel)) / 100;

      BMPPixelBuffer[pos + 2] = _Clip(nR);
      BMPPixelBuffer[pos + 1] = _Clip(nG);
      BMPPixelBuffer[pos]     = _Clip(nB);

      //}

      pixel++;
    }
  }

#ifdef DEBUG_FIREBIRDLIB
  CallTraceExit(NULL);
#endif
}
