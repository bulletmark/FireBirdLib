#include                "../libFireBird.h"

byte *GetUCPos(byte *String, int CharPos)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("GetUCPos");
  #endif

  byte                  bpc;
  int                   i;

  if(!String)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return NULL;
  }

  String = SkipCharTableBytes(String);

  i = 0;

  while(i < CharPos)
  {
    if(String[0] == '\0') break;

    UTF8ToUTF32(String, &bpc);
    String += bpc;
    i++;
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return String;
}
