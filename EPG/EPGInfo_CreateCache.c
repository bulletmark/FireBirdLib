#include                <stdio.h>
#include                <stdlib.h>
#include                <fcntl.h>
#include                <unistd.h>
#include                <sys/mman.h>
#include                <sys/stat.h>
#include                "FBLib_EPG.h"

bool EPGInfo_CreateCache(int NrRecords)
{
  TRACEENTER;

  extern dword __tap_ud__;

  TAP_SPrint(EPGCacheFile, "/mnt/hd/tmp/EPGCache_%x.bin", __tap_ud__);

  if(EPGInfoCacheFile) EPGInfo_DestroyCache();

  EPGInfoCacheSize = NrRecords * sizeof(TYPE_EPGInfo);

  //Delete the old cache
  unlink(EPGCacheFile);

  mkdir("/mnt/hd/tmp", 0777);
  EPGInfoCacheFile = open(EPGCacheFile, O_RDWR | O_CREAT | O_TRUNC, (mode_t)0600);

  if(EPGInfoCacheFile == -1)
  {
    LogEntryFBLibPrintf(TRUE, "EPGInfo: failed to create the memory mapped EPG cache");

    TRACEEXIT;
    return FALSE;
  }

  //Increase the size of the cache as needed
  if(lseek(EPGInfoCacheFile, EPGInfoCacheSize, SEEK_SET) == -1)
  {
    LogEntryFBLibPrintf(TRUE, "EPGInfo: failed to stretch the memory mapped EPG cache");
    close(EPGInfoCacheFile);
    unlink(EPGCacheFile);

    TRACEEXIT;
    return FALSE;
  }
  write(EPGInfoCacheFile, "", 1);

  //Map the memory
  EPGInfoCacheMap = mmap(0, EPGInfoCacheSize, PROT_READ | PROT_WRITE, MAP_SHARED, EPGInfoCacheFile, 0);
  if(EPGInfoCacheMap == MAP_FAILED)
  {
    LogEntryFBLibPrintf(TRUE, "EPGInfo: failed to memory map the EPG cache file");
    close(EPGInfoCacheFile);
    unlink(EPGCacheFile);

    TRACEEXIT;
    return FALSE;
  }

  EPGInfoCache = (TYPE_EPGInfo*)EPGInfoCacheMap;

  TRACEEXIT;
  return TRUE;
}
