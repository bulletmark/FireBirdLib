#include                "libFireBird.h"

char                    WDString[8][4] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun", "???"};

char *DayOfWeek(byte WeekDay)
{
  TRACEENTER;

  if(WeekDay > 7) WeekDay = 7;

  TRACEEXIT;
  return WDString[WeekDay];
}
