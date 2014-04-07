#include                <unistd.h>
#include                "../libFireBird.h"

bool FrontPanelEEPROMWrite(word Address, byte Data)
{
  TRACEENTER();

  byte                  Buffer[6];
  bool                  ret;
  int                  *__frontfd;
  int                   localfd = 0;

  ret = FALSE;

  __frontfd = (int*)FIS_vfrontfd();

  //Take over the handle from _frontfd
  localfd = *__frontfd;
  *__frontfd = 0;
  TAP_Delay(20);

  if(FrontPanelGetPatch(NULL, NULL) && __frontfd && (Address < 512))
  {
    //Query: 02 D3 EAH EAL DTA 03
    Buffer[0] = 0x00;
    Buffer[1] = 0x02;
    Buffer[2] = 0xD3;
    Buffer[3] = Address >> 8;
    Buffer[4] = Address & 0xff;
    Buffer[5] = Data;
    Buffer[6] = 0x03;

    write(localfd, Buffer, 7);
    TAP_Delay(20);

    ret = TRUE;
  }

  //Restore the communication
  *__frontfd = localfd;
  localfd = 0;

  TRACEEXIT();
  return ret;
}
