#include                <string.h>
#include                <stdlib.h>
#include                "../libFireBird.h"
#include                "FBLib_LogoManager.h"

void LogoManager_CleanupMemory(void)
{
  int                   i;

  if(LogoManager_LogoData)
  {
    for(i = 0; i < LogoManager_NrLogos; i++)
    {
      if(LogoManager_LogoData[i].grData)
      {
        TAP_MemFree(LogoManager_LogoData[i].grData);
        LogoManager_LogoData[i].grData = NULL;
      }
    }
  }
}
