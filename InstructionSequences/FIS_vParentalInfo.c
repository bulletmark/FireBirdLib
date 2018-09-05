#include "libFireBird.h"

inline dword FIS_vParentalInfo(void)
{
  TRACEENTER;

  static dword          vParentalInfo = 0;
  dword                 *d;

  if(!vParentalInfo)
  {
    d = (dword*)TryResolve("_parentalInfo");
    if(d) vParentalInfo = *d;
  }

  TRACEEXIT;
  return vParentalInfo;
}
