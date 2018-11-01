#include                "ELF.h"
#include                "FBLib_elf.h"

dword ELFGetSectionIndex(char *SectionName)
{
  TRACEENTER();

  int                   i;

  if(SectionName)
  {
    //Loop through all section headers and locate SectionName
    for(i = 1; i < ELFHeader->e_shnum; i++)
      if(!strcmp(&shstrtab[SectionHeaders[i].sh_name], SectionName))
      {
        TRACEEXIT();
        return i;
      }
  }

  TRACEEXIT();
  return 0;
}
