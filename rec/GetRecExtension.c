#include "libFireBird.h"

char *GetRecExtension(void)
{
  TRACEENTER();

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

  TRACEEXIT();
  return RecExtension ? RecExtension : ".rec";
}
