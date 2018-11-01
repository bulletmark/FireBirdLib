#include "libFireBird.h"

inline dword FIS_fwAppl_GetStreamFormat(void)
{
  TRACEENTER();

  static dword          _Appl_GetStreamFormat = 0;

  if(!_Appl_GetStreamFormat)
    _Appl_GetStreamFormat = TryResolve("_Z20Appl_GetStreamFormath");

  TRACEEXIT();
  return _Appl_GetStreamFormat;
}
