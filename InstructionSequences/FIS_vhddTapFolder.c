#include "../libFireBird.h"

inline dword FIS_vHddTapFolder(void)
{
  TRACEENTER();

  static dword          _hddTapFolder = 0;

  if(!_hddTapFolder)
    _hddTapFolder = TryResolve("_hddTapFolder");

  TRACEEXIT();
  return _hddTapFolder;
}
