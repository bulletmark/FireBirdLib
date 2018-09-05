#include "libFireBird.h"

void *TAP_MemRealloc(void *ptr, size_t OldSize, size_t NewSize, bool InitMemory)
{
  TRACEENTER;

  void *temp;

  temp = TAP_MemAlloc(NewSize);
  if(temp == NULL)
  {
    // out of memory!
    LogEntryFBLibPrintf(TRUE, "TAP_MemRealloc: not enough memory (alloc returned NULL)");

    TRACEEXIT;
    return NULL;
  }

  if(ptr && (OldSize > 0))
  {
    memcpy(temp, ptr, OldSize);
    TAP_MemFree(ptr);
  }

  if(InitMemory) memset((byte *) temp + OldSize, 0, NewSize - OldSize);

  TRACEEXIT;
  return temp;
}
