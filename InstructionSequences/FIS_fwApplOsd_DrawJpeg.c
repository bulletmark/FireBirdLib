#include "../libFireBird.h"

inline dword FIS_fwApplOsd_DrawJpeg(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwApplOsd_DrawJpeg");
  #endif

  static dword          fwApplOsd_DrawJpeg = 0;

  if(!fwApplOsd_DrawJpeg)
    fwApplOsd_DrawJpeg = TryResolve("_Z16ApplOsd_DrawJpegtjjjjPvjj");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return fwApplOsd_DrawJpeg;
}
