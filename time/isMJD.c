#include "../libFireBird.h"

bool isMJD(dword MJD)
{
  //Check minute
  if((MJD & 0xff) > 59) return FALSE;

  //Check hour
  if(((MJD >> 8) & 0xff) > 23) return FALSE;

  //Check date (2005 to 2020)
  if((((MJD >> 16) & 0xffff) < 0xD07B) || (((MJD >> 16) & 0xffff) > 0xE5E1)) return FALSE;

  return TRUE;
}
