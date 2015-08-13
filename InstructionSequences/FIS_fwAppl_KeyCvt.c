#include "../libFireBird.h"

inline dword FIS_fwAppl_KeyCvt(void)
{
  TRACEENTER();

  static dword          _Appl_KeyCvt = 0;

  if(!_Appl_KeyCvt)
    _Appl_KeyCvt = TryResolve("_Z11Appl_KeyCvtj");

  TRACEEXIT();
  return _Appl_KeyCvt;
}
