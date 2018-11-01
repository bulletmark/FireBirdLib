#include <string.h>
#include <stdlib.h>
#include "libFireBird.h"

char *HDD_MakeNewRecName(char *fname, word sequence, char *NewRecName, int NewRecNameSize)
{
  TRACEENTER();

  char                  try[FBLIB_DIR_SIZE], *Slash;
  size_t                len;
  char                  *p;
  int                   j;
  char                  c1, c2;

  if(NewRecName && NewRecNameSize)
  {
    memset(NewRecName, 0, NewRecNameSize);
    memset(try, 0, sizeof(try));

    Slash = strrchr(fname, '/');
    if(Slash)
    {
      int i;

      i = (dword)Slash - (dword)fname + 1;

      if(i >= NewRecNameSize)
      {
        //Not enough space in NewRecName
        TRACEEXIT();
        return NewRecName;
      }
      strncpy(NewRecName, fname, i);
      strncpy(try, Slash + 1, sizeof(try));
    }
    else
    {
      strncpy(try, fname, sizeof(try));
    }

    len = strlen(try);

    if(!(p = strrchr(try, '.'))) p = try + len;
    if((j = MAX_FILE_NAME_SIZE - len - 4) < 0)
    {
      strcpy(p + j, p);
      p += j;
    }

    memmove(p + 3, p, strlen(p) + 1);

    if(sequence)
    {
      c1 = sequence / 10 % 10 + '0';
      c2 = sequence % 10 + '0';
      p[0] = '-';
    }
    else
    {
      srand(TAP_GetTick());
      c1 = rand() % 26 + 'A';
      c2 = rand() % 26 + 'A';
      p[0] = ' ';
    }

    p[1] = c1;
    p[2] = c2;

    if((strlen(NewRecName) + strlen(try)) >= (dword)NewRecNameSize)
    {
      //Not enough space in NewRecName
      TRACEEXIT();
      return NewRecName;
    }

    strcat(NewRecName, try);
  }

  TRACEEXIT();
  return NewRecName;
}
