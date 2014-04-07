#include "../libFireBird.h"

inline dword FIS_vdupEntry(void)
{
  TRACEENTER();

  static dword          vdupEntry = 0;

  if(!vdupEntry)
    vdupEntry = TryResolve("_dupEntry");

  TRACEEXIT();
  return vdupEntry;
}
