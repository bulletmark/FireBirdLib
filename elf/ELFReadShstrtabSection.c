#include                <stdlib.h>
#include                "ELF.h"
#include                "FBLib_elf.h"

#undef malloc
#undef free

bool ELFReadShstrtabSection(void)
{
  TRACEENTER();

  Elf32_Shdr           *pshstrtabSH = NULL;   //Shortcut to speed up access to the .shstrtab section header

  //Read the .shstrtab section. It contains a "string database" with the names of all sections
  if(ELFHeader->e_shtrndx >= ELFHeader->e_shnum)
  {
    TRACEEXIT();
    return FALSE;
  }

  pshstrtabSH = &SectionHeaders[ELFHeader->e_shtrndx];
  if(pshstrtabSH->sh_type != SHT_STRTAB)
  {
    TRACEEXIT();
    return FALSE;
  }

  if(!(shstrtab = malloc(pshstrtabSH->sh_size)))
  {
    TRACEEXIT();
    return FALSE;
  }

  lseek(fTAP, pshstrtabSH->sh_offset, SEEK_SET);
  if(read(fTAP, shstrtab, pshstrtabSH->sh_size) != (int)pshstrtabSH->sh_size)
  {
    TRACEEXIT();
    return FALSE;
  }


  TRACEEXIT();
  return TRUE;
}
