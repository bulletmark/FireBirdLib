#include "FBLib_main.h"

word GetSysID(void)
{
  if (!LibInitialized) InitTAPex();

  return TAP_GetSystemId();
}
