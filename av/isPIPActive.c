#include "FBLib_av.h"
#include "../libFireBird.h"

bool isPIPActive(void)
{
  byte                 *_isPipActive;

  _isPipActive = (byte*)FIS_vIsPipActive();

  return _isPipActive ? *_isPipActive : FALSE;
}
