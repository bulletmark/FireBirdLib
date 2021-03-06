#include "libFireBird.h"

byte FPIRData[] = {0xa5, 0x00, 0x02, 0x34, 0x0a, 0x00,   //Mode 1
                   0xa5, 0x00, 0x49, 0x00, 0x0a, 0x00,   //Mode 2
                   0xa5, 0x00, 0x49, 0x99, 0x0a, 0x00,   //Mode 3
                   0xa5, 0x00, 0x20, 0xdf, 0x0a, 0x00,   //Mode 4
                   0xa5, 0x00, 0x50, 0x01, 0x0a, 0x00,   //Mode 5
                   0xa5, 0x00, 0x04, 0xff, 0x0a, 0x00};  //Mode 6

void SetRemoteMode(byte Mode, byte Index, bool Active)
{
  TRACEENTER();

  Mode--;
  if((Mode < 6) && (Index < 4))
  {
    DevFront_SetIrCode(Index, (Active ? 1 : 0), FPIRData[Mode * 6 + 2], FPIRData[Mode * 6 + 3], FPIRData[Mode * 6 + 4]);
  }

  TRACEEXIT();
}
