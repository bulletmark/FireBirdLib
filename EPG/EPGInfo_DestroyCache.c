#include                <unistd.h>
#include                <sys/mman.h>
#include                "FBLib_EPG.h"

void EPGInfo_DestroyCache(void)
{
  TRACEENTER();

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

  TRACEEXIT();
}
