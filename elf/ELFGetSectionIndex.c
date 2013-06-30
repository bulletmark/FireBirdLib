#include                "ELF.h"
#include                "FBLib_elf.h"

dword ELFGetSectionIndex(char *SectionName)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("ELFGetSectionIndex");
  #endif

  int                   i;

  if(SectionName)
  {
    //Loop through all section headers and locate SectionName
    for(i = 1; i < ELFHeader->e_shnum; i++)
      if(!strcmp(&shstrtab[SectionHeaders[i].sh_name], SectionName))
      {
        #ifdef DEBUG_FIREBIRDLIB
          CallTraceExit(NULL);
        #endif

        return i;
      }
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return 0;
}
