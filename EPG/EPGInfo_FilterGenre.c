#include                <stdlib.h>
#include                "FBLib_EPG.h"

void EPGInfo_FilterGenre(byte *GenreArray, byte GenreArraySize)
{
  TRACEENTER();

  if(GenreArray && GenreArraySize)
  {
    TAP_MemFree(EPGFilter.GenreArray);
    EPGFilter.GenreArray = TAP_MemAlloc(GenreArraySize);
    if(EPGFilter.GenreArray)
    {
      memcpy(EPGFilter.GenreArray, GenreArray, GenreArraySize);
      EPGFilter.GenreArraySize = GenreArraySize;
      EPGFilter.GenreFilter = TRUE;
    }
    else
    {
      //Something went wrong during the memory allocation for the genre array
      EPGFilter.GenreFilter = FALSE;
      EPGFilter.GenreArraySize = 0;
    }
  }
  else
  {
    EPGFilter.GenreFilter = FALSE;
    TAP_MemFree(EPGFilter.GenreArray);
    EPGFilter.GenreArray = NULL;
    EPGFilter.GenreArraySize = 0;
  }

  TRACEEXIT();
}
