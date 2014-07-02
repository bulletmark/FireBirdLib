#include                <unistd.h>
#include                "FBLib_main.h"

bool FrontPanelEEPROMRead(word Address, byte *Data)
{
  TRACEENTER();

  byte                  Buffer[20];
  int                   WaitTimeout;

  if(!FP_Initialize())
  {
    TRACEEXIT();
    return FALSE;
  }

  //Cache the two options so that the FrontPanelEEPROMRead() doesn't need to communicate with the front panel
  if(Address == 0x01ff)
  {
    if(Data) *Data = FPPatchAntiFreezeOption;

    TRACEEXIT();
    return TRUE;
  }

  if(Address == 0x01fe)
  {
    if(Data) *Data = FPPatchPowerRestoreOption;

    TRACEEXIT();
    return TRUE;
  }

  if(!HookFrontTxPacket())
  {
    TRACEEXIT();
    return FALSE;
  }

  //Read the AntiFreeze Option Byte
  //ReadEEPROM: Query: D2 EAH EAL; Response: D1 <DTA>
  Buffer[0] = 0xD2;
  Buffer[1] = Address >> 8;
  Buffer[2] = Address & 0xff;
  FPWaitResponse = 0xD1;
  Front_TxPacket_hooked(Buffer);

  WaitTimeout = 100;
  while((FPWaitResponse != 0) && WaitTimeout)
  {
    TAP_Delay(1);
    WaitTimeout--;
  }

  if(Data) *Data = FPResponse[1];

  UnhookFrontTxPacket();

  TRACEEXIT();
  return (WaitTimeout != 0);
}
