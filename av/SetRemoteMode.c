#include "../libFireBird.h"

byte FPIRData[] = {0xa5, 0x00, 0x02, 0x34, 0x0a, 0x00,   //Mode 1
                   0xa5, 0x01, 0x49, 0x00, 0x0a, 0x00,   //Mode 2 (can't be used at the same time as mode 5)
                   0xa5, 0x02, 0x49, 0x99, 0x0a, 0x00,   //Mode 3
                   0xa5, 0x03, 0x20, 0xdf, 0x0a, 0x00,   //Mode 4
                   0xa5, 0x01, 0x50, 0x01, 0x0a, 0x00};  //Mode 5 (can't be used at the same time as mode 2)

void SetRemoteMode(byte Mode, bool Active)
{
  TRACEENTER();

  void (*DevFront_SetIrCode)(byte P1, byte P2, byte P3, byte P4, byte P5);

  DevFront_SetIrCode = (void*)FIS_fwSetIrCode();
  if(DevFront_SetIrCode)
  {
    Mode--;
    if(Mode < 5)
    {
      DevFront_SetIrCode(FPIRData[Mode * 6 + 1],
                         (Active ? 1 : 0),
                         FPIRData[Mode * 6 + 2],
                         FPIRData[Mode * 6 + 3],
                         FPIRData[Mode * 6 + 4]);
    }
  }

  TRACEEXIT();
}
