#include "../libFireBird.h"

dword UTCtoLocal(dword UTCTime)
{
  dword (*Appl_TimeToLocal)(dword);

  Appl_TimeToLocal = (void*)FIS_fwApplTimeToLocal();
  if(!Appl_TimeToLocal) return 0;

  return Appl_TimeToLocal(UTCTime);
}
