#include <stdio.h>
#include "libFireBird.h"

TYPE_File *HDD_FappendOpen(char *FileName)
{
  TRACEENTER();

  TYPE_File            *file;
  char                  buffer[512];
  dword                 pos, blks, i;
  char                 *end;
  char                  TAPPath[FBLIB_DIR_SIZE], Name[FBLIB_DIR_SIZE];

  if(!FileName || !*FileName)
  {
    TRACEEXIT();
    return NULL;
  }

  ConvertPathType(FileName, TAPPath, PF_TAPPathOnly);
  ConvertPathType(FileName, Name, PF_FileNameOnly);

  HDD_TAP_PushDir();
  if(*TAPPath) HDD_ChangeDir(TAPPath);

  if(!TAP_Hdd_Exist(Name)) TAP_Hdd_Create(Name, ATTR_NORMAL);

  if((file = TAP_Hdd_Fopen(Name)))
  {
    if(TAP_Hdd_Fseek(file, 0, SEEK_SET) != 0)
    {
      TAP_Hdd_Fclose(file);
      file = NULL;
    }
    else
    {
      pos = 0;

      do
      {
        memset(buffer, 0, sizeof(buffer));
        blks = TAP_Hdd_Fread(&buffer, sizeof(buffer), 1, file);

        for(i = 0, end = buffer; i < sizeof(buffer); i++)
          if(buffer[i] == '\0')
          {
            end = buffer + i;
            break;
          }

        if(i < sizeof(buffer)) break;
        else pos += sizeof(buffer);
      }
      while(blks == 1);

      pos += end - buffer;

      if(TAP_Hdd_Fseek(file, pos, SEEK_SET) != pos)
      {
        TAP_Hdd_Fclose(file);
        file = NULL;
      }
    }
  }

  HDD_TAP_PopDir();

  TRACEEXIT();
  return file;
}
