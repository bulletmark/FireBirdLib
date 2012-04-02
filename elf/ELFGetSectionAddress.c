#include                "ELF.h"
#include                "FBLib_elf.h"

bool ELFGetSectionAddress(dword SectionIndex, dword *SectionAddress, dword *SectionSize)
{
  if(SectionIndex >= ELFHeader->e_shnum) return FALSE;

  if(SectionAddress) *SectionAddress = SectionHeaders[SectionIndex].sh_addr;
  if(SectionSize)    *SectionSize = SectionHeaders[SectionIndex].sh_size;

  return TRUE;
}
