#include                "libFireBird.h"

void Appl_WriteRecInfo(dword Slot)
{
  TRACEENTER;

  void(*__Appl_WriteRecInfo)(dword Slot) = NULL;

  __Appl_WriteRecInfo = (void*)FIS_fwAppl_WriteRecInfo();
  if(__Appl_WriteRecInfo) __Appl_WriteRecInfo(Slot);

  TRACEEXIT;
}
