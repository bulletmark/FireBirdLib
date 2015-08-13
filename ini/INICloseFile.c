#include <stdlib.h>
#include "FBLib_ini.h"
#include "../libFireBird.h"

void INICloseFile(void)
{
  TRACEENTER();

  if(INIBuffer != NULL)
  {
    TAP_MemFree(INIBuffer);
    INIBuffer = NULL;
    BufferSize = 0;
  }

  if(INICommentBuffer != NULL)
  {
    TAP_MemFree(INICommentBuffer);
    INICommentBuffer = NULL;
  }

  TRACEEXIT();
}
