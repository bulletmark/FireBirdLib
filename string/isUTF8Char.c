#include                "../libFireBird.h"

bool isUTF8Char(byte *p, byte *BytesPerChar)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("isUTF8Char");
  #endif

  bool                  a, b, c;
  byte                  bpc;

  if(!p)
  {
    if(BytesPerChar) *BytesPerChar = 1;

    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  bpc = 1;

  a = ((p[0] & 0xe0) == 0xc0) && ((p[1] & 0xc0) == 0x80);
  if(a) bpc = 2;

  b = ((p[0] & 0xf0) == 0xe0) && ((p[1] & 0xc0) == 0x80) && ((p[2] & 0xc0) == 0x80);
  if(b) bpc = 3;

  c = ((p[0] & 0xf8) == 0xf0) && ((p[1] & 0xc0) == 0x80) && ((p[2] & 0xc0) == 0x80)  && ((p[3] & 0xc0) == 0x80);
  if(c) bpc = 4;

  if(BytesPerChar) *BytesPerChar = bpc;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return (a || b || c);
}
