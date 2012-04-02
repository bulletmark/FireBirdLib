#include                "../libFireBird.h"

char                    WDString[7][4] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};

char *DayOfWeek(byte WeekDay)
{
  return WDString[WeekDay];
}
