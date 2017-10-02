#include <stdlib.h>
#include "../libFireBird.h"

#undef free

void PSBuffer_Free(tPSBuffer *PSBuffer)
{
  TRACEENTER();

  if(PSBuffer)
  {
    if(PSBuffer->Buffer[0].PSData) free(PSBuffer->Buffer[0].PSData);
    if(PSBuffer->Buffer[0].FileOffset) free(PSBuffer->Buffer[0].FileOffset);

    if(PSBuffer->Buffer[1].PSData) free(PSBuffer->Buffer[1].PSData);
    if(PSBuffer->Buffer[1].FileOffset) free(PSBuffer->Buffer[1].FileOffset);

    memset(PSBuffer, 0, sizeof(tPSBuffer));
  }

  TRACEEXIT();
}
