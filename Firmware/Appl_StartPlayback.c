#include                "../libFireBird.h"

byte Appl_StartPlayback(char *FileName, unsigned int p2, bool p3, bool ScaleInPip)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("Appl_StartPlayback");
  #endif

  byte (*__Appl_StartPlayback)(char const*, unsigned int, bool, bool);
  byte ret = 0;

  __Appl_StartPlayback = (void*)FIS_fwAppl_StartPlayback();
  if(__Appl_StartPlayback) ret = __Appl_StartPlayback(FileName, p2, p3, ScaleInPip);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
