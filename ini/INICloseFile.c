#include <stdlib.h>
#include "FBLib_ini.h"
#include "../libFireBird.h"

#undef malloc
#undef free

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
