#include                "../libFireBird.h"

byte ApplChannel_GetBer(unsigned char TunerIndex, unsigned char *BER)
{
  byte                  (*__ApplChannel_GetBer)(unsigned char, unsigned char *);
  byte                  ret = 0;

  __ApplChannel_GetBer = (void*)FIS_fwApplChannel_GetBer();
  if(__ApplChannel_GetBer) ret = __ApplChannel_GetBer(TunerIndex, BER);

  return ret;
}
