#include "../libFireBird.h"

inline dword FIS_vTapSysOsdCtrl(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vTapSysOsdCtrl");
  #endif

  static dword          vtapSysOsdCtrl = 0;

  if(!vtapSysOsdCtrl)
    vtapSysOsdCtrl = TryResolve("_tapSysOsdCtrl");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return vtapSysOsdCtrl;
}
