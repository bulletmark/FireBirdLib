#include "../libFireBird.h"

char *GetRecExtension(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("GetRecExtension");
  #endif

  dword                 i;
  tToppyInfo           *ToppyInfo;
  tFWDATHeader         *FWDatHeader;
  static char          *RecExtension = NULL;

  if(RecExtension == NULL)
  {
    if(LoadFirmwareDat(&FWDatHeader, &ToppyInfo, NULL))
    {
      for(i = 0; i < FWDatHeader->NrOfToppyInfoEntries; i++, ToppyInfo++)
      {
        if(ToppyInfo->SysID == TAP_GetSystemId())
        {
          switch(ToppyInfo->RecExtension)
          {
            case 0: RecExtension = ".rec"; break;
            case 1: RecExtension = ".mpg"; break;
              default:
                break;
          }
          break;
        }
      }
    }
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return RecExtension ? RecExtension : ".rec";
}
