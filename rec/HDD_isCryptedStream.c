#include "../libFireBird.h"

bool HDD_isCryptedStream(char *Buffer, dword BufferSize)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_isCryptedStream");
  #endif

  dword                 i;
  bool                  ret;

  ret = FALSE;
  for(i = 0; i < BufferSize; i += 188)
    if((Buffer[i] == 0x47) && ((Buffer[i + 3] & 0xC0) != 0))
    {
      ret = TRUE;
      break;
    }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
