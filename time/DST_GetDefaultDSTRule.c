#include                <string.h>
#include                "FBLib_time.h"

void DST_GetDefaultDSTRule(void)
{
  TRACEENTER;

  char DefaultRule[80];

  DST_SetDSTRule(DSTR_Firmware);
  HDD_TAP_PushDir();
  HDD_ChangeDir("/ProgramFiles/Settings");
  if(INIOpenFile(MANUALDSTINI, "") > INILOCATION_NewFile)
  {
    if(INIGetString("DefaultRule", DefaultRule, "", 80))
    {
      LowerCase(DefaultRule);
      if(strcmp(DefaultRule, "europe") == 0) DST_SetDSTRule(DSTR_Europe);
      else if(strcmp(DefaultRule, "manual") == 0) DST_SetDSTRule(DSTR_Manual);
    }
  }
  INICloseFile();
  HDD_TAP_PopDir();

  TRACEEXIT;
}
