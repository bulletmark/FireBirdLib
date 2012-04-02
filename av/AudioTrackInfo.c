#include      <string.h>
#include      "FBLib_av.h"
#include      "../libFireBird.h"

tAudioTrk *AudioTrackInfo(void)
{
  return (tAudioTrk*)FIS_vAudioTrack();
}
