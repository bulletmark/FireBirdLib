#include <stdio.h>
#include <tap.h>
#include "FBLib_rec.h"

FILE                   *infDatainfFileAbs = NULL;

bool infData_OpenFileAbs(char *infFileName)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("infData_OpenFileAbs");
  #endif

  infDatainfFileAbs = fopen(infFileName, "r+");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return (infDatainfFileAbs != NULL);
}
