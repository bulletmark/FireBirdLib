#include  <stdio.h>
#include  <string.h>
#include  "../libFireBird.h"

void LogEntryGeneric(char *ProgramName, bool Console, char *Text)
{
  TRACEENTER();

  char                 *s;
  int                   l;
  TYPE_File             *File;
  char                  *TS;
  char                  CRLF[] = {'\r', '\n'};
  byte                  Sec;
  byte                 *ISOText;

  #define FILENAME      "TAPSystem.log"

  if(!ProgramName || !Text)
  {
    TRACEEXIT();
    return;
  }

  HDD_TAP_PushDir();
  if(!HDD_ChangeDir("/ProgramFiles/Settings"))
  {
    HDD_ChangeDir("/ProgramFiles");
    if(!TAP_Hdd_Exist("Settings")) TAP_Hdd_Create("Settings", ATTR_FOLDER);
    HDD_ChangeDir("Settings");
  }

  l = strlen(ProgramName) + strlen(Text) + 4;
  s = TAP_MemAlloc(l);
  if(s)
  {
    memset(s, 0, l);
    TAP_SPrint(s, "%s: %s", ProgramName, Text);
    StrToISOAlloc(s, &ISOText);
    if(ISOText)
    {
      TS = TimeFormat(Now(&Sec), Sec, TIMESTAMP_YMDHMS);
      strcat(TS, " ");

      if(!TAP_Hdd_Exist(FILENAME)) TAP_Hdd_Create(FILENAME, ATTR_NORMAL);
      if((File = TAP_Hdd_Fopen(FILENAME)) != NULL)
      {
        TAP_Hdd_Fseek(File, 0, SEEK_END);
        TAP_Hdd_Fwrite(TS, strlen(TS), 1, File);
        TAP_Hdd_Fwrite(ISOText, strlen(ISOText), 1, File);
        TAP_Hdd_Fwrite(CRLF, 2, 1, File);
        TAP_Hdd_Fclose(File);
      }

      if(Console)
      {
        TAP_PrintNet("%s%s\n", TS, ISOText);
      }

      TAP_MemFree(ISOText);
    }
    TAP_MemFree(s);
  }
  HDD_TAP_PopDir();

  TRACEEXIT();
}
