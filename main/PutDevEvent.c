#include		"libFireBird.h"

bool PutDevEvent(word Event, dword Param1)
{
  TRACEENTER;

  bool(*__PutDevEvt)(word, dword);
  bool ret;

  ret = FALSE;

  __PutDevEvt = (void*)FIS_fwPutDevEvt();
  if(__PutDevEvt) ret = __PutDevEvt(Event, Param1);

  TRACEEXIT;
  return ret;
}
