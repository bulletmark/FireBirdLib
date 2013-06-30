#include <tap.h>
#include "FBLib_rec.h"

bool infData_isAvail(char *infFileName, char *NameTag, dword *PayloadSize)
{
  bool                  ret;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("infData_isAvail");
  #endif

  ret = infData_isAvailAbs(infData_LocToAbs(infFileName), NameTag, PayloadSize);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
