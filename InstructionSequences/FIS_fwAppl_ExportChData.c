#include "libFireBird.h"

inline dword FIS_fwAppl_ExportChData(void)
{
  TRACEENTER();

  static dword          _Appl_ExportChData = 0;

  if(!_Appl_ExportChData)
    _Appl_ExportChData = TryResolve("_Z17Appl_ExportChDataPKc");

  TRACEEXIT();
  return _Appl_ExportChData;
}
