#include <string.h>
#include "../libFireBird.h"

bool HDD_TAP_CheckCollision(void)
{
  TRACEENTER();

  char                 *myTAPFileName, *TAPFileName;
  dword                *pCurrentTAPIndex, myTAPIndex;
  dword                 i;
  bool                  TAPCollision;

  TAPCollision = FALSE;

  pCurrentTAPIndex = (dword*)FIS_vCurTapTask();
  if(pCurrentTAPIndex)
  {
    //Get the path to myself
    myTAPIndex = *pCurrentTAPIndex;
    if(HDD_TAP_GetFileNameByIndex(myTAPIndex, &myTAPFileName) && myTAPFileName)
    {
      //Check all other TAPs
      for(i = 0; i < 16; i++)
        if((i != myTAPIndex) && HDD_TAP_GetFileNameByIndex(i, &TAPFileName) && TAPFileName && (strcmp(TAPFileName, myTAPFileName) == 0))
        {
          TAPCollision = TRUE;
          break;
        }
    }
  }

  TRACEEXIT();
  return TAPCollision;
}
