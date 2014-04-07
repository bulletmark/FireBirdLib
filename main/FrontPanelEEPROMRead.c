#include                <unistd.h>
#include                "../libFireBird.h"

bool FrontPanelEEPROMRead(word Address, byte *Data)
{
  TRACEENTER();

  byte                  ExpectedResponseCode = 0xd1;
  int                   ExpectedResponseLen = 5;

  int                  *__frontfd;
  int                   localfd = 0;
  ssize_t               ret;
  dword                 WaitTimeout;
  byte                  Buffer[128];
  byte                  InBufferPtr;
  byte                  Retry;
  bool                  Timeout, Result;

  Result = FALSE;

  __frontfd = (int*)FIS_vfrontfd();

  if(FrontPanelGetPatch(NULL, NULL) && __frontfd && (Address < 512) && Data)
  {
    //Take over the handle from _frontfd
    localfd = *__frontfd;
    *__frontfd = 0;
    TAP_Delay(20);

    //Flush any bytes which are still in the buffer
    read(localfd, &Buffer[0], 64);

    Retry = 3;
    do
    {
      InBufferPtr = 0;

      //Query: 02 D2 EAH EAL 03
      Buffer[0] = 0x00;
      Buffer[1] = 0x02;
      Buffer[2] = 0xD2;
      Buffer[3] = Address >> 8;
      Buffer[4] = Address & 0xff;
      Buffer[5] = 0x03;

      write(localfd, Buffer, 6);

      //Wait for the F2 response
      WaitTimeout = TAP_GetTick() + 10;
      do
      {
        ret = read(localfd, &Buffer[InBufferPtr], 64);
        if(ret > 0)
        {
          InBufferPtr += ret;
          WaitTimeout = TAP_GetTick() + 5;
        }
        Timeout = (TAP_GetTick() > WaitTimeout);
      }while(!Timeout);

      //DumpMemory(Buffer, InBufferPtr, 16);

      if((InBufferPtr == ExpectedResponseLen) && (Buffer[2] == ExpectedResponseCode))
      {
        //Response: 00 02 D1 DTA 03
        if(Data) *Data = Buffer[3];
        Result = TRUE;
      }

      Retry--;
    }while((InBufferPtr == 0) && (Retry > 0));

    //Restore the communication
    *__frontfd = localfd;
    localfd = 0;
  }

  return Result;
}
