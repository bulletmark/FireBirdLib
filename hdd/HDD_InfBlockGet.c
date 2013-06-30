#include                <stdio.h>
#include                "FBLib_hdd.h"

bool HDD_InfBlockGet(char *AbsRecPath, tinfBlock *infBlock)
{
  #if STACKTRACE == TRUE
    CallTraceEnter("FilesSystem_InfBlockGet");
  #endif

  bool                  ret;
  FILE                 *FileHandle;
  tinfBlock             TempinfBlock;

  ret = FALSE;
  if(infBlock) memset(infBlock, 0, sizeof(tinfBlock));

  if(AbsRecPath)
  {
    FileHandle = fopen64(AbsRecPath, "rb");
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

  #if STACKTRACE == TRUE
    CallTraceExit(NULL);
  #endif
  return ret;
}
