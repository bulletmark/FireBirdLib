#include      <string.h>
#include      "FBLib_av.h"
#include      "../libFireBird.h"

tAudioTrk *AudioTrackInfo(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("AudioTrackInfo");
  #endif

  tAudioTrk  *p;

  p = (tAudioTrk*)FIS_vAudioTrack();

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return p;
}
