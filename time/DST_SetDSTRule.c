#include                "FBLib_time.h"

tDSTRule                DSTRule = DSTR_Undefined;
dword                   DSTStartUTCsaved = 0, DSTEndUTCsaved = 0;

void DST_SetDSTRule(tDSTRule NewDSTRule)
{
  TRACEENTER();

  DSTRule = NewDSTRule;

  TRACEEXIT();
}
