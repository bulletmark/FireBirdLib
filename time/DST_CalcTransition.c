#include                "FBLib_time.h"

dword DST_CalcTransition(byte ruleOrdinal, byte ruleDay, byte ruleMonth, byte ruleHour, byte ruleMin, dword StartDate)
{
  TRACEENTER;

  word        year;
  byte        month, day, weekDay;
  dword       toppyNow, workingDate;

  if(StartDate == 0)
    toppyNow = Now(NULL);
  else
    toppyNow = StartDate;

  TAP_ExtractMjd(toppyNow >> 16, &year, &month, &day, &weekDay);

  //If the transition month is less than the current month, then the transition must be next year.
  if(ruleMonth < month) year++;

  workingDate = DST_GetNextTransition(ruleOrdinal, ruleDay, ruleMonth, ruleHour, ruleMin, year);

  //If the result is still in the past, add a year and try again
  //This would normally happen if you are still in the transition month, but past the transition date/time.
  if(workingDate < toppyNow)
  {
    year++;
    workingDate = DST_GetNextTransition(ruleOrdinal, ruleDay, ruleMonth, ruleHour, ruleMin, year);
  }

  TRACEEXIT;
  return workingDate;
}
