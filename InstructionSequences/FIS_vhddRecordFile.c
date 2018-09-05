#include "libFireBird.h"

inline dword FIS_vhddRecordFile(void)
{
  TRACEENTER;

  static dword          vhddRecordFile = 0;

  if(!vhddRecordFile)
    vhddRecordFile = (dword)TryResolve("_hddRecordFile");

  TRACEEXIT;
  return vhddRecordFile;
}
