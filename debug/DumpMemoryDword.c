#include                <stdio.h>
#include                <string.h>
#include                "../libFireBird.h"

void DumpMemoryDword(dword *p, dword size)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("DumpMemoryDword");
  #endif

  dword                *StartAddress = p;
  int                   CollectedBytes;
  char                  Header[20];
  char                  s[255];
  int                   Remaining;

  if(!p)
  {
    TAP_Print("0x00000000 NULL\n");

    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return;
  }

  s[0] = '\0';
  CollectedBytes = 0;

  TAP_SPrint(Header, "%p 0x%4.4x: ", p, (dword)p - (dword)StartAddress);

  Remaining = size;
  while(Remaining > 0)
  {
    TAP_SPrint(&s[strlen(s)], "%8.8x ", *p);

    CollectedBytes += 4;
    p++;
    Remaining -= 4;

    if(CollectedBytes >= 16)
    {
      strcat(s, "\n");
      TAP_Print(Header);
      TAP_Print(s);
      s[0] = '\0';
      TAP_SPrint(Header, "%p 0x%4.4x: ", p, (dword)p - (dword)StartAddress);
      CollectedBytes = 0;
    }
  }

  if(strlen(s))
  {
    strcat(s, "\n");
    TAP_Print(Header);
    TAP_Print(s);
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
