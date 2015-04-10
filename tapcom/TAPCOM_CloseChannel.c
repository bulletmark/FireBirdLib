#include                <stdlib.h>
#include                "FBLib_tapcom.h"

#undef malloc
#undef free

void TAPCOM_CloseChannel(TAPCOM_Channel Channel)
{
  TRACEENTER();

  TAPCOM_InternalMesBuf *buf = (TAPCOM_InternalMesBuf *) Channel;

  if(isValidChannel(Channel) && (buf->FromID == __tap_ud__))
  {
    buf->tapcomSignature = 0;
    free(Channel);
  }

  TRACEEXIT();
}
