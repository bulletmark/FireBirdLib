#include "../libFireBird.h"

bool HDD_isRecFileName(char *FileName)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_isRecFileName");
  #endif

  bool ret;

  if(FileName && *FileName)
    ret = StringEndsWith(FileName, ".rec") || StringEndsWith(FileName, ".mpg");
  else
    ret = FALSE;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
