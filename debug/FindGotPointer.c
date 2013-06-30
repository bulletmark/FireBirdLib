#include                "../libFireBird.h"

dword *FindGotPointer(dword FunctionAddress)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FindGotPointer");
  #endif

  static dword          gotStart = 0, gotEnd = 0;
  dword                 SectionIndex;
  dword                *got;

  if(!gotStart)
  {
    if(ELFOpenAbsFile("/root/pvr") && ELFReadELFHeader() && ELFReadSectionHeaders() && ELFReadShstrtabSection())
    {
      SectionIndex = ELFGetSectionIndex(".got");
      if(SectionIndex)
      {
        ELFGetSectionAddress(SectionIndex, &gotStart, &gotEnd);
        gotEnd += gotStart;
      }
    }
    ELFCleanup();
  }

  got = (dword*)gotStart;
  while(got < (dword*)gotEnd)
  {
    if(*got == FunctionAddress)
    {
      #ifdef DEBUG_FIREBIRDLIB
        CallTraceExit(NULL);
      #endif

      return got;
    }
    got++;
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return 0;
}
