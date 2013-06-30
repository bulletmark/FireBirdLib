#include "../libFireBird.h"

bool isAnyOSDVisibleEx(dword CheckX, dword CheckY, dword CheckW, dword CheckH, byte Plane)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("isAnyOSDVisibleEx");
  #endif

  TYPE_OsdBaseInfo      OSDBaseInfo;
  dword                *pOSD;
  dword                 x, y;

  TAP_Osd_GetPlaneBaseInfo(&OSDBaseInfo, Plane);
  if(OSDBaseInfo.frameBuffer == NULL)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

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
        #ifdef DEBUG_FIREBIRDLIB
          CallTraceExit(NULL);
        #endif

        return TRUE;
      }
      pOSD += 4;
    }
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return FALSE;
}
