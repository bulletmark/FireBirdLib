#include                "../libFireBird.h"

bool Appl_GetIsExternal(void)
{
  bool(*__Appl_GetIsExternal)(void);
  bool ret = FALSE;

  __Appl_GetIsExternal = (void*)FIS_fwAppl_GetIsExternal();
  if(__Appl_GetIsExternal) ret = __Appl_GetIsExternal();

  return ret;
}
