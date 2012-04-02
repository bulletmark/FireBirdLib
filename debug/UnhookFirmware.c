#include                "../libFireBird.h"

bool UnhookFirmware(char *FirmwareFunctionName, void *RedirectTo, dword *PointerToOriginal)
{
  dword                *got;
  dword                 FirmwareFunction;

  if(!FirmwareFunctionName || !RedirectTo || !PointerToOriginal) return FALSE;

  FirmwareFunction = TryResolve(FirmwareFunctionName);
  if(!FirmwareFunction) return FALSE;

  got = FindGotPointer((dword)RedirectTo);
  if(got)
  {
    *got = *PointerToOriginal;
    return TRUE;
  }

  return FALSE;
}
