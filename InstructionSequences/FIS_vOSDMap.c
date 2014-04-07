#include "../libFireBird.h"

inline dword FIS_vOsdMap(void)
{
  TRACEENTER();

  static dword          vOSDMap = 0;

  if(!vOSDMap)
    vOSDMap = TryResolve("_osdInfo");

  TRACEEXIT();
  return vOSDMap;
}
