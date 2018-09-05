#include "libFireBird.h"

dword Now(byte *Sec)
{
  TRACEENTER;

  word      MJD;
  byte      Hour, Min, DummySec;
  dword     ret;

  TAP_GetTime(&MJD, &Hour, &Min, (Sec != NULL) ? Sec : &DummySec);
  ret = DATE(MJD, Hour, Min);

  TRACEEXIT;
  return ret;
}
