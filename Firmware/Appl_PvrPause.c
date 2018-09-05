#include                "libFireBird.h"

void Appl_PvrPause(bool p1)
{
  TRACEENTER;

  void (*__Appl_PvrPause)(bool);

  __Appl_PvrPause = (void*)FIS_fwAppl_PvrPause();
  if(__Appl_PvrPause) __Appl_PvrPause(p1);

  TRACEEXIT;
}
