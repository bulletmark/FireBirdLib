#include                <stdlib.h>
#include                "ELF.h"
#include                "FBLib_elf.h"

#undef malloc
#undef free

bool ELFReadELFHeader(void)
{
  TRACEENTER();

  if(!(ELFHeader = malloc(sizeof(Elf32_Ehdr))))
  {
    TRACEEXIT();
    return FALSE;
  }

  if(read(fTAP, ELFHeader, sizeof(Elf32_Ehdr)) != sizeof(Elf32_Ehdr))
  {
    TRACEEXIT();
    return FALSE;
  }

  TRACEEXIT();
  return TRUE;
}
