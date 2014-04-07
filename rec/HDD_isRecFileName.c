#include "../libFireBird.h"

bool HDD_isRecFileName(char *FileName)
{
  TRACEENTER();

  bool ret;

  if(FileName && *FileName)
    ret = StringEndsWith(FileName, ".rec") || StringEndsWith(FileName, ".mpg");
  else
    ret = FALSE;

  TRACEEXIT();
  return ret;
}
