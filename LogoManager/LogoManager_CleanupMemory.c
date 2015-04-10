#include                <string.h>
#include                <stdlib.h>
#include                "../libFireBird.h"
#include                "FBLib_LogoManager.h"

#undef malloc
#undef free

void LogoManager_CleanupMemory(void)
{
  TRACEENTER();

  int                   i;

  if(LogoManager_LogoData)
  {
    for(i = 0; i < LogoManager_NrLogos; i++)
    {
      if(LogoManager_LogoData[i].grData)
      {
        free(LogoManager_LogoData[i].grData);
        LogoManager_LogoData[i].grData = NULL;
      }
    }
  }


  TRACEEXIT();
}
