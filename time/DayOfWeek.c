#include                "../libFireBird.h"

char                    WDString[8][4] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun", "???"};

char *DayOfWeek(byte WeekDay)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("DayOfWeek");
  #endif

  if(WeekDay > 7) WeekDay = 7;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return WDString[WeekDay];
}
