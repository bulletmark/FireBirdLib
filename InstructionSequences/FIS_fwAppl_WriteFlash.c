#include "../libFireBird.h"

inline dword FIS_fwAppl_WriteFlash(void)
{
  static dword          _Appl_WriteFlash = 0;

  if (!_Appl_WriteFlash)
    _Appl_WriteFlash = TryResolve("_Z15Appl_WriteFlashb");

  return _Appl_WriteFlash;
}
