#include "libFireBird.h"

bool TAP_GetSysOsdControl(TYPE_TapSysOsdId osdId)
{
  TRACEENTER();

  dword                *__tapSysOsdCtrl = NULL;

  __tapSysOsdCtrl = (dword*)FIS_vTapSysOsdCtrl();
  if(!__tapSysOsdCtrl)
  {
    TRACEEXIT();
    return FALSE;
  }

  switch(osdId)
  {
    case SYSOSD_InfoBox:        return (*__tapSysOsdCtrl & 0x00000001) != 0;
    case SYSOSD_PvrInfo:        return (*__tapSysOsdCtrl & 0x00000100) != 0;
    case SYSOSD_VolumeBar:      return (*__tapSysOsdCtrl & 0x00010000) != 0;
    case SYSOSD_ServiceStatus:  return (*__tapSysOsdCtrl & 0x01000000) != 0;
  }

  TRACEEXIT();
  return FALSE;
}
