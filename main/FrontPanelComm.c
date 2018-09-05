#include                <pthread.h>
#include                "FBLib_main.h"

byte                    FPPatchVersion = 0;
byte                    FPPatchType = 0;
byte                    FPPatchAntiFreezeOption = 0;
byte                    FPPatchPowerRestoreOption = 0;
bool                    FPPatchInitialized = FALSE;
byte                    FPWaitResponse = 0;
byte                    FPResponse[12];

static pthread_mutex_t  FrontMutex;
static bool             FrontHooked = FALSE;

static void (*Front_TxPacket_orig)(byte *Data) = NULL;
static int (*PutMsgQ_orig)(dword *MsgQ, dword *Data) = NULL;

void Front_TxPacket_hooked(byte *Data)
{
  pthread_mutex_lock(&FrontMutex);
  Front_TxPacket_orig(Data);
  pthread_mutex_unlock(&FrontMutex);
}

int PutMsgQ_hooked(dword *MsgQ, dword *Data)
{
  int                   ret;
  static dword         *_MsgQ_Front = NULL;

  //Get the address of the front panel message queue. As this is not a global variable
  //we have to use the nearest exported variable and add the offset.
  //Then extract the pointer from it.
  if(!_MsgQ_Front)
  {
    _MsgQ_Front = (dword*)TryResolve("_chKeyInputTime");
    if(_MsgQ_Front) _MsgQ_Front = (dword*)*(_MsgQ_Front + 2);
  }

  if((MsgQ == _MsgQ_Front) && (Data[0] == 0x00000001))
  {
    //DumpMemoryDword(Data, 16);

    if((Data[1] >> 24) == FPWaitResponse)
    {
      FPResponse[ 0] =  Data[1] >> 24;
      FPResponse[ 1] = (Data[1] >> 16) & 0xff;
      FPResponse[ 2] = (Data[1] >>  8) & 0xff;
      FPResponse[ 3] =  Data[1]        & 0xff;

      FPResponse[ 4] =  Data[2] >> 24;
      FPResponse[ 5] = (Data[2] >> 16) & 0xff;
      FPResponse[ 6] = (Data[2] >>  8) & 0xff;
      FPResponse[ 7] =  Data[2]        & 0xff;

      FPResponse[ 8] =  Data[3] >> 24;
      FPResponse[ 9] = (Data[3] >> 16) & 0xff;
      FPResponse[10] = (Data[3] >>  8) & 0xff;
      FPResponse[11] =  Data[3]        & 0xff;

      FPWaitResponse = 0;

      //This is allowed, the firmware handler can handle a NULL pointer
      MsgQ = NULL;
    }
  }

  //Let the original handler do its work
  ret = PutMsgQ_orig(MsgQ, Data);

  return ret;
}

void UnhookFrontTxPacket(void)
{
  TRACEENTER;

  if(FrontHooked)
  {
    if(!UnhookFirmware("Front_TxPacket", Front_TxPacket_hooked, (void*)&Front_TxPacket_orig))
      LogEntryFBLibPrintf(TRUE, "UnhookFrontTxPacket: failed to unhook Front_TxPacket");

    if(!UnhookFirmware("PutMsgQ", PutMsgQ_hooked, (void*)&PutMsgQ_orig))
      LogEntryFBLibPrintf(TRUE, "UnhookFrontTxPacket: failed to unhook PutMsgQ");

    FrontHooked = FALSE;
    TAP_Delay(10);
  }

  TRACEEXIT;
}

bool HookFrontTxPacket(void)
{
  TRACEENTER;

  if(!FrontHooked)
  {
    if(HookFirmware("Front_TxPacket", Front_TxPacket_hooked, (void*)&Front_TxPacket_orig))
    {
      if(HookFirmware("PutMsgQ", PutMsgQ_hooked, (void*)&PutMsgQ_orig))
      {
        FrontHooked = TRUE;
      }
      else
      {
        LogEntryFBLibPrintf(TRUE, "HookFrontTxPacket: failed to hook PutMsgQ");
        UnhookFrontTxPacket();
      }
    }
    else
    {
      LogEntryFBLibPrintf(TRUE, "HookFrontTxPacket: failed to hook Front_TxPacket");
    }
    TAP_Delay(10);
  }

  TRACEEXIT;
  return FrontHooked;
}

bool FP_Initialize(void)
{
  TRACEENTER;

  if(!FPPatchInitialized && HookFrontTxPacket())
  {
    byte                Buffer[20];
    int                 WaitTimeout, Repeat;

    //The following code sends a command to the front panel and waits for the reply
    //As the reply is recorded by an different thread, we can block until the reply is received

    Repeat = 2;
    do
    {
      //GetPanelType: Query: F0; Response: F2 <VERSION> <TYPE>
      Buffer[0] = 0xF0;
      FPWaitResponse = 0xF2;
      Front_TxPacket_hooked(Buffer);

      WaitTimeout = 100;
      while((FPWaitResponse != 0) && WaitTimeout)
      {
        TAP_Delay(1);
        WaitTimeout--;
      }
      Repeat--;
    }while((WaitTimeout == 0) && Repeat);

    if(WaitTimeout == 0)
    {
      UnhookFrontTxPacket();
      FPPatchVersion = 0;
      FPPatchType = 0;

      TRACEEXIT;
      return FALSE;
    }
    FPPatchVersion = FPResponse[1];
    FPPatchType = FPResponse[2];

    Repeat = 2;
    do
    {
      //Read the AntiFreeze Option Byte
      //ReadEEPROM: Query: D2 EAH EAL; Response: D1 <DTA>
      Buffer[0] = 0xD2;
      Buffer[1] = 0x01;
      Buffer[2] = 0xFF;
      FPWaitResponse = 0xD1;
      Front_TxPacket_hooked(Buffer);

      WaitTimeout = 100;
      while((FPWaitResponse != 0) && WaitTimeout)
      {
        TAP_Delay(1);
        WaitTimeout--;
      }
      Repeat--;
    }while((WaitTimeout == 0) && Repeat);

    if(WaitTimeout != 0) FPPatchAntiFreezeOption = FPResponse[1];

    Repeat = 2;
    do
    {
      //Read the PowerRestore Option Byte
      //ReadEEPROM: Query: D2 EAH EAL; Response: D1 <DTA>
      Buffer[0] = 0xD2;
      Buffer[1] = 0x01;
      Buffer[2] = 0xFE;
      FPWaitResponse = 0xD1;
      Front_TxPacket_hooked(Buffer);

      WaitTimeout = 100;
      while((FPWaitResponse != 0) && WaitTimeout)
      {
        TAP_Delay(1);
        WaitTimeout--;
      }
      Repeat--;
    }while((WaitTimeout == 0) && Repeat);

    if(WaitTimeout != 0) FPPatchPowerRestoreOption = FPResponse[1];

    FPPatchInitialized = TRUE;

    UnhookFrontTxPacket();
  }

  TRACEEXIT;
  return TRUE;
}
