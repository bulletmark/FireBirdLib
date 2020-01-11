#include <string.h>
#include "libFireBird.h"

bool StringEndsWith(const char *text, const char *postfix)
{
  TRACEENTER();

  const char           *p;
  int                   l, i;
  bool                  ret = FALSE;

  if(!text || !*text || !postfix || !*postfix)
  {
    TRACEEXIT();
    return FALSE;
  }

  l = strlen(text);
  i = strlen(postfix);

  if (l >= i)
  {
    p = &text[l - i];
    ret = (memcmp(p, postfix, i) == 0);
  }

  TRACEEXIT();
  return ret;
}
