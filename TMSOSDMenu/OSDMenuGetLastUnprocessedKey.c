#include                "FBLib_TMSOSDMenu.h"

dword OSDMenuGetLastUnprocessedKey(void)
{
  TRACEENTER();

  dword                 ret;

  ret = LastUnprocessedOSDMenuKey;
  LastUnprocessedOSDMenuKey = 0;

  TRACEEXIT();
  return ret;
}
