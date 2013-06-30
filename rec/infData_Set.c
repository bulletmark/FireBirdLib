#include <string.h>
#include <tap.h>
#include "FBLib_rec.h"

bool infData_Set(char *infFileName, char *NameTag, dword PayloadSize, byte *Payload)
{
  bool                  ret;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("infData_Set");
  #endif

  ret = infData_SetAbs(infData_LocToAbs(infFileName), NameTag, PayloadSize, Payload);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
