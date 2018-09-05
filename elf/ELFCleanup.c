#include                <stdlib.h>
#include                "ELF.h"
#include                "FBLib_elf.h"

void ELFCleanup(void)
{
  TRACEENTER;

  if(fTAP)
  {
    close(fTAP);
    fTAP = 0;
  }

  if(ELFHeader)
  {
    TAP_MemFree(ELFHeader);
    ELFHeader = NULL;
  }

  if(SectionHeaders)
  {
    TAP_MemFree(SectionHeaders);
    SectionHeaders = NULL;
  }

  if(shstrtab)
  {
    TAP_MemFree(shstrtab);
    shstrtab = NULL;
  }

  if(strtab)
  {
    TAP_MemFree(strtab);
    strtab = NULL;
  }

  TRACEEXIT;
}
