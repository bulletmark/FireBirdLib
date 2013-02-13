#include                "../libFireBird.h"

void Appl_SetPlaybackSpeed(byte Mode, int Speed, bool p3)
{
  void (*__Appl_SetPlaybackSpeed)(unsigned char, int, bool);

  __Appl_SetPlaybackSpeed = (void*)FIS_fwAppl_SetPlaybackSpeed();
  if(__Appl_SetPlaybackSpeed) __Appl_SetPlaybackSpeed(Mode, Speed, p3);
}
