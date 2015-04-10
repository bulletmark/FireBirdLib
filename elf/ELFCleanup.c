#include                <stdlib.h>
#include                "ELF.h"
#include                "FBLib_elf.h"

#undef malloc
#undef free

void ELFCleanup(void)
{
  TRACEENTER();

  if(fTAP)
  {
    close(fTAP);
    fTAP = 0;
  }

  if(ELFHeader)
  {
    free(ELFHeader);
    ELFHeader = NULL;
  }

  if(SectionHeaders)
  {
    free(SectionHeaders);
    SectionHeaders = NULL;
  }

  if(shstrtab)
  {
    free(shstrtab);
    shstrtab = NULL;
  }

  if(strtab)
  {
    free(strtab);
    strtab = NULL;
  }

  TRACEEXIT();
}
