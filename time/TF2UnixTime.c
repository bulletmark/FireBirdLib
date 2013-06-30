#include                "../libFireBird.h"

dword TF2UnixTime(dword TFTimeStamp)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("TF2UnixTime");
  #endif

  dword ret = ((TFTimeStamp >> 16) - 0x9e8b) * 86400 + ((TFTimeStamp >> 8 ) & 0xff) * 3600 + (TFTimeStamp & 0xff) * 60;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
