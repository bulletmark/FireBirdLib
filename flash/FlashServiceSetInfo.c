#include                <string.h>
#include                "FBLib_flash.h"

bool FlashServiceSetInfo(int SvcType, int SvcNum, tFlashService *Service)
{
  //SvcType out of range
  if((SvcType < 0) || (SvcType > SVC_TYPE_Radio)) return FALSE;

  //SvcNum out of range
  if((SvcNum < 0) || (SvcNum >= FlashServiceGetTotal(SvcType))) return FALSE;

  //Service is NULL
  if(!Service) return FALSE;

  switch(GetSystemType())
  {
    //Unknown and old 5k/6k systems are not supported
    case ST_UNKNOWN:
    case ST_S:
    case ST_ST:
    case ST_T:
    case ST_C:
    case ST_CT:
    case ST_T5700:
    case ST_T5800:
    case ST_TF7k7HDPVR: return FALSE;

    case ST_TMSS:
    {
      TYPE_Service_TMSS    *p;

      if(SvcType == SVC_TYPE_Tv)
        p = (TYPE_Service_TMSS*)(FIS_vFlashBlockTVServices() + SvcNum * sizeof(TYPE_Service_TMSS));
      else
        p = (TYPE_Service_TMSS*)(FIS_vFlashBlockRadioServices() + SvcNum * sizeof(TYPE_Service_TMSS));
      if(!p) return FALSE;

      return FlashServiceEncode(p, Service);
    }

    case ST_TMST:
    {
      TYPE_Service_TMST    *p;

      if(SvcType == SVC_TYPE_Tv)
        p = (TYPE_Service_TMST*)(FIS_vFlashBlockTVServices() + SvcNum * sizeof(TYPE_Service_TMST));
      else
        p = (TYPE_Service_TMST*)(FIS_vFlashBlockRadioServices() + SvcNum * sizeof(TYPE_Service_TMST));
      if(!p) return FALSE;

      return FlashServiceEncode(p, Service);
    }

    case ST_TMSC:
    {
      TYPE_Service_TMSC    *p;

      if(SvcType == SVC_TYPE_Tv)
        p = (TYPE_Service_TMSC*)(FIS_vFlashBlockTVServices() + SvcNum * sizeof(TYPE_Service_TMSC));
      else
        p = (TYPE_Service_TMSC*)(FIS_vFlashBlockRadioServices() + SvcNum * sizeof(TYPE_Service_TMSC));
      if(!p) return FALSE;

      return FlashServiceEncode(p, Service);
    }

    case ST_NRTYPES: break;
  }

  return FALSE;
}
