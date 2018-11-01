#include                "libFireBird.h"

dword *FindGotPointer(dword FunctionAddress)
{
  TRACEENTER();

  static dword          gotStart = 0, gotEnd = 0;
  dword                 SectionIndex;
  dword                *got;

  if(!gotStart)
  {
    if(ELFOpenFile("/root/pvr") && ELFReadELFHeader() && ELFReadSectionHeaders() && ELFReadShstrtabSection())
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
      TRACEEXIT();

      return got;
    }
    got++;
  }

  TRACEEXIT();
  return 0;
}
