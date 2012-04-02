#include "../libFireBird.h"

inline dword FIS_vAudioTrack(void)
{
  static tAudioTrk     *AudioTracks = NULL;

  if(!AudioTracks) AudioTracks = (tAudioTrk*)TryResolve("_audioTrk");

  return (dword)AudioTracks;
}
