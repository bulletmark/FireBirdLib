#include                <stdio.h>
#include                "libFireBird.h"

char *TimeFormat(dword DateTime, byte Sec, eTimeStampFormat TimeStampFormat, char *Result)
{
  TRACEENTER;

  word                  Mjd, Year;
  byte                  Month, Day, WeekDay, Hour, Min;

  if(Result)
  {
    Mjd  = MJD    (DateTime);
    Hour = HOUR   (DateTime);
    Min  = MINUTE (DateTime);
    TAP_ExtractMjd(Mjd, &Year, &Month, &Day, &WeekDay);
    if(Mjd == 0)
    {
      Year = 0;
      Month = 0;
      Day = 0;
      WeekDay = 0;
    }

    switch(TimeStampFormat)
    {
      case TIMESTAMP_HM     : TAP_SPrint(Result, "%02d:%02d", Hour, Min); break;
      case TIMESTAMP_HMS    : TAP_SPrint(Result, "%02d:%02d:%02d", Hour, Min, Sec); break;
      case TIMESTAMP_YMD    : TAP_SPrint(Result, "%02d-%02d-%02d", Year, Month, Day); break;
      case TIMESTAMP_YMDHM  : TAP_SPrint(Result, "%04d-%02d-%02d %02d:%02d", Year, Month, Day, Hour, Min); break;
      case TIMESTAMP_YMDHMS : TAP_SPrint(Result, "%04d-%02d-%02d %02d:%02d:%02d", Year, Month, Day, Hour, Min, Sec); break;
      case TIMESTAMP_FNYMDHM: TAP_SPrint(Result, "%04d%02d%02d_%02d%02d", Year, Month, Day, Hour, Min); break;
      default               : Result[0] = '\0'; break;
    }
  }

  TRACEEXIT;
  return Result;
}
