#include "libFireBird.h"

inline dword FIS_vFlashBlockTransponderInfo(void)
{
  TRACEENTER();

  static dword          *vFlashTPInfo = 0;

  if(!vFlashTPInfo)
    vFlashTPInfo = (dword*)TryResolve("_tpInfo");

  TRACEEXIT();
  return (vFlashTPInfo ? *vFlashTPInfo : 0);
}
