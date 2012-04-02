#include                "ELF.h"
#include                "FBLib_elf.h"

bool ELFReadShstrtabSection(void)
{
  Elf32_Shdr           *pshstrtabSH = NULL;   //Shortcut to speed up access to the .shstrtab section header

  //Read the .shstrtab section. It contains a "string database" with the names of all sections
  if(ELFHeader->e_shtrndx >= ELFHeader->e_shnum) return FALSE;
  pshstrtabSH = &SectionHeaders[ELFHeader->e_shtrndx];
  if(pshstrtabSH->sh_type != SHT_STRTAB) return FALSE;
  if(!(shstrtab = TAP_MemAlloc(pshstrtabSH->sh_size))) return FALSE;
  lseek(fTAP, pshstrtabSH->sh_offset, SEEK_SET);
  if(read(fTAP, shstrtab, pshstrtabSH->sh_size) != (int)pshstrtabSH->sh_size) return FALSE;

  return TRUE;
}
