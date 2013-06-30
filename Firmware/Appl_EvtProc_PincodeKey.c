#include                "../libFireBird.h"

bool Appl_EvtProc_PincodeKey(dword p1, dword p2)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("Appl_EvtProc_PincodeKey");
  #endif

  bool (*__Appl_EvtProc_PincodeKey)(dword, dword);
  bool ret = FALSE;

  __Appl_EvtProc_PincodeKey = (void*)FIS_fwAppl_EvtProc_PincodeKey();
  if(__Appl_EvtProc_PincodeKey) ret = __Appl_EvtProc_PincodeKey(p1, p2);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
