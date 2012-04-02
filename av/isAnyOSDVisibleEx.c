#include "../libFireBird.h"

bool isAnyOSDVisibleEx(dword checkX, dword checkY, dword checkW, dword checkH, byte Plane)
{
  TYPE_OsdBaseInfo      OSDBaseInfo;
  dword                *pOSD;
  dword                 x, y;

  TAP_Osd_GetPlaneBaseInfo(&OSDBaseInfo, Plane);
  if(OSDBaseInfo.frameBuffer == NULL) return FALSE;

  for(y = checkY; y < (checkY + checkH); y += 4)
  {
    pOSD = (dword*)(OSDBaseInfo.frameBuffer);
    pOSD = (dword*)&pOSD[720*y + checkX];
    for(x = checkX; x < (checkX + checkW); x += 4)
    {
      if(*pOSD != 0x00000000) return TRUE;
      pOSD += 4;
    }
  }
  return FALSE;
}
