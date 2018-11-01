#include                "FBLib_time.h"

void DST_GetTransitions_Manual(dword *DSTStartUTC, dword *DSTEndUTC)
{
  TRACEENTER();

  if(DSTStartUTCsaved != 0 && DSTEndUTCsaved != 0)
  {
    if(Now(NULL) < DSTStartUTCsaved && Now(NULL) < DSTStartUTCsaved)
    {
      if(DSTStartUTC) *DSTStartUTC = DSTStartUTCsaved;
      if(DSTEndUTC) *DSTEndUTC = DSTEndUTCsaved;

      TRACEEXIT();
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
      INIGetString("DSTStartRule", s, "", sizeof(s) - 1);
      if(s[0])
      {
        DST_ProcessRule(s, DSTStartUTC, 0);  //This is still in local time

        //Because the DST rule is expressed in local time, the opposite offset needs to be applied.
        //The rule states "At this time (local), the offset will become x", therefore, the current offset is the opposite.
        *DSTStartUTC = AddTime(*DSTStartUTC, -StdOffset);
        DSTStartUTCsaved = *DSTStartUTC;
      }
      else
        *DSTStartUTC = 0;
    }

    if(DSTEndUTC)
    {
      INIGetString("DSTEndRule", s, "", sizeof(s) - 1);
      if(s[0])
      {
        DST_ProcessRule(s, DSTEndUTC, 0);  //This is still in local time
        *DSTEndUTC = AddTime(*DSTEndUTC, -StdOffset);
        DSTEndUTCsaved = *DSTEndUTC;
      }
      else
        *DSTEndUTC = 0;
    }
  }
  else
  {
    //Failed to open DST.ini
    if(DSTStartUTC) *DSTStartUTC = 0;
    if(DSTEndUTC) *DSTEndUTC = 0;
  }
  INICloseFile();
  HDD_TAP_PopDir();

  TRACEEXIT();
}
