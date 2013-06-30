#include                "ELF.h"
#include                "FBLib_elf.h"

bool ELFGetSectionAddress(dword SectionIndex, dword *SectionAddress, dword *SectionSize)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("ELFGetSectionAddress");
  #endif

  if(SectionIndex >= ELFHeader->e_shnum)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  if(SectionAddress) *SectionAddress = SectionHeaders[SectionIndex].sh_addr;
  if(SectionSize)    *SectionSize = SectionHeaders[SectionIndex].sh_size;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return TRUE;
}
