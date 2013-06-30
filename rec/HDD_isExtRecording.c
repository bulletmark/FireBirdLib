#include                "../libFireBird.h"

bool HDD_isExtRecording(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_isExtRecording");
  #endif

  bool ret;
  bool(*Appl_GetIsExternal)(void);

  ret = FALSE;
  Appl_GetIsExternal = (void*)FIS_fwAppl_GetIsExternal();
  if(Appl_GetIsExternal) ret = Appl_GetIsExternal();

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
