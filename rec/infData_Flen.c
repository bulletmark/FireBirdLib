#include <stdio.h>
#include "FBLib_rec.h"

extern FILE            *infDatainfFile;

dword infData_Flen(void)
{
  long    tempPos=0;
  long    tempLen=0;

  TRACEENTER;

  //This may be better with a stat() function
  tempPos = ftell(infDatainfFile);
  fseek(infDatainfFile, 0, SEEK_END);
  tempLen = ftell(infDatainfFile);
  fseek(infDatainfFile, tempPos, SEEK_SET);

  TRACEEXIT;
  return tempLen;
}
