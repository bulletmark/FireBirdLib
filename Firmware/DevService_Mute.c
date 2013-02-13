#include                "../libFireBird.h"

int DevService_Mute(bool Mute)
{
  int (*_DevService_Mute)(bool) = NULL;
  int ret = 0;

  _DevService_Mute = (void*)FIS_fwDevService_Mute();
  if(_DevService_Mute) ret = _DevService_Mute(Mute);

  return ret;
}
