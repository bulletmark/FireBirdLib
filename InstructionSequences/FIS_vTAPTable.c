#include "libFireBird.h"

inline dword FIS_vTAPTable(void)
{
  TRACEENTER();

  static dword          *vTAP_TableAddress = NULL;

  if(!vTAP_TableAddress) vTAP_TableAddress = (dword*)TryResolve("_tapTask");

  TRACEEXIT();
  return (dword)vTAP_TableAddress;
}
