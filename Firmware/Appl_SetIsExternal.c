#include                "../libFireBird.h"

void Appl_SetIsExternal(bool External)
{
  TRACEENTER();

  void (*__Appl_SetIsExternal)(bool);

  __Appl_SetIsExternal = (void*)FIS_fwAppl_SetIsExternal();
  if(__Appl_SetIsExternal) __Appl_SetIsExternal(External);

  TRACEEXIT();
}
