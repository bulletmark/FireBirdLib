#include                <stdio.h>
#include                "ELF.h"
#include                "FBLib_elf.h"

int                      fTAP = 0;
Elf32_Ehdr              *ELFHeader = NULL;
Elf32_Shdr              *SectionHeaders = NULL;
char                    *shstrtab = NULL;
char                    *strtab = NULL;
Elf32_Sym               *symtab = NULL;

bool ELFOpenFile(const char *FileName)
{
  TRACEENTER();

  bool                  ret = FALSE;
  char                  AbsFileName[FBLIB_DIR_SIZE];

  if(FileName && *FileName)
  {
    ConvertPathType(FileName, AbsFileName, PF_FullLinuxPath);
    fTAP = open(AbsFileName, O_RDONLY);
    ret = (fTAP >= 0);
  }

  TRACEEXIT();
  return ret;
}
