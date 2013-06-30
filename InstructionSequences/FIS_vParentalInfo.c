#include "../libFireBird.h"

inline dword FIS_vParentalInfo(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vParentalInfo");
  #endif

  static dword          vParentalInfo = 0;
  dword                 *d;

  if(!vParentalInfo)
  {
    d = (dword*)TryResolve("_parentalInfo");
    if(d) vParentalInfo = *d;
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return vParentalInfo;
}
