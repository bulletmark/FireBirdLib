#include  <fcntl.h>
#include  <unistd.h>
#include  <stdio.h>
#include  <string.h>
#include  "../libFireBird.h"

void LogEntry(char *FileName, char *ProgramName, bool Console, eTimeStampFormat TimeStampFormat, char *Text)
{
  TRACEENTER();

  int                   f;
  char                 *TS;
  char                  CRLF[] = {'\r', '\n'};
  byte                  Sec;
  byte                 *ISOText;
  char                  AbsFileName[FBLIB_DIR_SIZE];

  if(!Text)
  {
    TRACEEXIT();
    return;
  }

  TS = TimeFormat(Now(&Sec), Sec, TimeStampFormat);
  if(TS[0]) strcat(TS, " ");

  if(FileName && FileName[0])
  {
    ConvertPathType(FileName, AbsFileName, PF_FullLinuxPath);
    f = open(AbsFileName, O_WRONLY | O_CREAT | O_APPEND);
    if(f >= 0)
    {
      write(f, TS, strlen(TS));
      if(Text && Text[0]) write(f, Text, strlen(Text));
      write(f, CRLF, 2);
      close(f);
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

  TRACEEXIT();
}
