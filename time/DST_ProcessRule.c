#include                <stdio.h>
#include                "FBLib_time.h"

void DST_ProcessRule(char *dstRuleString, dword *dstDate, dword StartDate)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("DST_ProcessRule");
  #endif

  byte        ruleOrdinal = 0;
  byte        ruleDay = 0;
  byte        ruleMonth = 0;
  byte        ruleHour = 0;
  byte        ruleMin = 0;

  dword       transitionDate = 0;

  //TAP_PrintNet("Processing DST rule [%s].\r\n\r\n", dstRuleString);

  if(dstRuleString == NULL)
  {
    if(dstDate) *dstDate = 0;

    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return;
  }

  sscanf(dstRuleString, "%hhu,%hhu,%hhu,%02hhu:%02hhu", &ruleOrdinal, &ruleDay, &ruleMonth, &ruleHour, &ruleMin);

  //TAP_PrintNet("DST rule [%s] string parsed.\r\n\r\n", dstRuleString);

  //Some basic error checking, but it could be more comprehensive if required.
  if(ruleOrdinal > 5){ruleOrdinal = 5;}
  if(ruleDay > 6){ruleDay = 6;}
  if(ruleMonth > 12){ruleMonth = 12;}

  //TAP_PrintNet("Ordinal = %d, Day = %d, Month = %d, Hour = %d, Min = %d.\r\n\r\n", ruleOrdinal, ruleDay, ruleMonth, ruleHour, ruleMin);

  transitionDate = DST_CalcTransition(ruleOrdinal, ruleDay, ruleMonth, ruleHour, ruleMin, StartDate);

  //    TAP_ExtractMjd(transitionDate>>16, &year, &month, &day, &weekDay) ;
  //    hour = (transitionDate&0xff00)>>8;
  //    minute = (transitionDate&0xff);
  //
  //    TAP_PrintNet("Next transition at %02d:%02d on %04d/%02d/%02d.\r\n\r\n", hour, minute, year, month, day);
  //    TAP_PrintNet("----------------------------------------------\r\n\r\n");

  if(dstDate) *dstDate = transitionDate;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
