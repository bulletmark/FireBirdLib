#include "../libFireBird.h"

inline dword FIS_fwAppl_CheckRecording(void)
{
  TRACEENTER();

  static dword          _Appl_CheckRecording = 0;

  if(!_Appl_CheckRecording)
    _Appl_CheckRecording = TryResolve("_Z19Appl_CheckRecordinghtb");

  TRACEEXIT();
  return _Appl_CheckRecording;
}
