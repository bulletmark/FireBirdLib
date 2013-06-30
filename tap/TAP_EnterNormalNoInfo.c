#include                "../libFireBird.h"

void TAP_EnterNormalNoInfo(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("TAP_EnterNormalNoInfo");
  #endif

  void (*_EnterNormal)(byte);

  _EnterNormal = (void*)FIS_fwAppl_EnterNormal();
  if(_EnterNormal) _EnterNormal(0);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
