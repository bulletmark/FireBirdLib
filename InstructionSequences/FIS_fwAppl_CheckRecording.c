#include "../libFireBird.h"

inline dword FIS_fwAppl_CheckRecording(void)
{
  static dword          _Appl_CheckRecording = 0;

  if (!_Appl_CheckRecording)
    _Appl_CheckRecording = TryResolve("_Z19Appl_CheckRecordinghtb");

  return _Appl_CheckRecording;
}
