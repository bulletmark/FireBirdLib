#include                "libFireBird.h"

dword TF2UnixTime(dword TFTimeStamp)
{
  TRACEENTER();

  dword ret = ((TFTimeStamp >> 16) - 0x9e8b) * 86400 + ((TFTimeStamp >> 8 ) & 0xff) * 3600 + (TFTimeStamp & 0xff) * 60;

  TRACEEXIT();
  return ret;
}
