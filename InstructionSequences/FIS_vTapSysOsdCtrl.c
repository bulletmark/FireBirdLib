#include "libFireBird.h"

inline dword FIS_vTapSysOsdCtrl(void)
{
  TRACEENTER;

  static dword          vtapSysOsdCtrl = 0;

  if(!vtapSysOsdCtrl)
    vtapSysOsdCtrl = TryResolve("_tapSysOsdCtrl");

  TRACEEXIT;
  return vtapSysOsdCtrl;
}
