#include                "../libFireBird.h"

int Appl_CheckRecording_Tuner(byte TunerIndex, int SvcType, int SvcNum, bool Unknown)
{
  TRACEENTER();

  byte                  (*__Appl_CheckRecording_Tuner)(byte, int, int, bool);
  int                  ret = FALSE;

  __Appl_CheckRecording_Tuner = (void*)FIS_fwAppl_CheckRecording_Tuner();
  if(__Appl_CheckRecording_Tuner) ret = __Appl_CheckRecording_Tuner(TunerIndex, SvcType, SvcNum, Unknown);

  TRACEEXIT();
  return ret;
}
