#include <tap.h>
#include "FBLib_rec.h"

bool infData_Get(char *infFileName, char *NameTag, dword *PayloadSize, byte **Payload)
{
  bool                  ret;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("infData_Get");
  #endif

  ret = infData_GetAbs(infData_LocToAbs(infFileName), NameTag, PayloadSize, Payload);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
