#include                "ELF.h"
#include                "FBLib_elf.h"

bool ELFReadSectionHeaders(void)
{
  if(ELFHeader->e_shnum == 0) return FALSE;
  if(!(SectionHeaders = TAP_MemAlloc(ELFHeader->e_shnum * sizeof(Elf32_Shdr)))) return FALSE;
  lseek(fTAP, ELFHeader->e_shoff, SEEK_SET);
  if(read(fTAP, SectionHeaders, ELFHeader->e_shnum * sizeof(Elf32_Shdr)) != (int)(ELFHeader->e_shnum * sizeof(Elf32_Shdr))) return FALSE;

  return TRUE;
}
