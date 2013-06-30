#include "../libFireBird.h"

inline dword FIS_vhddRecordFile(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vhddRecordFile");
  #endif

  static dword          vhddRecordFile = 0;

  if(!vhddRecordFile)
    vhddRecordFile = (dword)TryResolve("_hddRecordFile");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return vhddRecordFile;
}
