#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "../libFireBird.h"

void SeparateFileNameComponents(char *FileName, char *Path, char *Name, char *Ext, int *Index, bool *isRec, bool *isDel)
{
  TRACEENTER();

  char                 *dot, *slash;

  if(!FileName || !*FileName || !Name)
  {
    TRACEEXIT();
    return;
  }

  slash = strrchr(FileName, '/');
  if(slash)
  {
    if(Path)
    {
      char *c;

      strcpy(Path, FileName);
      c = strrchr(Path, '/');
      if(c) c[1] = '\0';
    }
    strcpy(Name, slash + 1);
  }
  else
  {
    if(Path) Path[0] = '\0';
    strcpy(Name, FileName);
  }

  if(isDel)
  {
    *isDel = FALSE;
    if(StringEndsWith(Name, ".del"))
    {
      *isDel = TRUE;
      Name[strlen(Name) - 4] = '\0';
    }
  }

  if(StringEndsWith(Name, ".rec.inf")) Name[strlen(Name) - 4] = '\0';
  if(StringEndsWith(Name, ".mpg.inf")) Name[strlen(Name) - 4] = '\0';
  if(StringEndsWith(Name, ".rec.nav")) Name[strlen(Name) - 4] = '\0';
  if(StringEndsWith(Name, ".mpg.nav")) Name[strlen(Name) - 4] = '\0';

  if(isRec) *isRec = HDD_isRecFileName(Name);

  dot = strrchr(Name, '.');
  if(Ext)
  {
    Ext[0] = '\0';
    if(dot) strcpy(Ext, dot);
  }
  if(dot) *dot = '\0';

  if(Index)
  {
    *Index = 0;
    if(strlen(Name) > 2)
    {
      if((Name[strlen(Name) - 2] == '-') && isdigit(Name[strlen(Name) - 1]) && (Name[strlen(Name) - 1] != '0'))
      {
        *Index = strtol(&Name[strlen(Name) - 1], NULL, 10);
        Name[strlen(Name) - 2] = '\0';
      }
    }
  }

  TRACEEXIT();
}
