#include                "../libFireBird.h"

void Appl_WriteRecInfo(dword Slot)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("Appl_WriteRecInfo");
  #endif

  void(*__Appl_WriteRecInfo)(dword Slot) = NULL;

  __Appl_WriteRecInfo = (void*)FIS_fwAppl_WriteRecInfo();
  if(__Appl_WriteRecInfo) __Appl_WriteRecInfo(Slot);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
