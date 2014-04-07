#include                <unistd.h>
#include                "../libFireBird.h"

bool FrontPanelGetPatch(byte *Version, byte *Type)
{
  TRACEENTER();

  byte                  ExpectedResponseCode = 0xf2;
  int                   ExpectedResponseLen = 6;

  int                  *__frontfd = NULL;
  int                   localfd = 0;
  ssize_t               ret;
  dword                 WaitTimeout;
  byte                  Buffer[128];
  byte                  InBufferPtr;
  byte                  Retry;
  bool                  Timeout;

  static byte           FPVersion = 0, FPType = 0;
  static bool           AlreadyChecked = FALSE;
  static bool           Result = FALSE;

  if(!AlreadyChecked)
  {
    //Find the int* variable _frontfd
    __frontfd = (int*)FIS_vfrontfd();
    if(__frontfd == NULL)
    {
      TRACEEXIT();
      return FALSE;
    }

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

      //Send the F0 command
      Buffer[0] = 0x00;
      Buffer[1] = 0x02;
      Buffer[2] = 0xf0;
      Buffer[3] = 0x03;

      write(localfd, Buffer, 4);

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

      if((InBufferPtr == ExpectedResponseLen) && (Buffer[2] == ExpectedResponseCode))
      {
        FPVersion = Buffer[3];
        FPType = Buffer[4];
        Result = TRUE;
        break;
      }
      Retry--;
    }while((InBufferPtr == 0) && (Retry > 0));

    //Restore the communication
    *__frontfd = localfd;
    localfd = 0;
  }

  AlreadyChecked = TRUE;
  if(Version) *Version = FPVersion;
  if(Type) *Type = FPType;

  TRACEEXIT();
  return Result;
}
