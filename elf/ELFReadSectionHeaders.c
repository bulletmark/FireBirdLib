#include                "ELF.h"
#include                "FBLib_elf.h"

bool ELFReadSectionHeaders(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("ELFReadSectionHeaders");
  #endif

  if(ELFHeader->e_shnum == 0)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  if(!(SectionHeaders = TAP_MemAlloc(ELFHeader->e_shnum * sizeof(Elf32_Shdr))))
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  lseek(fTAP, ELFHeader->e_shoff, SEEK_SET);
  if(read(fTAP, SectionHeaders, ELFHeader->e_shnum * sizeof(Elf32_Shdr)) != (int)(ELFHeader->e_shnum * sizeof(Elf32_Shdr)))
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
