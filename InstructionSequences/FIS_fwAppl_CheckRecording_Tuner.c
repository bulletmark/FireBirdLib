#include "libFireBird.h"

inline dword FIS_fwAppl_CheckRecording_Tuner(void)
{
  TRACEENTER();

  static dword          _Appl_CheckRecording_Tuner = 0;

  if(!_Appl_CheckRecording_Tuner)
    _Appl_CheckRecording_Tuner = TryResolve("_Z25Appl_CheckRecording_Tunerhhtb");

  TRACEEXIT();
  return _Appl_CheckRecording_Tuner;
}
