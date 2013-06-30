#include                "../libFireBird.h"

void Appl_RestartTimeShiftSvc(bool p1, dword Block)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("Appl_RestartTimeShiftSvc");
  #endif

  void (*__Appl_RestartTimeShiftSvc)(bool, dword Block);

  __Appl_RestartTimeShiftSvc = (void*)FIS_fwAppl_RestartTimeShiftSvc();
  if(__Appl_RestartTimeShiftSvc) __Appl_RestartTimeShiftSvc(p1, Block);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
