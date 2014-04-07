#include "FBLib_ini.h"
#include "../libFireBird.h"

void INICloseFile(void)
{
  TRACEENTER();

  if(INIBuffer != NULL)
  {
    free(INIBuffer);
    INIBuffer = NULL;
    BufferSize = 0;
  }

  if(INICommentBuffer != NULL)
  {
    free(INICommentBuffer);
    INICommentBuffer = NULL;
  }

  TRACEEXIT();
}
