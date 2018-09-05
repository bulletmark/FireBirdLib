#include "libFireBird.h"

inline dword FIS_vAudioTrack(void)
{
  TRACEENTER;

  static tAudioTrk     *AudioTracks = NULL;

  if(!AudioTracks)
    AudioTracks = (tAudioTrk*)TryResolve("_audioTrk");

  TRACEEXIT;
  return (dword)AudioTracks;
}
