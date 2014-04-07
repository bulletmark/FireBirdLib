#include <string.h>
#include "FBLib_string.h"

void MakeValidFileName(char *strName, eRemoveChars ControlCharacters)
{
  TRACEENTER();

  strcpy(strName, ValidFileName(strName, ControlCharacters));

  TRACEEXIT();
}
