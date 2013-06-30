#include                <unistd.h>
#include                <sys/mman.h>
#include                "FBLib_EPG.h"

void EPGInfo_DestroyCache(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("EPGInfo_DestroyCache");
  #endif

  if(EPGInfoCacheMap)
  {
    //Release the mapped memory
    msync(EPGInfoCacheMap, EPGInfoCacheSize, MS_SYNC);
    munmap(EPGInfoCacheMap, EPGInfoCacheSize);
    EPGInfoCacheMap = NULL;
    EPGInfoCache = NULL;
    EPGInfoCacheSize = 0;
    EPGInfoCacheEntries = 0;
    EPGInfoNrEntries = 0;

    //Close and delete the cache file
    close(EPGInfoCacheFile);
    unlink(EPGCacheFile);
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
