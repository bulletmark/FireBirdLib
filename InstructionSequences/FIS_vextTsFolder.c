#include "../libFireBird.h"

inline dword FIS_vExtTsFolder(void)
{
  static dword          vextTsFolder = 0;

  if(!vextTsFolder) vextTsFolder = (dword)TryResolve("_extTsFolder");

  return vextTsFolder;
}
