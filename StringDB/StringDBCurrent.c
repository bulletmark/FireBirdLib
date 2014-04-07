#include                "../libFireBird.h"

dword StringDBCurrent(tStringDB *StringDB)
{
  TRACEENTER();

  dword ret;

  if(!StringDB)
  {
    TRACEEXIT();
    return '\0';
  }
  ret = (dword)StringDB->DBPtr - (dword)StringDB->DB;

  TRACEEXIT();
  return ret;
}
