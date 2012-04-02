#include "../libFireBird.h"

inline dword FIS_vIboxTimerId(void)
{
  static byte   *iboxTimerId = NULL;

  if(!iboxTimerId) iboxTimerId = (byte*)TryResolve("_iboxTimerId");

  return (dword)iboxTimerId;
}
