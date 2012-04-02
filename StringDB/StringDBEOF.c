#include                "../libFireBird.h"

bool StringDBEOF(tStringDB *StringDB)
{
  if(!StringDB) return TRUE;

  return (StringDB->DBPtr[0] == '\0');
}
