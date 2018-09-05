#include                <stdio.h>
#include                "FBLib_time.h"

void DST_ProcessRule(char *dstRuleString, dword *dstDate, dword StartDate)
{
  TRACEENTER;

  byte        ruleOrdinal = 0;
  byte        ruleDay = 0;
  byte        ruleMonth = 0;
  byte        ruleHour = 0;
  byte        ruleMin = 0;

  dword       transitionDate = 0;

  if(dstRuleString == NULL)
  {
    if(dstDate) *dstDate = 0;

    TRACEEXIT;
    return;
  }

  sscanf(dstRuleString, "%hhu,%hhu,%hhu,%02hhu:%02hhu", &ruleOrdinal, &ruleDay, &ruleMonth, &ruleHour, &ruleMin);

  //Some basic error checking, but it could be more comprehensive if required.
  if(ruleOrdinal > 5){ruleOrdinal = 5;}
  if(ruleDay > 6){ruleDay = 6;}
  if(ruleMonth > 12){ruleMonth = 12;}

  transitionDate = DST_CalcTransition(ruleOrdinal, ruleDay, ruleMonth, ruleHour, ruleMin, StartDate);

  if(dstDate) *dstDate = transitionDate;

  TRACEEXIT;
}
