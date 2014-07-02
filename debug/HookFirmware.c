#include                "../libFireBird.h"

bool HookFirmware(char *FirmwareFunctionName, void *RedirectTo, void *PointerToOriginal)
{
  TRACEENTER();

  dword                *got;
  dword                 FirmwareFunction;

  if(!FirmwareFunctionName || !RedirectTo || !PointerToOriginal)
  {
    TRACEEXIT();
    return FALSE;
  }

  FirmwareFunction = TryResolve(FirmwareFunctionName);
  if(!FirmwareFunction)
  {
    TRACEEXIT();
    return FALSE;
  }

  got = FindGotPointer(FirmwareFunction);
  if(got)
  {
    *(dword*)PointerToOriginal = FirmwareFunction;
    *got = (dword)RedirectTo;

    TRACEEXIT();
    return TRUE;
  }

  TRACEEXIT();
  return FALSE;
}
