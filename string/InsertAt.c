#include                <string.h>
#include                "libFireBird.h"

void InsertAt(const char *SourceString, int Pos, char *NewString)
{
  TRACEENTER();

  char                 *dst, *src;
  char                 *Target;
  int                   OldLen, NewLen;

  if(!SourceString || !NewString)
  {
    TRACEEXIT();
    return;
  }

  src = SkipCharTableBytes(SourceString);

  if(Pos >= (int)strlenUC(src))
  {
    strcat(src, NewString);

    TRACEEXIT();
    return;
  }

  if(Pos < 0) Pos = 0;

  OldLen = strlen(src);
  NewLen = strlen(NewString);

  dst = &src[OldLen + NewLen];
  *dst = '\0';
  dst--;

  Target = GetUCPos(src, Pos);
  src = &src[OldLen - 1];

  while(src >= Target)
  {
    *dst = *src;
    dst--;
    src--;
  }

  memcpy(Target, NewString, NewLen);

  TRACEEXIT();
}
