#include                "../libFireBird.h"

dword Appl_WaitEvt(dword Event, dword *a1, dword a2, dword a3, dword Timeout)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("Appl_WaitEvt");
  #endif

  dword                 (*__Appl_WaitEvt)(dword, dword *, dword, dword, dword);
  dword                 ret = 0;

  __Appl_WaitEvt = (void*)FIS_fwAppl_WaitEvt();
  if(__Appl_WaitEvt) ret = __Appl_WaitEvt(Event, a1, a2, a3, Timeout);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
