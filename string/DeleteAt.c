#include                <string.h>
#include                "../libFireBird.h"

void DeleteAt(char *SourceString, int Pos, int Len)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("DeleteAt");
  #endif

  char                 *dst, *src;
  int                   l;

  if((SourceString == NULL) || (!*SourceString) || (Len == 0))
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return;
  }

  if(Pos < 0) Pos = 0;
  l = strlenUC(SourceString);

  if((Pos >= l))
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return;
  }

  dst = GetUCPos(SourceString, Pos) - 1;
  src = GetUCPos(dst + 1, Len) - 1;
  if(Pos + Len > l) src++;

  do
  {
    dst++;
    src++;
    *dst = *src;
  }while(*dst);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
