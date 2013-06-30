#include <string.h>
#include "../libFireBird.h"

bool StringEndsWith(char *text, char *postfix)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("StringEndsWith");
  #endif

  char                 *p;
  int                   i;
  bool                  ret;

  if(!text || !*text || !postfix || !*postfix)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  i = strlen(postfix);
  p = &text[strlen(text) - i];
  ret = (memcmp(p, postfix, i) == 0);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
