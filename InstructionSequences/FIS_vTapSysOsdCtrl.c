#include "../libFireBird.h"

inline dword FIS_vTapSysOsdCtrl(void)
{
  static dword          vtapSysOsdCtrl = 0;

  if (!vtapSysOsdCtrl)
    vtapSysOsdCtrl = TryResolve("_tapSysOsdCtrl");

  return vtapSysOsdCtrl;
}
