#define                 FB_DEBUG_CHK
#define                 FB_LOG_ENTRY_LIB_PRINTF
#include                "libFireBird.h"

void* TAP_MemAlloc_Chk(char *Comment, dword size)
{
  TRACEENTER();

  void                 *ret;

  ret = TAP_MemAlloc(size);

  if(!ret && Comment) LogEntryFBLibPrintf(TRUE, "TAP_MemAlloc_Chk Warning: TAP_MemAlloc(%lu) returned NULL pointer @ %s", size, Comment);

  TRACEEXIT();
  return ret;
}
