#include                "../libFireBird.h"

int Appl_CheckRecording(int SvcType, int SvcNum, bool Unknown)
{
  byte                  (*__Appl_CheckRecording)(int, int, bool);
  int                  ret = FALSE;

  __Appl_CheckRecording = (void*)FIS_fwAppl_CheckRecording();
  if(__Appl_CheckRecording) ret = __Appl_CheckRecording(SvcType, SvcNum, Unknown);

  return ret;
}
