#include  <stdio.h>
#include  <string.h>
#include  "../libFireBird.h"

void LogEntry(char *FileName, char *ProgramName, bool Console, eTimeStampFormat TimeStampFormat, char *Text)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("LogEntry");
  #endif

  TYPE_File             *File;
  char                  *TS;
  char                  CRLF[] = {'\r', '\n'};
  byte                  Sec;
  byte                 *ISOText;

  if(!Text)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return;
  }


  TS = TimeFormat(Now(&Sec), Sec, TimeStampFormat);
  if(TS[0]) strcat(TS, " ");

  if(FileName && FileName[0])
  {
    if(!TAP_Hdd_Exist(FileName)) TAP_Hdd_Create(FileName, ATTR_NORMAL);
    if((File = TAP_Hdd_Fopen(FileName)) != NULL)
    {
      TAP_Hdd_Fseek(File, 0, SEEK_END);
      TAP_Hdd_Fwrite(TS, strlen(TS), 1, File);
      if(Text && Text[0]) TAP_Hdd_Fwrite(Text, strlen(Text), 1, File);
      TAP_Hdd_Fwrite(CRLF, 2, 1, File);
      TAP_Hdd_Fclose(File);
    }
  }

  if(Console)
  {
    if(TimeStampFormat != TIMESTAMP_NONE) TAP_PrintNet(TS);
    if(ProgramName && ProgramName[0]) TAP_PrintNet("%s: ", ProgramName);

    //Max length is 512. If above, a buffer overflow may occur
    StrToISOAlloc(Text, &ISOText);
    if(ISOText && ISOText[0])
    {
      if(strlen(ISOText) < 510)
      {
        TAP_PrintNet("%s", ISOText);
      }
      else
      {
        char *p = ISOText;

        while(*p)
        {
          int     l;
          char    q;

          l = strlen(p);
          if(l > 510) l = 510;

          q = p[l];
          p[l] = '\0';
          TAP_PrintNet("%s", p);
          p[l] = q;
          p += l;
        }
      }
    }
    TAP_PrintNet("\n");
    TAP_MemFree(ISOText);
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
