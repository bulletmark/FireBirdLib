#include <string.h>
#include "../libFireBird.h"

bool HDD_TAP_CheckCollision(void)
{
  TRACEENTER();

  char                 *myTAPFileName, *TAPFileName;
  dword                 i;
  bool                  TAPCollision;

  TAPCollision = FALSE;

  //The curTapTask variable is not thread safe. Call InitTAPex() if this function will be called from a sub thread
  if(TAP_TableIndex == 0xffffffff)
  {
    dword *curTapTask;

    curTapTask = (dword*)FIS_vCurTapTask();
    if(!curTapTask)
    {
      TRACEEXIT();
      return FALSE;
    }
    TAP_TableIndex = *curTapTask;
  }

  //Get the path to myself
  if(HDD_TAP_GetFileNameByIndex(TAP_TableIndex, &myTAPFileName) && myTAPFileName)
  {
    //Check all other TAPs
    for(i = 0; i < 16; i++)
      if((i != TAP_TableIndex) && HDD_TAP_GetFileNameByIndex(i, &TAPFileName) && TAPFileName && (strcmp(TAPFileName, myTAPFileName) == 0))
      {
        TAPCollision = TRUE;
        break;
      }
  }

  TRACEEXIT();
  return TAPCollision;
}
