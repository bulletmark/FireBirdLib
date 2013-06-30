#include <string.h>
#ifndef _TMSEMU_
  #include <ctype.h>
#endif
#include "FBLib_string.h"

// case-insensitive version of strstr()
char *stricstr(char *s1, char *s2)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("stricstr");
  #endif

  bool found = FALSE;
  char start[3];
  char *str = NULL;

  if(!s1 || !s2)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return NULL;
  }

  s1 = SkipCharTableBytes(s1);
  s2 = SkipCharTableBytes(s2);

  if(*s2)
  {
    size_t len = strlen(s2) - 1;

    start[0] = toupper(*s2);
    start[1] = tolower(*s2);
    start[2] = '\0';

    s2++;

    do
    {
      if((str = strpbrk(s1, start)))
      {
        s1 = str + 1;
        found = (strncasecmp(s1, s2, len) == 0);
      }
    }
    while(str && !found && *s1);
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return (found ? str : NULL);
}
