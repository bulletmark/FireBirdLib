#include                "libFireBird.h"

bool isUTFToppy(void)
{
  TRACEENTER();

  static bool ret = FALSE;
  static bool FirstCall = TRUE;

  if(FirstCall)
  {
    ret = FIS_fwAppl_ConvertToValidUTF8Str() != 0;
    FirstCall= FALSE;
  }

  TRACEEXIT();
  return ret;
}
