#include		"../libFireBird.h"

bool PutDevEvent(word Event, dword Param1)
{
  bool(*__PutDevEvt)(word, dword);

  __PutDevEvt = (void*)FIS_fwPutDevEvt();
  if(!__PutDevEvt) return FALSE;

  return __PutDevEvt(Event, Param1);
}
