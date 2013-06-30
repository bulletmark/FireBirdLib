#include "../libFireBird.h"

inline dword FIS_vExtTsFolder(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vExtTsFolder");
  #endif

  static dword          vextTsFolder = 0;

  if(!vextTsFolder)
    vextTsFolder = (dword)TryResolve("_extTsFolder");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return vextTsFolder;
}
