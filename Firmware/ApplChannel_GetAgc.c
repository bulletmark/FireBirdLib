#include                "libFireBird.h"

byte ApplChannel_GetAgc(byte TunerIndex, byte *AGC)
{
  TRACEENTER;

  byte                  (*__ApplChannel_GetAgc)(byte, byte *);
  byte                  ret = 0;

  __ApplChannel_GetAgc = (void*)FIS_fwApplChannel_GetAgc();
  if(__ApplChannel_GetAgc) ret = __ApplChannel_GetAgc(TunerIndex, AGC);

  TRACEEXIT;
  return ret;
}
