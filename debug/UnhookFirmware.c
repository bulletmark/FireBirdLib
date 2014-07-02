#include                "../libFireBird.h"

bool UnhookFirmware(char *FirmwareFunctionName, void *RedirectTo, void *PointerToOriginal)
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

  got = FindGotPointer((dword)RedirectTo);
  if(got)
  {
    *got = *(dword*)PointerToOriginal;

    TRACEEXIT();
    return TRUE;
  }

  TRACEEXIT();
  return FALSE;
}
