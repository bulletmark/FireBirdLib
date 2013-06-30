#include		"../libFireBird.h"

byte *GetMacAddress(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("GetMacAddress");
  #endif

  byte *ret = (byte*)FIS_vMACAddress();

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
