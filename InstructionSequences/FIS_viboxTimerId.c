#include "libFireBird.h"

inline dword FIS_vIboxTimerId(void)
{
  TRACEENTER;

  static byte   *iboxTimerId = NULL;

  if(!iboxTimerId)
    iboxTimerId = (byte*)TryResolve("_iboxTimerId");

  TRACEEXIT;
  return (dword)iboxTimerId;
}
