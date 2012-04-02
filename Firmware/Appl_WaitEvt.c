#include                "../libFireBird.h"

dword Appl_WaitEvt(uint Event, uint *a1, uint a2, uint a3, uint Timeout)
{
  dword                 (*__Appl_WaitEvt)(uint, uint *, uint, uint, uint);
  dword                 ret = 0;

  __Appl_WaitEvt = (void*)FIS_fwAppl_WaitEvt();
  if(__Appl_WaitEvt) ret = __Appl_WaitEvt(Event, a1, a2, a3, Timeout);

  return ret;
}
