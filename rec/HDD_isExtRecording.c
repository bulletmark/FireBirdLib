#include                "libFireBird.h"

bool HDD_isExtRecording(void)
{
  TRACEENTER();

  bool ret;
  bool(*Appl_GetIsExternal)(void);

  ret = FALSE;
  Appl_GetIsExternal = (void*)FIS_fwAppl_GetIsExternal();
  if(Appl_GetIsExternal) ret = Appl_GetIsExternal();

  TRACEEXIT();
  return ret;
}
