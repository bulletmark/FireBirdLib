#include <string.h>
#include "FBLib_string.h"

char *ParseLine(const char *zeile, size_t *n, char delim)
{
  TRACEENTER();

  char *p;

  if(!zeile || !*zeile)
  {
    *n = 0;

    TRACEEXIT();
    return NULL;
  }

  if(*zeile == delim) zeile++;

  if((p = strchr(zeile, delim)))
  {
    *n = p - zeile;

    TRACEEXIT();
    return (char *) zeile;
  }
  else
  {
    *n = strlen(zeile);

    TRACEEXIT();

    return (char *) zeile;
  }

  TRACEEXIT();
}
