#include                "../libFireBird.h"

byte Appl_StartPlaybackMedia(char const *FileName, unsigned int p2, bool p3, bool ScaleInPip)
{
  byte (*__Appl_StartPlaybackMedia)(char const*, unsigned int, bool, bool);
  byte ret = 0;

  __Appl_StartPlaybackMedia = (void*)FIS_fwAppl_StartPlaybackMedia();
  if(__Appl_StartPlaybackMedia) ret = __Appl_StartPlaybackMedia(FileName, p2, p3, ScaleInPip);

  return ret;
}
