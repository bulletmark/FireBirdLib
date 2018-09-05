#include <string.h>
#include "FBLib_tap.h"

bool HDD_TAP_CheckCollision(void)
{
  TRACEENTER;

  char                 *myTAPFileName, *TAPFileName;
  dword                 i;
  bool                  TAPCollision;

  if(!LibInitialized && !InitTAPex())
  {
    TRACEEXIT;
    return FALSE;
  }

  TAPCollision = FALSE;

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

  TRACEEXIT;
  return TAPCollision;
}
