#include "libFireBird.h"

bool HDD_isCryptedStream(byte *Buffer, dword BufferSize)
{
  TRACEENTER();

  dword                 i;
  bool                  ret;

  ret = FALSE;
  for(i = 0; i < BufferSize; i += 188)
    if((Buffer[i] == 0x47) && ((Buffer[i + 3] & 0xC0) != 0))
    {
      ret = TRUE;
      break;
    }

  TRACEEXIT();
  return ret;
}
