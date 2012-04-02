#include                "ELF.h"
#include                "FBLib_elf.h"

bool ELFOpenAbsFile(char *FileName)
{
  fTAP = open(FileName, O_RDONLY);

  return (fTAP != 0);
}
