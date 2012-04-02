#include "../libFireBird.h"

dword UTCtoLocal(dword UTCTime)
{
  static dword (*Appl_TimeToLocal)(dword) = NULL;

  if(!Appl_TimeToLocal)
  {
    Appl_TimeToLocal = (void*)FIS_fwApplTimeToLocal();
    if(!Appl_TimeToLocal) return 0;
  }

  return Appl_TimeToLocal(UTCTime);
}
