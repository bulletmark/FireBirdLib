#include <stdio.h>
#include  <string.h>
#include  "libFireBird.h"

void DumpMemory(byte* p, dword size, int BytesPerLine)
{
  TRACEENTER;

  byte                 *StartAddress = p;
  int                   CollectedBytes, i;
  char                  text[200], Header[20];
  char                  s[255];
  dword                 Remaining;

  if(!p)
  {
    TAP_Print("0x00000000 NULL\n");

    TRACEEXIT;
    return;
  }

  s[0] = '\0';
  text[0] = '\0';
  CollectedBytes = 0;

  TAP_SPrint(Header, "%p 0x%4.4x: ", p, (dword)(p - StartAddress));

  Remaining = size;
  while(Remaining > 0)
  {
    TAP_SPrint(&s[strlen(s)], "%2.2x ", *p);
    if((*p >= 0x20) && (*p <= 0x7e))  // && (*p != 0x25)
      TAP_SPrint(&text[strlen(text)], "%c", *p);
    else
      TAP_SPrint(&text[strlen(text)], ".");

    CollectedBytes++;
    p++;
    Remaining--;

    if(CollectedBytes >= BytesPerLine)
    {
      TAP_SPrint(&s[strlen(s)], "  %s\n", text);
      TAP_Print(Header);
      TAP_Print(s);
      s[0] = '\0';
      text[0] = '\0';
      TAP_SPrint(Header, "%p 0x%4.4x: ", p, (dword)(p - StartAddress));
      CollectedBytes = 0;
    }
  }
  if(strlen(s))
  {
    size %= BytesPerLine;
    if(size)
    {
      size = BytesPerLine - size;
      for(i = 0; i < (int)size; i++)
        strcat(s, "   ");
    }

    TAP_SPrint(&s[strlen(s)], "  %s\n", text);
    TAP_Print(Header);
    TAP_Print(s);
  }

  TRACEEXIT;
}
