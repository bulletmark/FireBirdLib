#include "../libFireBird.h"

inline dword FIS_vParentalInfo(void)
{
  static dword          vParentalInfo = 0;
  dword                 *d;

  if(!vParentalInfo)
  {
    d = (dword*)TryResolve("_parentalInfo");
    if(d) vParentalInfo = *d;
  }

  return vParentalInfo;
}
