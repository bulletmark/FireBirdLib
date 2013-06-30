#include "../libFireBird.h"

inline dword FIS_fwAppl_ExportChData(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwAppl_ExportChData");
  #endif

  static dword          _Appl_ExportChData = 0;

  if(!_Appl_ExportChData)
    _Appl_ExportChData = TryResolve("_Z17Appl_ExportChDataPKc");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _Appl_ExportChData;
}
