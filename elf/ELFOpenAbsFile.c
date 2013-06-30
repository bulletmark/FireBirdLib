#include                "ELF.h"
#include                "FBLib_elf.h"

bool ELFOpenAbsFile(char *FileName)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("ELFOpenAbsFile");
  #endif

  fTAP = open(FileName, O_RDONLY);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return (fTAP != 0);
}
