#include <string.h>
#include <tap.h>
#include "FBLib_rec.h"

bool infData_GetNameByIndex(char *infFileName, dword NameIndex, char *NameTag)
{
  bool                  ret;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("infData_GetNameByIndex");
  #endif

  ret = infData_GetNameByIndexAbs(infData_LocToAbs(infFileName), NameIndex, NameTag);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
