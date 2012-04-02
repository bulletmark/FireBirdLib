#include                "../libFireBird.h"

bool HookFirmware(char *FirmwareFunctionName, void *RedirectTo, dword *PointerToOriginal)
{
  dword                *got;
  dword                 FirmwareFunction;

  if(!FirmwareFunctionName || !RedirectTo || !PointerToOriginal) return FALSE;

  FirmwareFunction = TryResolve(FirmwareFunctionName);
  if(!FirmwareFunction) return FALSE;

  got = FindGotPointer(FirmwareFunction);
  if(got)
  {
    *PointerToOriginal = FirmwareFunction;
    *got = (dword)RedirectTo;
    return TRUE;
  }

  return FALSE;
}
