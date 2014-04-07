#include                "FBLib_time.h"

dword DST_GetNextTransition(byte ruleOrdinal, byte ruleDay, byte ruleMonth, byte ruleHour, byte ruleMin, word ruleYear)
{
  TRACEENTER();

  word        tempDate;
  dword       returnDate;
  word        year;
  byte        month, day, weekDay;

  tempDate = TAP_MakeMjd(ruleYear, ruleMonth, 1);  //Get the first day of the transition month;

  TAP_ExtractMjd(tempDate, &year, &month, &day, &weekDay);

  tempDate = tempDate + ruleDay - weekDay;

  if(weekDay > ruleDay)
  {
    tempDate = tempDate + (ruleOrdinal * 7);
  }
  else
  {
    tempDate = tempDate + ((ruleOrdinal - 1) * 7);
  }

  TAP_ExtractMjd(tempDate, &year, &month, &day, &weekDay);

  if(month != ruleMonth) {tempDate = tempDate - 7;} //An ordinal of 5 can sometimes land in next month

  returnDate = ((tempDate & 0xffff) << 16) | ((ruleHour & 0xff) << 8) | (ruleMin & 0xff);

  TRACEEXIT();
  return returnDate;
}
