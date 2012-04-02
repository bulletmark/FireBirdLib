#include                <string.h>
#include                "../libFireBird.h"

void DeleteAt(char *SourceString, int Pos, int Len)
{
  char                 *dst;

  if((Pos < 0) || (Pos >= (int)strlen(SourceString))) return;
  if(Pos + Len > (int)strlen(SourceString)) return;

  SourceString = SourceString + Pos - 1;
  dst = SourceString;
  SourceString += Len;

  do
  {
    dst++;
    SourceString++;
    *dst = *SourceString;
  }while(*dst);
}
