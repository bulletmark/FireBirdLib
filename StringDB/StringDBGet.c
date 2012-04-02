#include                "../libFireBird.h"

char *StringDBGet(tStringDB *StringDB, dword Index)
{
  if(!StringDB) return '\0';

  return StringDB->DB + Index;
}
