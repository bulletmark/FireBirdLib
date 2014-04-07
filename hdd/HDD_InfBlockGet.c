#include                <string.h>
#include                <stdio.h>
#include                "FBLib_hdd.h"

bool HDD_InfBlockGet(char *RecPath, tinfBlock *infBlock)
{
  TRACEENTER();

  bool                  ret;
  FILE                 *FileHandle;
  tinfBlock             TempinfBlock;
  char                  AbsFileName[FBLIB_DIR_SIZE];

  if(!RecPath && !*RecPath)
  {
    TRACEEXIT();
    return FALSE;
  }

  ret = FALSE;
  if(infBlock) memset(infBlock, 0, sizeof(tinfBlock));

  ConvertPathType(RecPath, AbsFileName, PF_FullLinuxPath);
  if(*AbsFileName)
  {
    if(!StringEndsWith(AbsFileName, ".inf")) strcat(AbsFileName, ".inf");
    FileHandle = fopen64(AbsFileName, "rb");
    if(FileHandle)
    {
      fseeko64(FileHandle, -((__off64_t)sizeof(tinfBlock)), SEEK_END);
      fread(&TempinfBlock, sizeof(tinfBlock), 1, FileHandle);
      fclose(FileHandle);
      if((memcmp(TempinfBlock.Magic, INFBLOCKMAGIC, 4) == 0) && (TempinfBlock.Version == INFBLOCKVERSION))
      {
        if(infBlock) memcpy(infBlock, &TempinfBlock, sizeof(tinfBlock));
        ret = TRUE;
      }
    }
  }

  TRACEEXIT();
  return ret;
}
