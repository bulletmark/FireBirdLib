#include		"libFireBird.h"

byte *GetMacAddress(void)
{
  TRACEENTER();

  byte *ret = (byte*)FIS_vMACAddress();

  TRACEEXIT();
  return ret;
}
