#include "../libFireBird.h"

inline dword FIS_vHddTsFolder(void)
{
  TRACEENTER();

  static dword          _hddTsFolder = 0;

  if(!_hddTsFolder)
    _hddTsFolder = TryResolve("_hddTsFolder");

  TRACEEXIT();
  return _hddTsFolder;
}
