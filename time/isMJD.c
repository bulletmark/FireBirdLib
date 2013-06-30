#include "../libFireBird.h"

bool isMJD(dword MJD)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("isMJD");
  #endif

  //Check minute
  if((MJD & 0xff) > 59)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  //Check hour
  if(((MJD >> 8) & 0xff) > 23)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  //Check date (2005 to 2020)
  if((((MJD >> 16) & 0xffff) < 0xD07B) || (((MJD >> 16) & 0xffff) > 0xE5E1))
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return TRUE;
}
