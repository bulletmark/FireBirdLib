#include                "ELF.h"
#include                "FBLib_elf.h"

bool ELFGetSectionAddress(dword SectionIndex, dword *SectionAddress, dword *SectionSize)
{
  TRACEENTER();

  if(SectionIndex >= ELFHeader->e_shnum)
  {
    TRACEEXIT();
    return FALSE;
  }

  if(SectionAddress) *SectionAddress = SectionHeaders[SectionIndex].sh_addr;
  if(SectionSize)    *SectionSize = SectionHeaders[SectionIndex].sh_size;

  TRACEEXIT();
  return TRUE;
}
