#include "../libFireBird.h"

bool TAP_GetSysOsdControl(TYPE_TapSysOsdId osdId)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("TAP_GetSysOsdControl");
  #endif

  dword                *__tapSysOsdCtrl = NULL;

  __tapSysOsdCtrl = (dword*)FIS_vTapSysOsdCtrl();
  if(!__tapSysOsdCtrl)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  switch(osdId)
  {
    case SYSOSD_InfoBox:        return *__tapSysOsdCtrl & 0x00000001;
    case SYSOSD_PvrInfo:        return *__tapSysOsdCtrl & 0x00000100;
    case SYSOSD_VolumeBar:      return *__tapSysOsdCtrl & 0x00010000;
    case SYSOSD_ServiceStatus:  return *__tapSysOsdCtrl & 0x01000000;
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return FALSE;
}
