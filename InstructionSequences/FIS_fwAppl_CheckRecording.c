#include "../libFireBird.h"

inline dword FIS_fwAppl_CheckRecording(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("_Appl_CheckRecording");
  #endif

  static dword          _Appl_CheckRecording = 0;

  if(!_Appl_CheckRecording)
    _Appl_CheckRecording = TryResolve("_Z19Appl_CheckRecordinghtb");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _Appl_CheckRecording;
}
