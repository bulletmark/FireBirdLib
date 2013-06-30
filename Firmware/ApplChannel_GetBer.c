#include                "../libFireBird.h"

byte ApplChannel_GetBer(byte TunerIndex, byte *BER)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("ApplChannel_GetBer");
  #endif

  byte                  (*__ApplChannel_GetBer)(byte, byte *);
  byte                  ret = 0;

  __ApplChannel_GetBer = (void*)FIS_fwApplChannel_GetBer();
  if(__ApplChannel_GetBer) ret = __ApplChannel_GetBer(TunerIndex, BER);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
