#include <stdio.h>
#include <string.h>
#include "libFireBird.h"

bool FixInvalidFileName(char *FileName)
{
  TRACEENTER();

  char                  NewRecName[TS_FILE_NAME_SIZE+5];
  char                 *Slash, Path[FBLIB_DIR_SIZE];
  bool                  ret;

  ret = FALSE;
  if(FileName && *FileName && HDD_Exist(FileName))
  {
    memset(NewRecName, 0, sizeof(NewRecName));

    //Check if the file is busy
    if(HDD_isFileInUse(FileName) != FIU_No)
    {
      TRACEEXIT();
      return FALSE;
    }

    Slash = strrchr(FileName, '/');
    if(Slash)
    {
      dword i;

      i = (dword)Slash - (dword)FileName + 1;
      strncpy(Path, FileName, i);
      Path[i] = '\0';
      strcpy(NewRecName, Slash + 1);
    }
    else
    {
      Path[0] = '\0';
      strcpy(NewRecName, FileName);
    }

    //If necessary, convert to UTF8
    if(isUTFToppy())
    {
      //Use ISO 8859-9 as the default encoding table
      StrMkUTF8(NewRecName, 9);
    }
    else
    {
      MakeValidFileName(NewRecName, ControlChars);
    }
    if(*Path) InsertAt(NewRecName, 0, Path);

    if(!strcmp(FileName, NewRecName))
    {
      //No need to rename
      TRACEEXIT();
      return TRUE;
    }

    MakeUniqueFileName(NewRecName);
    ret = HDD_Rename(FileName, NewRecName);
    strcpy(FileName, NewRecName);
  }

  TRACEEXIT();
  return ret;
}
