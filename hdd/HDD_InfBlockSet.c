#include                <string.h>
#include                <stdio.h>
#include                "FBLib_hdd.h"

bool HDD_InfBlockSet(const char *RecPath, tinfBlock *infBlock)
{
  TRACEENTER();

  bool                  ret;
  FILE                 *FileHandle;
  tinfBlock             TempinfBlock;
  char                  AbsFileName[FBLIB_DIR_SIZE];
  tstat64               statbuf;

  if(!RecPath && !*RecPath)
  {
    TRACEEXIT();
    return FALSE;
  }

  ret = FALSE;

  ConvertPathType(RecPath, AbsFileName, PF_FullLinuxPath);
  if(*AbsFileName && infBlock)
  {
    if(!StringEndsWith(AbsFileName, ".inf"))
    {
      strcat(AbsFileName, ".inf");

      //Falls es keine .inf gibt, dann die eigentliche Datei nehmen
      if(stat64(AbsFileName, &statbuf) != 0)
      {
        AbsFileName[strlen(AbsFileName) - 4] = '\0';
      }
    }

    //Ein paar Daten updaten
    memcpy(infBlock->Magic, INFBLOCKMAGIC, 4);
    infBlock->Version = INFBLOCKVERSION;

    FileHandle = fopen64(AbsFileName, "rb+");
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

  TRACEEXIT();
  return ret;
}
