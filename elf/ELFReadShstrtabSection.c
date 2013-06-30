#include                "ELF.h"
#include                "FBLib_elf.h"

bool ELFReadShstrtabSection(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("ELFReadShstrtabSection");
  #endif

  Elf32_Shdr           *pshstrtabSH = NULL;   //Shortcut to speed up access to the .shstrtab section header

  //Read the .shstrtab section. It contains a "string database" with the names of all sections
  if(ELFHeader->e_shtrndx >= ELFHeader->e_shnum)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  pshstrtabSH = &SectionHeaders[ELFHeader->e_shtrndx];
  if(pshstrtabSH->sh_type != SHT_STRTAB)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  if(!(shstrtab = TAP_MemAlloc(pshstrtabSH->sh_size)))
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  lseek(fTAP, pshstrtabSH->sh_offset, SEEK_SET);
  if(read(fTAP, shstrtab, pshstrtabSH->sh_size) != (int)pshstrtabSH->sh_size)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }


  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return TRUE;
}
