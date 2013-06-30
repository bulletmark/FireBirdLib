#include                "../libFireBird.h"

void Appl_SetIsExternal(bool External)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("Appl_SetIsExternal");
  #endif

  void (*__Appl_SetIsExternal)(bool);

  __Appl_SetIsExternal = (void*)FIS_fwAppl_SetIsExternal();
  if(__Appl_SetIsExternal) __Appl_SetIsExternal(External);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
