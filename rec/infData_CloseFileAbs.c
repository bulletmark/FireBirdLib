#include <stdio.h>
#include <tap.h>
#include "FBLib_rec.h"

extern FILE            *infDatainfFileAbs;

void infData_CloseFileAbs(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("infData_CloseFileAbs");
  #endif

  if(infDatainfFileAbs)
  {
    fclose(infDatainfFileAbs);
    infDatainfFileAbs = NULL;
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
