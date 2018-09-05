#include                "libFireBird.h"

dword Appl_KeyCvt(dword NECKeyCode)
{
  TRACEENTER;

  dword (*__Appl_KeyCvt)(dword NECKeyCode);
  dword ret = 0;

  __Appl_KeyCvt = (void*)FIS_fwAppl_KeyCvt();
  if(__Appl_KeyCvt) ret = __Appl_KeyCvt(NECKeyCode);

  TRACEEXIT;
  return ret;
}
