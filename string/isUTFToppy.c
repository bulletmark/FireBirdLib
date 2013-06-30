#include                "../libFireBird.h"

bool isUTFToppy(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("isUTFToppy");
  #endif

  static bool ret = FALSE;
  static bool FirstCall = TRUE;

  if(FirstCall)
  {
    ret = FIS_fwAppl_ConvertToValidUTF8Str() != 0;
    FirstCall= FALSE;
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
