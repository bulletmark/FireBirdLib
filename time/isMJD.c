#include "libFireBird.h"

bool isMJD(dword MJD)
{
  TRACEENTER();

  //Check minute
  if((MJD & 0xff) > 59)
  {
    TRACEEXIT();
    return FALSE;
  }

  //Check hour
  if(((MJD >> 8) & 0xff) > 23)
  {
    TRACEEXIT();
    return FALSE;
  }

  //Check date (2005 to 2038)
  if((((MJD >> 16) & 0xffff) < 0xD07B) || (((MJD >> 16) & 0xffff) > 0xFF90))
  {
    TRACEEXIT();
    return FALSE;
  }

  TRACEEXIT();
  return TRUE;
}
