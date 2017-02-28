#include                <fcntl.h>
#include                <stdlib.h>
#include                <unistd.h>
#include                <stdio.h>
#include                <string.h>
#include                <sys/types.h>
#include                <utime.h>
#include                "../libFireBird.h"

void LogEntry(char *FileName, char *ProgramName, bool Console, eTimeStampFormat TimeStampFormat, char *Text)
{
  TRACEENTER();

  int                   f;
  char                  TimeResult[40];
  char                  CRLF[] = {'\r', '\n'};
  byte                  Sec;
  byte                 *ISOText;
  char                  AbsFileName[FBLIB_DIR_SIZE];
  struct utimbuf        times;

  if(!Text)
  {
    TRACEEXIT();
    return;
  }

  TimeFormat(Now(&Sec), Sec, TimeStampFormat, TimeResult);
  if(TimeResult[0]) strcat(TimeResult, " ");

  if(FileName && FileName[0])
  {
    ConvertPathType(FileName, AbsFileName, PF_FullLinuxPath);
    f = open(AbsFileName, O_WRONLY | O_CREAT | O_APPEND);
    if(f >= 0)
    {
      write(f, TimeResult, strlen(TimeResult));
      if(Text && Text[0]) write(f, Text, strlen(Text));
      write(f, CRLF, 2);
      close(f);

      //As the log would receive the Linux time stamp (01.01.2000), adjust to the PVR's time
      times.actime = PvrTimeToLinux(Now(NULL));
      times.modtime = times.actime;
      utime(AbsFileName, &times);
    }
  }

  if(Console)
  {
    if(TimeStampFormat != TIMESTAMP_NONE) TAP_PrintNet(TimeResult);
    if(ProgramName && ProgramName[0]) TAP_PrintNet("%s: ", ProgramName);

    if(isUTFToppy())
    {
      if(strlen(Text) < 510)
      {
        TAP_PrintNet("%s", Text);
      }
      else
      {
        char *p = Text;

        while(*p)
        {
          int     l;
          char    q;

          l = strlen(p);
          q = p[l];
          p[l] = '\0';
          TAP_PrintNet("%s", p);
          p[l] = q;
          p += l;
        }
      }
      TAP_PrintNet("\n");
    }
    else
    {
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
  }

  TRACEEXIT();
}
