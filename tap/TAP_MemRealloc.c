#include "../libFireBird.h"

void *TAP_MemRealloc(void *ptr, size_t OldSize, size_t NewSize, bool InitMemory)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("TAP_MemRealloc");
  #endif

  void *temp;

  temp = TAP_MemAlloc(NewSize);
  if(temp == NULL)
  {
    // out of memory!
    //TAP_Print("not enough memory (alloc returned NULL)\n");

    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return NULL;
  }

  if(ptr && (OldSize > 0))
  {
    memcpy(temp, ptr, OldSize);
    TAP_MemFree(ptr);
  }

  if(InitMemory) memset(temp + OldSize, 0, NewSize - OldSize);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return temp;
}
