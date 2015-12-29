#include                "ELF.h"
#include                "FBLib_elf.h"

bool ELFGetSectionOffset(dword SectionIndex, dword *SectionOffset, dword *SectionSize)
{
  TRACEENTER();

  if(SectionIndex >= ELFHeader->e_shnum)
  {
    TRACEEXIT();
    return FALSE;
  }

  if(SectionOffset) *SectionOffset = SectionHeaders[SectionIndex].sh_offset;
  if(SectionSize)   *SectionSize = SectionHeaders[SectionIndex].sh_size;

  TRACEEXIT();
  return TRUE;
}
