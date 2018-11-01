#include                "libFireBird.h"

//returns 0 on ok or 1 on failure

int Appl_StartPlaybackDivx(char *FileName, unsigned int p2, bool p3)
{
  TRACEENTER();

  int  (*__Appl_StartPlaybackDivx)(char const*, unsigned int, bool);
  int  ret = 1;

  __Appl_StartPlaybackDivx = (void*)FIS_fwAppl_StartPlaybackDivx();
  if(__Appl_StartPlaybackDivx) ret = __Appl_StartPlaybackDivx(FileName, p2, p3);

  TRACEEXIT();
  return ret;
}
