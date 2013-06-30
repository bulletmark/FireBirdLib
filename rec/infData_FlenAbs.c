#include <stdio.h>
#include <tap.h>
#include "FBLib_rec.h"

extern FILE            *infDatainfFileAbs;

dword infData_FlenAbs(void)
{
  long    tempPos=0;
  long    tempLen=0;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("infData_FlenAbs");
  #endif

  //This may be better with a stat() function
  tempPos = ftell(infDatainfFileAbs);
  fseek(infDatainfFileAbs, 0, SEEK_END);
  tempLen = ftell(infDatainfFileAbs);
  fseek(infDatainfFileAbs, tempPos, SEEK_SET);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return tempLen;
}
