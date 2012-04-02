#include                "../libFireBird.h"

byte ApplChannel_GetAgc(unsigned char TunerIndex, unsigned char *AGC)
{
  byte                  (*__ApplChannel_GetAgc)(unsigned char, unsigned char *);
  byte                  ret = 0;

  __ApplChannel_GetAgc = (void*)FIS_fwApplChannel_GetAgc();
  if(__ApplChannel_GetAgc) ret = __ApplChannel_GetAgc(TunerIndex, AGC);

  return ret;
}
