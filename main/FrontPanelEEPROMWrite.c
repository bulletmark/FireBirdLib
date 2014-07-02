#include                <unistd.h>
#include                "FBLib_main.h"

bool FrontPanelEEPROMWrite(word Address, byte Data)
{
  TRACEENTER();

  byte                  Buffer[8];

  if(!FP_Initialize() || !HookFrontTxPacket())
  {
    TRACEEXIT();
    return FALSE;
  }

  //Query: D3 EAH EAL DTA
  Buffer[0] = 0xD3;
  Buffer[1] = Address >> 8;
  Buffer[2] = Address & 0xff;
  Buffer[3] = Data;

  Front_TxPacket_hooked(Buffer);
  UnhookFrontTxPacket();

  //Cache the two options so that the FrontPanelEEPROMRead() doesn't need to communicate with the front panel
  if(Address == 0x01ff) FPPatchAntiFreezeOption = Data;
  if(Address == 0x01fe) FPPatchPowerRestoreOption = Data;

  TRACEEXIT();
  return TRUE;
}
