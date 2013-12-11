#include                "FBLib_time.h"

void DST_GetTransitions_Manual(dword *DSTStartUTC, dword *DSTEndUTC)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("DST_GetTransitions_Manual");
  #endif

  if(DSTStartUTCsaved != 0 && DSTEndUTCsaved != 0)
  {
    if(Now(NULL) < DSTStartUTCsaved && Now(NULL) < DSTStartUTCsaved)
    {
      if(DSTStartUTC) *DSTStartUTC = DSTStartUTCsaved;
      if(DSTEndUTC) *DSTEndUTC = DSTEndUTCsaved;

      #ifdef DEBUG_FIREBIRDLIB
        CallTraceExit(NULL);
      #endif

      return;
    }
  }

  char                  s[24];
  short                 StdOffset;

  //Get both transition times from DST.ini
  HDD_TAP_PushDir();
  HDD_ChangeDir("/ProgramFiles/Settings");
  if(INIOpenFile(MANUALDSTINI, "") > INILOCATION_NewFile)
  {
    GetCurrentTimeZone(&StdOffset, NULL);

    if(DSTStartUTC)
    {
      //TAP_PrintNet("Getting start rule.\n");
      INIGetString("DSTStartRule", s, "", sizeof(s) - 1);
      //TAP_PrintNet("Start rule = [%s].\n", s);
      if(s[0])
      {
        //TAP_PrintNet("Processing start rule.\n");
        DST_ProcessRule(s, DSTStartUTC, 0);  //This is still in local time
        //TAP_PrintNet("Start rule processed.\n");

        //Because the DST rule is expressed in local time, the opposite offset needs to be applied.
        //The rule states "At this time (local), the offset will become x", therefore, the current offset is the opposite.
        *DSTStartUTC = AddTime(*DSTStartUTC, -StdOffset);
        //TAP_PrintNet("DST Rule Start: %s.\n", TimeFormat(*DSTStartUTC, 0, TIMESTAMP_YMDHM));
        DSTStartUTCsaved = *DSTStartUTC;
      }
      else
        *DSTStartUTC = 0;
    }//END DST Start

    if(DSTEndUTC)
    {
      //TAP_PrintNet("Getting end rule.\n");
      INIGetString("DSTEndRule", s, "", sizeof(s) - 1);
      //TAP_PrintNet("End rule = [%s].\n", s);
      if(s[0])
      {
        //TAP_PrintNet("Processing end rule.\n");
        DST_ProcessRule(s, DSTEndUTC, 0);  //This is still in local time
        //TAP_PrintNet("End rule processed.\n");
        *DSTEndUTC = AddTime(*DSTEndUTC, -StdOffset);
        //TAP_PrintNet("DST Rule   End: %s.\n", TimeFormat(*DSTEndUTC, 0, TIMESTAMP_YMDHM));
        DSTEndUTCsaved = *DSTEndUTC;
      }
      else
        *DSTEndUTC = 0;
    }//END DST End
  }
  else
  {
    //Failed to open DST.ini
    if(DSTStartUTC) *DSTStartUTC = 0;
    if(DSTEndUTC) *DSTEndUTC = 0;
  }
  INICloseFile();
  HDD_TAP_PopDir();

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
