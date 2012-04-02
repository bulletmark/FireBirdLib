#include                "../libFireBird.h"

dword StringDBCurrent(tStringDB *StringDB)
{
  if(!StringDB) return '\0';

  return (dword)StringDB->DBPtr - (dword)StringDB->DB;
}
