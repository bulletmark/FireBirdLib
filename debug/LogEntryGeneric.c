#include  <stdio.h>
#include  <string.h>
#include  "../libFireBird.h"

void LogEntryGeneric(char *ProgramName, bool Console, char *Text)
{
  char                 *s;
  int                   l;
  TYPE_File             *File;
  char                  *TS;
  char                  CRLF[] = {'\r', '\n'};
  byte                  Sec;

#define FILENAME        "TAPSystem.log"

  HDD_TAP_PushDir();
  if(!HDD_ChangeDir("/ProgramFiles/Settings"))
  {
    HDD_ChangeDir("/ProgramFiles");
    if(!TAP_Hdd_Exist("Settings")) TAP_Hdd_Create("Settings", ATTR_FOLDER);
    HDD_ChangeDir("Settings");
  }
  l = strlen(ProgramName) + strlen(Text) + 4;
  s = TAP_MemAlloc(l);
  memset(s, 0, l);
  TAP_SPrint(s, "%s: %s", ProgramName, Text);

  TS = TimeFormat(Now(&Sec), Sec, TIMESTAMP_YMDHMS);
  strcat(TS, " ");

  if(!TAP_Hdd_Exist(FILENAME)) TAP_Hdd_Create(FILENAME, ATTR_NORMAL);
  if((File = TAP_Hdd_Fopen(FILENAME)) != NULL)
  {
    TAP_Hdd_Fseek(File, 0, SEEK_END);
    TAP_Hdd_Fwrite(TS, strlen(TS), 1, File);
    TAP_Hdd_Fwrite(s, strlen(s), 1, File);
    TAP_Hdd_Fwrite(CRLF, 2, 1, File);
    TAP_Hdd_Fclose(File);
  }

  if (Console)
  {
    TAP_PrintNet("%s%s\n", TS, s);
  }

  HDD_TAP_PopDir();
  TAP_MemFree(s);
}
