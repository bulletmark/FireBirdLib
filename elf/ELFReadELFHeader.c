#include                "ELF.h"
#include                "FBLib_elf.h"

bool ELFReadELFHeader(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("ELFReadELFHeader");
  #endif

  if(!(ELFHeader = TAP_MemAlloc(sizeof(Elf32_Ehdr))))
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  if(read(fTAP, ELFHeader, sizeof(Elf32_Ehdr)) != sizeof(Elf32_Ehdr))
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
