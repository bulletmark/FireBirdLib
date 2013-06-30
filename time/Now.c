#include "../libFireBird.h"

dword Now(byte *Sec)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("Now");
  #endif

  word      MJD;
  byte      Hour, Min, DummySec;
  dword     ret;

  TAP_GetTime(&MJD, &Hour, &Min, (Sec != NULL) ? Sec : &DummySec);
  ret = DATE(MJD, Hour, Min);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
