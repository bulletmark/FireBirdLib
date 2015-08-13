#include                <stdlib.h>
#include                "ELF.h"
#include                "FBLib_elf.h"

bool ELFReadSectionHeaders(void)
{
  TRACEENTER();

  if(ELFHeader->e_shnum == 0)
  {
    TRACEEXIT();
    return FALSE;
  }

  if(!(SectionHeaders = TAP_MemAlloc(ELFHeader->e_shnum * sizeof(Elf32_Shdr))))
  {
    TRACEEXIT();
    return FALSE;
  }

  lseek(fTAP, ELFHeader->e_shoff, SEEK_SET);
  if(read(fTAP, SectionHeaders, ELFHeader->e_shnum * sizeof(Elf32_Shdr)) != (int)(ELFHeader->e_shnum * sizeof(Elf32_Shdr)))
  {
    TRACEEXIT();
    return FALSE;
  }


  TRACEEXIT();
  return TRUE;
}
