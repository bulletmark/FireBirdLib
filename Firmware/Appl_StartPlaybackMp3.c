#include                "libFireBird.h"

//returns 0 on ok or 1 on failure

int Appl_StartPlaybackMp3(char *FileName)
{
  TRACEENTER;

  int  (*__Appl_StartPlaybackMp3)(char const*);
  int  ret = 1;

  __Appl_StartPlaybackMp3 = (void*)FIS_fwAppl_StartPlaybackMp3();
  if(__Appl_StartPlaybackMp3) ret = __Appl_StartPlaybackMp3(FileName);

  TRACEEXIT;
  return ret;
}
