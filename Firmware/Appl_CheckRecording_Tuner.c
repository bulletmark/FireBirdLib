#include                "../libFireBird.h"

int Appl_CheckRecording_Tuner(byte TunerIndex, int SvcType, int SvcNum, bool Unknown)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("Appl_CheckRecording_Tuner");
  #endif

  byte                  (*__Appl_CheckRecording_Tuner)(byte, int, int, bool);
  int                  ret = FALSE;

  __Appl_CheckRecording_Tuner = (void*)FIS_fwAppl_CheckRecording_Tuner();
  if(__Appl_CheckRecording_Tuner) ret = __Appl_CheckRecording_Tuner(TunerIndex, SvcType, SvcNum, Unknown);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
