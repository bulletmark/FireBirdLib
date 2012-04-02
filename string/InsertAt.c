#include                <string.h>
#include                "../libFireBird.h"

void InsertAt(char *SourceString, int Pos, char *NewString)
{
  char                 *dst;
  char                 *Target;
  int                   OldLen, NewLen;

  if(Pos >= (int)strlen(SourceString))
  {
    strcat(SourceString, NewString);
    return;
  }

  if(Pos < 0) Pos = 0;

  OldLen = strlen(SourceString);
  NewLen = strlen(NewString);

  dst = &SourceString[OldLen + NewLen];
  *dst = '\0';
  dst--;

  Target = &SourceString[Pos];
  SourceString = &SourceString[OldLen - 1];

  while(SourceString >= Target)
  {
    *dst = *SourceString;
    dst--;
    SourceString--;
  }

  memcpy(Target, NewString, NewLen);
}
