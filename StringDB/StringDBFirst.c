#include                "../libFireBird.h"

dword StringDBFirst(tStringDB *StringDB)
{
  if(!StringDB) return '\0';

  StringDB->DBPtr = StringDB->DB;

  return (dword)StringDB->DBPtr - (dword)StringDB->DB;
}
