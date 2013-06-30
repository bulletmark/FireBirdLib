#include                <string.h>
#include                "FBLib_flash.h"

bool FlashServiceDel(int SvcType, int SvcNum)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FlashServiceDel");
  #endif

  word                 *nSvc;
  bool                  ret;

  //SvcType out of range
  if((SvcType < 0) || (SvcType > SVC_TYPE_Radio))
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  //SvcNum out of range
  if((SvcNum < 0) || (SvcNum >= FlashServiceGetTotal(SvcType)))
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  //Prepare the nSvc pointer
  if(SvcType == SVC_TYPE_Tv)
    nSvc = (word*)FIS_vnTvSvc();
  else
    nSvc = (word*)FIS_vnRadioSvc();
  if(!nSvc)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

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

      FlashServiceDelServiceName(SvcType, SvcNum);

      if(SvcType == SVC_TYPE_Tv)
        p = (TYPE_Service_TMSS*)(FIS_vFlashBlockTVServices() + SvcNum * sizeof(TYPE_Service_TMSS));
      else
        p = (TYPE_Service_TMSS*)(FIS_vFlashBlockRadioServices() + SvcNum * sizeof(TYPE_Service_TMSS));
      if(p && FlashServiceDelete(p))
      {
        *nSvc = *nSvc - 1;

        //TODO: Delete provider

        FlashReindexFavorites(SvcType, SvcNum, -1);
        FlashReindexTimers(SvcType, SvcNum, -1);

        ret = TRUE;
      }
      break;
    }

    case ST_TMST:
    {
      TYPE_Service_TMST    *p;

      FlashServiceDelServiceName(SvcType, SvcNum);

      if(SvcType == SVC_TYPE_Tv)
        p = (TYPE_Service_TMST*)(FIS_vFlashBlockTVServices() + SvcNum * sizeof(TYPE_Service_TMST));
      else
        p = (TYPE_Service_TMST*)(FIS_vFlashBlockRadioServices() + SvcNum * sizeof(TYPE_Service_TMST));
      if(p && FlashServiceDelete(p))
      {
        *nSvc = *nSvc - 1;

        //TODO: Delete provider

        FlashReindexFavorites(SvcType, SvcNum, -1);
        FlashReindexTimers(SvcType, SvcNum, -1);

        ret = TRUE;
      }
      break;
    }

    case ST_TMSC:
    {
      TYPE_Service_TMSC    *p;

      FlashServiceDelServiceName(SvcType, SvcNum);

      if(SvcType == SVC_TYPE_Tv)
        p = (TYPE_Service_TMSC*)(FIS_vFlashBlockTVServices() + SvcNum * sizeof(TYPE_Service_TMSC));
      else
        p = (TYPE_Service_TMSC*)(FIS_vFlashBlockRadioServices() + SvcNum * sizeof(TYPE_Service_TMSC));
      if(p && FlashServiceDelete(p))
      {
        *nSvc = *nSvc - 1;

        //TODO: Delete provider

        FlashReindexFavorites(SvcType, SvcNum, -1);
        FlashReindexTimers(SvcType, SvcNum, -1);

        ret = TRUE;
      }
      break;
    }

    case ST_NRTYPES: break;
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
