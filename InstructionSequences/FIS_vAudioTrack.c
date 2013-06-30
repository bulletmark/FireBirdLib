#include "../libFireBird.h"

inline dword FIS_vAudioTrack(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vAudioTrack");
  #endif

  static tAudioTrk     *AudioTracks = NULL;

  if(!AudioTracks)
    AudioTracks = (tAudioTrk*)TryResolve("_audioTrk");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return (dword)AudioTracks;
}
