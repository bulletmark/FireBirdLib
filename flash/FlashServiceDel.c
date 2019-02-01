#include                <string.h>
#include                "FBLib_flash.h"

bool FlashServiceDel(int SvcType, int SvcIndex)
{
  TRACEENTER();

  word                 *nSvc;
  bool                  ret;

  //SvcType out of range
  if((SvcType < 0) || (SvcType > SVC_TYPE_Radio))
  {
    TRACEEXIT();
    return FALSE;
  }

  //SvcNum out of range
  if((SvcIndex < 0) || (SvcIndex >= FlashServiceGetTotal(SvcType)))
  {
    TRACEEXIT();
    return FALSE;
  }

  //Prepare the nSvc pointer
  if(SvcType == SVC_TYPE_Tv)
    nSvc = (word*)FIS_vnTvSvc();
  else
    nSvc = (word*)FIS_vnRadioSvc();
  if(!nSvc)
  {
    TRACEEXIT();
    return FALSE;
  }

  ret = FALSE;
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
    case ST_TF7k7HDPVR: break;

    case ST_TMSS:
    {
      TYPE_Service_TMSS    *p;

      FlashServiceDelServiceName(SvcType, SvcIndex);

      if(SvcType == SVC_TYPE_Tv)
        p = (TYPE_Service_TMSS*)(FIS_vFlashBlockTVServices() + SvcIndex * sizeof(TYPE_Service_TMSS));
      else
        p = (TYPE_Service_TMSS*)(FIS_vFlashBlockRadioServices() + SvcIndex * sizeof(TYPE_Service_TMSS));
      if(p && FlashServiceDelete(p))
      {
        *nSvc = *nSvc - 1;

        //TODO: Delete provider

        FlashReindexFavorites(SvcType, SvcIndex, -1);
        FlashReindexTimers(SvcType, SvcIndex, -1);

        ret = TRUE;
      }
      break;
    }

    case ST_TMST:
    {
      TYPE_Service_TMST    *p;

      FlashServiceDelServiceName(SvcType, SvcIndex);

      if(SvcType == SVC_TYPE_Tv)
        p = (TYPE_Service_TMST*)(FIS_vFlashBlockTVServices() + SvcIndex * sizeof(TYPE_Service_TMST));
      else
        p = (TYPE_Service_TMST*)(FIS_vFlashBlockRadioServices() + SvcIndex * sizeof(TYPE_Service_TMST));
      if(p && FlashServiceDelete(p))
      {
        *nSvc = *nSvc - 1;

        //TODO: Delete provider

        FlashReindexFavorites(SvcType, SvcIndex, -1);
        FlashReindexTimers(SvcType, SvcIndex, -1);

        ret = TRUE;
      }
      break;
    }

    case ST_TMSC:
    {
      TYPE_Service_TMSC    *p;

      FlashServiceDelServiceName(SvcType, SvcIndex);

      if(SvcType == SVC_TYPE_Tv)
        p = (TYPE_Service_TMSC*)(FIS_vFlashBlockTVServices() + SvcIndex * sizeof(TYPE_Service_TMSC));
      else
        p = (TYPE_Service_TMSC*)(FIS_vFlashBlockRadioServices() + SvcIndex * sizeof(TYPE_Service_TMSC));
      if(p && FlashServiceDelete(p))
      {
        *nSvc = *nSvc - 1;

        //TODO: Delete provider

        FlashReindexFavorites(SvcType, SvcIndex, -1);
        FlashReindexTimers(SvcType, SvcIndex, -1);

        ret = TRUE;
      }
      break;
    }

    case ST_NRTYPES: break;
  }

  TRACEEXIT();
  return ret;
}
