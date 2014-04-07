#include "../libFireBird.h"

inline dword FIS_vTempRecSlot(void)
{
  TRACEENTER();

  static dword          vTempRecSlot = 0;

  if(!vTempRecSlot)
    vTempRecSlot = TryResolve("_tempRecSlot");

  TRACEEXIT();
  return vTempRecSlot;
}
