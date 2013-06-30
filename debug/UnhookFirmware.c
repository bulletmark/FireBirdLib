#include                "../libFireBird.h"

bool UnhookFirmware(char *FirmwareFunctionName, void *RedirectTo, dword *PointerToOriginal)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("UnhookFirmware");
  #endif

  dword                *got;
  dword                 FirmwareFunction;

  if(!FirmwareFunctionName || !RedirectTo || !PointerToOriginal)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  FirmwareFunction = TryResolve(FirmwareFunctionName);
  if(!FirmwareFunction)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  got = FindGotPointer((dword)RedirectTo);
  if(got)
  {
    *got = *PointerToOriginal;

    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return TRUE;
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return FALSE;
}
