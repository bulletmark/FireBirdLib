#include <string.h>
#include "FBLib_string.h"

char *ParseLine(char *zeile, size_t *n, char delim)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("ParseLine");
  #endif

  char *p;

  if(!zeile || !*zeile)
  {
    *n = 0;

    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return NULL;
  }

  if(*zeile == delim) zeile++;

  if((p = strchr(zeile, delim)))
  {
    *n = p - zeile;

    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return zeile;
  }
  else
  {
    *n = strlen(zeile);

    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif


    return zeile;
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
