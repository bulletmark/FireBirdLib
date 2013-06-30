#include                <stdio.h>
#include                "FBLib_hdd.h"

bool HDD_InfBlockSet(char *AbsRecPath, tinfBlock *infBlock)
{
  #if STACKTRACE == TRUE
    CallTraceEnter("HDD_InfBlockSet");
  #endif

  bool                  ret;
  FILE                 *FileHandle;
  tinfBlock             TempinfBlock;

  ret = FALSE;
  if(AbsRecPath && infBlock)
  {
    //Ein paar Daten updaten
    memcpy(infBlock->Magic, INFBLOCKMAGIC, 4);
    infBlock->Version = INFBLOCKVERSION;

    FileHandle = fopen64(AbsRecPath, "rb+");
    if(FileHandle)
    {
      //Prüfen, ob es bereits einen infBlock gibt
      fseeko64(FileHandle, -((__off64_t)sizeof(tinfBlock)), SEEK_END);
      fread(&TempinfBlock, sizeof(tinfBlock), 1, FileHandle);
      if((memcmp(TempinfBlock.Magic, INFBLOCKMAGIC, 4) == 0) && (TempinfBlock.Version == INFBLOCKVERSION))
      {
        //Ja, neu positionieren und überschreiben
        fseeko64(FileHandle, -((__off64_t)sizeof(tinfBlock)), SEEK_END);
      }
      else
      {
        //Nein, am Ende anhängen
        fseeko64(FileHandle, 0, SEEK_END);
      }
      fwrite(infBlock, sizeof(tinfBlock), 1, FileHandle);
      fclose(FileHandle);
      ret = TRUE;
    }
  }

  #if STACKTRACE == TRUE
    CallTraceExit(NULL);
  #endif
  return ret;
}
