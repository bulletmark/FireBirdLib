#include <string.h>
#include "../libFireBird.h"

// take off spaces from a string's end
char *RTrim(char *s)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("RTrim");
  #endif

  char *p;

  if(s)
  {
    if((p = strrchr(s, '\0')))
    {
      p--;

      while(p > s && *p == ' ') p--;

      *++p = '\0';
    }
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return s;
}
