#include "libFireBird.h"

bool isAnyOSDVisibleEx(dword CheckX, dword CheckY, dword CheckW, dword CheckH, byte Plane)
{
  TRACEENTER();

  TYPE_OsdBaseInfo      OSDBaseInfo;
  dword                *pOSD;
  dword                 x, y;

  TAP_Osd_GetPlaneBaseInfo(&OSDBaseInfo, Plane);
  if(OSDBaseInfo.frameBuffer == NULL)
  {
    TRACEEXIT();
    return FALSE;
  }

  for(y = CheckY; y < (CheckY + CheckH); y += 4)
  {
    pOSD = (dword*)(OSDBaseInfo.frameBuffer);
    pOSD = (dword*)&pOSD[720*y + CheckX];
    for(x = CheckX; x < (CheckX + CheckW); x += 4)
    {
      if(*pOSD != 0x00000000)
      {
        TRACEEXIT();
        return TRUE;
      }
      pOSD += 4;
    }
  }

  TRACEEXIT();
  return FALSE;
}
