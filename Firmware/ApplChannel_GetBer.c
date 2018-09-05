#include                "libFireBird.h"

byte ApplChannel_GetBer(byte TunerIndex, byte *BER)
{
  TRACEENTER;

  byte                  (*__ApplChannel_GetBer)(byte, byte *);
  byte                  ret = 0;

  __ApplChannel_GetBer = (void*)FIS_fwApplChannel_GetBer();
  if(__ApplChannel_GetBer) ret = __ApplChannel_GetBer(TunerIndex, BER);

  TRACEEXIT;
  return ret;
}
