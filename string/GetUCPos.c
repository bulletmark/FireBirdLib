#include                "libFireBird.h"

byte *GetUCPos(byte *String, int CharPos)
{
  TRACEENTER();

  byte                  bpc;
  int                   i;

  if(!String)
  {
    TRACEEXIT();
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

  TRACEEXIT();
  return String;
}
