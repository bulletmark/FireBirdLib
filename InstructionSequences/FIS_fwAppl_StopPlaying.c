#include "libFireBird.h"

inline dword FIS_fwAppl_StopPlaying(void)
{
  TRACEENTER;

  static dword          _Appl_StopPlaying = 0;

  if(!_Appl_StopPlaying)
    _Appl_StopPlaying = TryResolve("_Z16Appl_StopPlayingv");

  TRACEEXIT;
  return _Appl_StopPlaying;
}
