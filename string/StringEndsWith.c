#include <string.h>
#include "../libFireBird.h"

bool StringEndsWith(char *text, char *postfix)
{
  char                 *p;
  int                   i;

  i = strlen(postfix);
  p = &text[strlen(text) - i];

  return (strncmp(p, postfix, i) == 0);
}
