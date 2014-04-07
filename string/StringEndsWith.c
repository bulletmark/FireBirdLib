#include <string.h>
#include "../libFireBird.h"

bool StringEndsWith(char *text, char *postfix)
{
  TRACEENTER();

  char                 *p;
  int                   i;
  bool                  ret;

  if(!text || !*text || !postfix || !*postfix)
  {
    TRACEEXIT();
    return FALSE;
  }

  i = strlen(postfix);
  p = &text[strlen(text) - i];
  ret = (memcmp(p, postfix, i) == 0);

  TRACEEXIT();
  return ret;
}
