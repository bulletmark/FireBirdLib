#include <string.h>
#include "FBLib_string.h"

void MakeValidFileName(char *strName, eRemoveChars ControlCharacters)
{
  TRACEENTER();

  char                  Result[FBLIB_DIR_SIZE];

  strcpy(strName, ValidFileName(strName, ControlCharacters, Result, sizeof(Result)));

  TRACEEXIT();
}
