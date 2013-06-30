#include                "../libFireBird.h"

int StringDBCountRecords(tStringDB *StringDB)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("StringDBCountRecords");
  #endif

  int                   Cnt;
  char                 *p;

  if(!StringDB)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return 0;
  }

  p = StringDB->DB;
  if(!p)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return 0;
  }

  Cnt = 0;
  while(*p)
  {
    Cnt++;
    while(*p)
    {
      p++;
    }
    p++;
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return Cnt;
}
