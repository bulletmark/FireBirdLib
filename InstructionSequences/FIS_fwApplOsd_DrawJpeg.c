#include "../libFireBird.h"

inline dword FIS_fwApplOsd_DrawJpeg(void)
{
  static dword          fwApplOsd_DrawJpeg = 0;

  if (!fwApplOsd_DrawJpeg)
    fwApplOsd_DrawJpeg = TryResolve("_Z16ApplOsd_DrawJpegtjjjjPvjj");

  return fwApplOsd_DrawJpeg;
}
