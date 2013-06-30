#include                "../libFireBird.h"

bool HookFirmware(char *FirmwareFunctionName, void *RedirectTo, dword *PointerToOriginal)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HookFirmware");
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

  got = FindGotPointer(FirmwareFunction);
  if(got)
  {
    *PointerToOriginal = FirmwareFunction;
    *got = (dword)RedirectTo;

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
