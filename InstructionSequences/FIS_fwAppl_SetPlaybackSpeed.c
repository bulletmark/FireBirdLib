#include "../libFireBird.h"

inline dword FIS_fwAppl_SetPlaybackSpeed(void)
{
  TRACEENTER();

  static dword          _Appl_SetPlaybackSpeed = 0;

  if(!_Appl_SetPlaybackSpeed)
    _Appl_SetPlaybackSpeed = TryResolve("_Z21Appl_SetPlaybackSpeedhib");

  TRACEEXIT();
  return _Appl_SetPlaybackSpeed;
}
