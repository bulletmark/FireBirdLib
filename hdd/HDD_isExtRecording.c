#include                "../libFireBird.h"

bool HDD_isExtRecording(void)
{
  bool(*Appl_GetIsExternal)(void);

  Appl_GetIsExternal = (void*)FIS_fwAppl_GetIsExternal();
  if(!Appl_GetIsExternal) return FALSE;

  return Appl_GetIsExternal();
}
