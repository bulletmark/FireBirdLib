#include  "FBLib_FontManager.h"

bool FMUC_IsDiacriticalMark(dword Character)
{
  TRACEENTER();

  dword Diacricital[] = {0x00a8, 0x00b4, 0x00b8, 0x0384, 0x0385, 0x0e31};
  dword i;

  if((Character >= 0x0300) && (Character <= 0x036f))
  {
    TRACEEXIT();
    return TRUE;
  }

  if((Character >= 0x0e34) && (Character <= 0x0e3a))
  {
    TRACEEXIT();
    return TRUE;
  }

  if((Character >= 0x0e47) && (Character <= 0x0e4e))
  {
    TRACEEXIT();
    return TRUE;
  }


  for(i = 0; i < 6; i++)
    if(Character == Diacricital[i])
    {
      TRACEEXIT();
      return TRUE;
    }

  TRACEEXIT();
  return FALSE;
}
