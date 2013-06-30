#include "FBLib_ini.h"
#include "../libFireBird.h"

void INICloseFile(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("INICloseFile");
  #endif

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

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
