#include                <string.h>
#include                <stdlib.h>
#include                "libFireBird.h"
#include                "FBLib_LogoManager.h"

bool LogoManager_LogosAvailable(tLogoStyle LogoStyle)
{
  TRACEENTER;

  int                   i;

  for(i = 0; i < LogoManager_NrLogos; i++)
    if(LogoManager_LogoData[i].Style  == LogoStyle)
    {
      TRACEEXIT;
      return TRUE;
    }

  TRACEEXIT;
  return FALSE;
}
