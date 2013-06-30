#ifndef _TMSEMU_
  #include <ctype.h>
#endif
#include <string.h>
#include <stdlib.h>
#include "../libFireBird.h"

void SeparateFileNameComponents(char *FileName, char *Name, char *Ext, int *Index, bool *isRec, bool *isDel)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("SeparateFileNameComponents");
  #endif

  char                 *dot;

  if(!FileName || !*FileName || !Name)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return;
  }

  strcpy(Name, FileName);

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

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
