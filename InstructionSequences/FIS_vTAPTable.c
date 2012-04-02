#include "../libFireBird.h"

inline dword FIS_vTAPTable(void)
{
  static dword          *vTAP_TableAddress = NULL;

  if(!vTAP_TableAddress) vTAP_TableAddress = (dword*)TryResolve("_tapTask");
  return (dword)vTAP_TableAddress;
}
