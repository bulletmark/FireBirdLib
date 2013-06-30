#include  <stdio.h>
#include  <string.h>
#include "stdarg.h"    //va_list
#include  "../libFireBird.h"

int vsnprintf(char *str, size_t size, const char *format, va_list ap);   //define missing prototype

void LogEntryFBLibPrintf(bool Console, char *format, ...)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("LogEntryFBLibPrintf");
  #endif

  char                  Text[512];
  TYPE_File            *File;
  char                 *TS;
  byte                  Sec;
  char                  CRLF[] = {'\r', '\n'};

  #define FILENAME      "FBLib.log"

  if(!format)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return;
  }

  va_list args;
  va_start(args, format);
  vsnprintf(Text, sizeof(Text), format, args);
  va_end(args);

  HDD_TAP_PushDir();
  if(!HDD_ChangeDir("/ProgramFiles/Settings"))
  {
    HDD_ChangeDir("/ProgramFiles");
    if(!TAP_Hdd_Exist("Settings")) TAP_Hdd_Create("Settings", ATTR_FOLDER);
    HDD_ChangeDir("Settings");
  }

  TS = TimeFormat(Now(&Sec), Sec, TIMESTAMP_YMDHMS);
  strcat(TS, " ");

  if(!TAP_Hdd_Exist(FILENAME)) TAP_Hdd_Create(FILENAME, ATTR_NORMAL);
  if((File = TAP_Hdd_Fopen(FILENAME)) != NULL)
  {
    TAP_Hdd_Fseek(File, 0, SEEK_END);
    TAP_Hdd_Fwrite(TS, strlen(TS), 1, File);
    TAP_Hdd_Fwrite(Text, strlen(Text), 1, File);
    TAP_Hdd_Fwrite(CRLF, 2, 1, File);
    TAP_Hdd_Fclose(File);
  }

  if(Console)
  {
    TAP_PrintNet("%s FBLIB - %s\n", TS, Text);
  }

  HDD_TAP_PopDir();

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
