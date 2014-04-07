#include                <string.h>
#include                "tap.h"
#include                "libFireBird.h"

#define PROGRAM_NAME    "EPGPoolTest"
#define VERSION         "V0.3"

TAP_ID                  (0x8E0A4265);
TAP_PROGRAM_NAME        (PROGRAM_NAME" "VERSION);
TAP_AUTHOR_NAME         ("FireBird");
TAP_DESCRIPTION         ("EPGPoolTest");
TAP_ETCINFO             (__DATE__);

dword TAP_EventHandler(word event, dword param1, dword param2)
{
  (void) event;
  (void) param2;

  return param1;
}

void BruteForceTimeZoneCheck(void)
{
  dword   StartTime, EndTime, CurrentTime;
  dword   CalcLocalTime, CalcUTCTime;
  short   Offset1, Offset2;

  StartTime = TAP_MakeMjd(2013, 1, 1) << 16;
  EndTime = TAP_MakeMjd(2014, 1, 1) << 16;

  CurrentTime = StartTime;
  DST_SetDSTRule(DSTR_Europe);
  while(CurrentTime < EndTime)
  {
    CalcLocalTime = UTC2LocalTime(CurrentTime, &Offset1);
    CalcUTCTime = LocalTime2UTC(CalcLocalTime, &Offset2);

    TAP_PrintNet("%s (UTC)", TimeFormat(CurrentTime, 0, TIMESTAMP_YMDHM));
    TAP_PrintNet(" -> %s (UTC+%d)", TimeFormat(CalcLocalTime, 0, TIMESTAMP_YMDHM), Offset1);
    TAP_PrintNet(" -> %s (Local-%d)", TimeFormat(CalcUTCTime, 0, TIMESTAMP_YMDHM), Offset2);

    if(CurrentTime != CalcUTCTime) TAP_PrintNet("  UTC time mismatch!!!");

    TAP_PrintNet("\n");

    CurrentTime = AddTime(CurrentTime, 30);
  }
}

void Test1(void)
{
  TYPE_EPGInfo      EPGData;
  dword             NrEntries, i;

  TAP_PrintNet("Test 1: print all available data\n");

  EPGInfo_FilterReset();

  //EPGInfo_FilterChannelByIndex(0, 1032);

  NrEntries = EPGInfo_FindFirst(&EPGData);
  TAP_PrintNet("  %d entries cached\n", NrEntries);
  for(i = 0; i < NrEntries; i++)
  {
    TAP_PrintNet("  %s: (%d) %s (%d')\n", TimeFormat(EPGData.StartTime, 0, TIMESTAMP_YMDHM), EPGData.TimeZone, EPGData.EventName, EPGData.duration);
    EPGInfo_FindNext(&EPGData);
  }
  EPGInfo_Free();
  TAP_PrintNet("\n");
}

void Test2(void)
{
  TYPE_EPGInfo      EPGData;
  dword             NrEntries, i;
  int               SvcType, SvcNum;

  TAP_PrintNet("Test 2: print the events of the current channel +- 3h\n");

  EPGInfo_FilterReset();
  EPGInfo_FilterTime(AddTime(Now(NULL), -180), AddTime(Now(NULL), 180));
  TAP_Channel_GetCurrent(&SvcType, &SvcNum);
  EPGInfo_FilterChannelByIndex(SvcType, SvcNum, FALSE);
  NrEntries = EPGInfo_FindFirst(&EPGData);
  TAP_PrintNet("  %d entries cached\n", NrEntries);
  for(i = 0; i < NrEntries; i++)
  {
    TAP_PrintNet("  %s: (%d) %s (%d')\n", TimeFormat(EPGData.StartTime, 0, TIMESTAMP_YMDHM), EPGData.TimeZone, EPGData.EventName, EPGData.duration);
    EPGInfo_FindNext(&EPGData);
  }
  EPGInfo_Free();
  TAP_PrintNet("\n");
}

void Test3(void)
{
  TYPE_EPGInfo      EPGData;
  dword             NrEntries, i;

  TAP_PrintNet("Test 3: all events with a duration between 60 and 70 minutes\n");

  EPGInfo_FilterReset();
  EPGInfo_FilterDuration(60, 70);
  NrEntries = EPGInfo_FindFirst(&EPGData);
  TAP_PrintNet("  %d entries cached\n", NrEntries);
  for(i = 0; i < NrEntries; i++)
  {
    TAP_PrintNet("  %s: (%d) %s (%d')\n", TimeFormat(EPGData.StartTime, 0, TIMESTAMP_YMDHM), EPGData.TimeZone, EPGData.EventName, EPGData.duration);
    EPGInfo_FindNext(&EPGData);
  }
  EPGInfo_Free();
  TAP_PrintNet("\n");
}

bool CallbackFunction(TYPE_EPGInfo *EvtInfo)
{
  return EvtInfo->RunningStatus == RST_Running;
}

void Test4(void)
{
  TYPE_EPGInfo      EPGData;
  dword             NrEntries, i;

  TAP_PrintNet("Test 4: use a callback function. It will return TRUE for all currently running programmes (running status = running)\n");

  EPGInfo_FilterReset();
  EPGInfo_FilterCallback(CallbackFunction);

  NrEntries = EPGInfo_FindFirst(&EPGData);
  TAP_PrintNet("  %d entries cached\n", NrEntries);
  for(i = 0; i < NrEntries; i++)
  {
    TAP_PrintNet("  %s: (%d) %s (%d')\n", TimeFormat(EPGData.StartTime, 0, TIMESTAMP_YMDHM), EPGData.TimeZone, EPGData.EventName, EPGData.duration);
    EPGInfo_FindNext(&EPGData);
  }
  EPGInfo_Free();
  TAP_PrintNet("\n");
}

void Test5(void)
{
  TYPE_EPGInfo      EPGData;
  dword             NrEntries, i;
  int               SvcType, SvcNum;

  TAP_PrintNet("Test 5a: read all events for the current channel, print the first 10 and then reverse over the previous 5 events\n");

  EPGInfo_FilterReset();
  TAP_Channel_GetCurrent(&SvcType, &SvcNum);
  EPGInfo_FilterChannelByIndex(SvcType, SvcNum, FALSE);
  NrEntries = EPGInfo_FindFirst(&EPGData);
  TAP_PrintNet("  %d entries cached\n", NrEntries);
  for(i = 0; i < 10; i++)
  {
    TAP_PrintNet("  %s: (%d) %s (%d')\n", TimeFormat(EPGData.StartTime, 0, TIMESTAMP_YMDHM), EPGData.TimeZone, EPGData.EventName, EPGData.duration);
    EPGInfo_FindNext(&EPGData);
  }

  TAP_PrintNet("----------------\n");

  //EPGInfo_FindPrev(&EPGData);
  for(i = 0; i < 5; i++)
  {
    EPGInfo_FindPrev(&EPGData);
    TAP_PrintNet("  %s: (%d) %s (%d')\n", TimeFormat(EPGData.StartTime, 0, TIMESTAMP_YMDHM), EPGData.TimeZone, EPGData.EventName, EPGData.duration);
    //EPGInfo_FindPrev(&EPGData);
  }

  TAP_PrintNet("\nTest 5b: get the first event again\n");
  EPGInfo_FindItem(&EPGData, 0, FALSE);
  TAP_PrintNet("  %s: (%d) %s (%d')\n", TimeFormat(EPGData.StartTime, 0, TIMESTAMP_YMDHM), EPGData.TimeZone, EPGData.EventName, EPGData.duration);

  TAP_PrintNet("\nTest 5c: get the last event again, resetting the current location.\n");
  EPGInfo_FindItem(&EPGData, NrEntries - 1, TRUE);
  TAP_PrintNet("  %s: (%d) %s (%d')\n", TimeFormat(EPGData.StartTime, 0, TIMESTAMP_YMDHM), EPGData.TimeZone, EPGData.EventName, EPGData.duration);

  TAP_PrintNet("\nTest 5d: read back through the last 5 again [Firmware DST Rules].\n");

  DST_SetDSTRule(DSTR_Firmware);

  for(i = 0; i < 5; i++)
  {
    EPGInfo_FindPrev(&EPGData);
    TAP_PrintNet("  %s: (%d) %s (%d')\n", TimeFormat(EPGData.StartTime, 0, TIMESTAMP_YMDHM), EPGData.TimeZone, EPGData.EventName, EPGData.duration);
  }
  EPGInfo_Free();
}

int TAP_Main(void)
{
  //DST_SetDSTRule(DSTR_Manual);
  DST_SetDSTRule(DSTR_Europe);

  TAP_PrintNet("-----------------------\n");
  Test1();
  Test2();
  Test3();
  Test4();
  Test5();

  //BruteForceTimeZoneCheck();

  TAP_PrintNet("\n");

  return 0;
}
