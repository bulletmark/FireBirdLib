#include                "ELF.h"
#include                "FBLib_elf.h"

bool ELFReadELFHeader(void)
{
  if(!(ELFHeader = TAP_MemAlloc(sizeof(Elf32_Ehdr)))) return FALSE;
  if(read(fTAP, ELFHeader, sizeof(Elf32_Ehdr)) != sizeof(Elf32_Ehdr)) return FALSE;

  return TRUE;
}
