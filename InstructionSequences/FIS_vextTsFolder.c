#include "libFireBird.h"

inline dword FIS_vExtTsFolder(void)
{
  TRACEENTER;

  static dword          vextTsFolder = 0;

  if(!vextTsFolder)
    vextTsFolder = (dword)TryResolve("_extTsFolder");

  TRACEEXIT;
  return vextTsFolder;
}
