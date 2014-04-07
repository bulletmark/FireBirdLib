#include      <string.h>
#include      "FBLib_av.h"
#include      "../libFireBird.h"

tAudioTrk *AudioTrackInfo(void)
{
  TRACEENTER();

  tAudioTrk  *p;

  p = (tAudioTrk*)FIS_vAudioTrack();

  TRACEEXIT();

  return p;
}
