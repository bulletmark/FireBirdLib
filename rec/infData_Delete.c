#include <tap.h>
#include "FBLib_rec.h"

bool infData_Delete(char *infFileName, char *NameTag)
{
  bool                  ret;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("infData_Delete");
  #endif

  ret = infData_DeleteAbs(infData_LocToAbs(infFileName), NameTag);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
