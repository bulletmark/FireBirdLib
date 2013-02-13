#include "../libFireBird.h"

inline dword FIS_vdupEntry(void)
{
  static dword          vdupEntry = 0;

  if(!vdupEntry) vdupEntry = TryResolve("_dupEntry");
  return (dword)vdupEntry;
}
