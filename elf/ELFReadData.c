#include                "ELF.h"
#include                "FBLib_elf.h"

bool ELFReadData(dword SectionIndex, byte *Data)
{
  Elf32_Shdr           *pSection = NULL;     //Shortcut to speed up access

  pSection = &SectionHeaders[SectionIndex];

  if(Data)
  {
    lseek(fTAP, pSection->sh_offset, SEEK_SET);
    if(read(fTAP, Data, pSection->sh_size) != (int)pSection->sh_size) return FALSE;
  }

  return TRUE;
}
