#include                "ELF.h"
#include                "FBLib_elf.h"

dword ELFGetSectionIndex(char *SectionName)
{
  int                   i;

  //Loop through all section headers and locate SectionName
  for(i = 1; i < ELFHeader->e_shnum; i++)
    if(!strcmp(&shstrtab[SectionHeaders[i].sh_name], SectionName)) return i;

  return 0;
}
