#include                "../libFireBird.h"

int Appl_CheckRecording(int SvcType, int SvcNum, bool Unknown)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("Appl_CheckRecording");
  #endif

  byte                  (*__Appl_CheckRecording)(int, int, bool);
  int                  ret = FALSE;

  __Appl_CheckRecording = (void*)FIS_fwAppl_CheckRecording();
  if(__Appl_CheckRecording) ret = __Appl_CheckRecording(SvcType, SvcNum, Unknown);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
