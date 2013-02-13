#include                <string.h>
#include                "FBLib_flash.h"

bool FlashServiceDecode(void *Data, tFlashService *Service)
{
  //Service is NULL
  if(!Data || !Service) return FALSE;

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

    case ST_TMSS: return FlashServiceDecode_ST_TMSS(Data, Service);
    case ST_TMST: return FlashServiceDecode_ST_TMST(Data, Service);
    case ST_TMSC: return FlashServiceDecode_ST_TMSC(Data, Service);

    case ST_NRTYPES: break;
  }

  return FALSE;
}

bool FlashServiceDecode_ST_TMSS(TYPE_Service_TMSS *Data, tFlashService *Service)
{

  char                 *Text;

  memset(Service, 0, sizeof(tFlashService));
  Service->SatIndex        = Data->SatIdx;
  Service->VideoStreamType = Data->VideoStreamType;
  Service->FlagDelete      = Data->DelFlag;
  Service->FlagCAS         = Data->CASFlag;
  Service->FlagLock        = Data->LockFlag;
  Service->FlagSkip        = Data->SkipFlag;
  Service->Tuner           = Data->TunerNum;
  Service->TransponderIndex= Data->TPIdx;
  Service->ServiceID       = Data->SVCID;
  Service->PMTPID          = Data->PMTPID;
  Service->PCRPID          = Data->PCRPID;
  Service->VideoPID        = Data->VideoPID;
  Service->AudioPID        = Data->AudioPID;
  Service->LCN             = Data->LCN;
  Service->AudioStreamType = Data->AudioStreamType;
  Service->NameLock        = Data->NameLock;
  Service->Flags2          = Data->Flags2;
  memcpy(Service->unknown2, Data->unknown2, 6);

  Text = (char*)(FIS_vFlashBlockServiceName() + Data->NameOffset);
  strncpy(Service->ServiceName, Text, MAX_SvcName - 1);

  Text = (char*)(FIS_vFlashBlockProviderInfo() + 21 * Data->ProviderIdx);
  strncpy(Service->ProviderName, Text, 20);

  return TRUE;
}

bool FlashServiceDecode_ST_TMST(TYPE_Service_TMST *Data, tFlashService *Service)
{
  //The TV and radio service structures are identical
  return FlashServiceDecode_ST_TMSS(Data, Service);
}

bool FlashServiceDecode_ST_TMSC(TYPE_Service_TMSC *Data, tFlashService *Service)
{
  //The TV and radio service structures are identical
  return FlashServiceDecode_ST_TMSS(Data, Service);
}


bool FlashServiceEncode(void *Data, tFlashService *Service)
{
  //Service is NULL
  if(!Data || !Service) return FALSE;

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

    case ST_TMSS: return FlashServiceEncode_ST_TMSS(Data, Service);
    case ST_TMST: return FlashServiceEncode_ST_TMST(Data, Service);
    case ST_TMSC: return FlashServiceEncode_ST_TMSC(Data, Service);

    case ST_NRTYPES: break;
  }

  return FALSE;
}

bool FlashServiceEncode_ST_TMSS(TYPE_Service_TMSS *Data, tFlashService *Service)
{
  bool                  isRadio;
  int                   ServiceIndex;

  char *(*Appl_AddSvcName)(char const*);
  void  (*Appl_DeleteTvSvcName)(unsigned short, bool);
  void  (*Appl_DeleteRadioSvcName)(unsigned short, bool);
  word  (*Appl_SetProviderName)(char const*);

  isRadio = (dword)Data >= FIS_vFlashBlockRadioServices();

  //Change the service name if necessary
  if(isRadio)
  {
    ServiceIndex = ((dword)Data - FIS_vFlashBlockRadioServices()) / sizeof(TYPE_Service_TMSS);
    Appl_DeleteRadioSvcName = (void*)FIS_fwAppl_DeleteRadioSvcName();
    if(Appl_DeleteRadioSvcName) Appl_DeleteRadioSvcName(ServiceIndex, FALSE);
  }
  else
  {
    ServiceIndex = ((dword)Data - FIS_vFlashBlockTVServices()) / sizeof(TYPE_Service_TMSS);
    Appl_DeleteTvSvcName = (void*)FIS_fwAppl_DeleteTvSvcName();
    if(Appl_DeleteTvSvcName) Appl_DeleteTvSvcName(ServiceIndex, FALSE);
  }

  memset(Data, 0, sizeof(TYPE_Service_TMSS));
  Data->SatIdx          = Service->SatIndex;
  Data->VideoStreamType = Service->VideoStreamType;
  Data->DelFlag         = Service->FlagDelete;
  Data->CASFlag         = Service->FlagCAS;
  Data->LockFlag        = Service->FlagLock;
  Data->SkipFlag        = Service->FlagSkip;
  Data->TunerNum        = Service->Tuner;
  Data->TPIdx           = Service->TransponderIndex;
  Data->SVCID           = Service->ServiceID;
  Data->PMTPID          = Service->PMTPID;
  Data->PCRPID          = Service->PCRPID;
  Data->VideoPID        = Service->VideoPID;
  Data->AudioPID        = Service->AudioPID;
  Data->LCN             = Service->LCN;
  Data->AudioStreamType = Service->AudioStreamType;
  Data->NameLock        = Service->NameLock;
  Data->Flags2          = Service->Flags2;
  memcpy(Data->unknown2, Service->unknown2, 6);

  Appl_AddSvcName = (void*)FIS_fwAppl_AddSvcName();
  if(Appl_AddSvcName) Data->NameOffset = (dword)Appl_AddSvcName(Service->ServiceName);

  //Update the provider name
  Appl_SetProviderName = (void*)FIS_fwAppl_SetProviderName();
  if(Appl_SetProviderName) Data->ProviderIdx = Appl_SetProviderName(Service->ProviderName);

  return TRUE;
}

bool FlashServiceEncode_ST_TMST(TYPE_Service_TMST *Data, tFlashService *Service)
{
  //The TV and radio service structures are identical
  return FlashServiceEncode_ST_TMSS(Data, Service);
}

bool FlashServiceEncode_ST_TMSC(TYPE_Service_TMSC *Data, tFlashService *Service)
{
  //The TV and radio service structures are identical
  return FlashServiceEncode_ST_TMSS(Data, Service);
}

bool FlashServiceDelete(void *Data)
{
  //Service is NULL
  if(!Data) return FALSE;

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

    case ST_TMSS: return FlashServiceDelete_ST_TMSS(Data);
    case ST_TMST: return FlashServiceDelete_ST_TMST(Data);
    case ST_TMSC: return FlashServiceDelete_ST_TMSC(Data);

    case ST_NRTYPES: break;
  }

  return FALSE;
}

bool FlashServiceDelete_ST_TMSS(TYPE_Service_TMSS *Data)
{
  TYPE_Service_TMSS    *NextData;

  NextData = Data + 1;

  while(NextData->TunerNum != 0)
  {
    memcpy(Data, NextData, sizeof(TYPE_Service_TMSS));
    Data++;
    NextData++;
  }
  memset(Data, 0, sizeof(TYPE_Service_TMSS));

  return TRUE;
}

bool FlashServiceDelete_ST_TMST(TYPE_Service_TMST *Data)
{
  //The TV and radio service structures are identical
  return FlashServiceDelete_ST_TMSS(Data);
}

bool FlashServiceDelete_ST_TMSC(TYPE_Service_TMSC *Data)
{
  //The TV and radio service structures are identical
  return FlashServiceDelete_ST_TMSS(Data);
}

bool FlashServiceDelServiceName(int SvcType, int SvcNum)
{
  void (*Appl_DeleteTvSvcName)(unsigned short, bool);
  void (*Appl_DeleteRadioSvcName)(unsigned short, bool);

  if(SvcType == SVC_TYPE_Tv)
  {
    Appl_DeleteTvSvcName = (void*)FIS_fwAppl_DeleteTvSvcName();
    if(!Appl_DeleteTvSvcName) return FALSE;
    Appl_DeleteTvSvcName(SvcNum, FALSE);
  }
  else
  {
    Appl_DeleteRadioSvcName = (void*)FIS_fwAppl_DeleteRadioSvcName();
    if(!Appl_DeleteRadioSvcName) return FALSE;
    Appl_DeleteRadioSvcName(SvcNum, FALSE);
  }

  return TRUE;
}

//Set FromSvcNum = -1 when adding a service entry
//or  ToSvcNum = -1 to deleting a service entry
void FlashReindexFavorites(int SvcType, int FromSvcNum, int ToSvcNum)
{
  tFavorites           *Favorites;
  int                   i, j;

  Favorites = (tFavorites*)FIS_vFlashBlockFavoriteGroup();

  for(i = 0; i < MAXFAVS; i++)
  {
    if(Favorites->GroupName[0] && Favorites->NrEntries)
    {
      j = 0;
      while(j < Favorites->NrEntries)
      {
        if(Favorites->SvcType[j] == SvcType)
        {
          if(FromSvcNum == -1)
          {
            //Case 1: a new service has been inserted at ToSvcNum
            if(Favorites->SvcNum[j] >= ToSvcNum) Favorites->SvcNum[j]++;
          }
          else if(ToSvcNum == -1)
          {
            //Case 2: a service has been deleted at FromSvcNum
            if(Favorites->SvcNum[j] >= FromSvcNum)
            {
              if(Favorites->SvcNum[j] == FromSvcNum)
              {
                memcpy(&Favorites->SvcNum[j], &Favorites->SvcNum[j + 1], (100 - j - 1) * sizeof(word));
                Favorites->SvcNum[99] = 0;
                Favorites->NrEntries--;
              }
              else
                Favorites->SvcNum[j]--;
            }
          }
          else if(FromSvcNum < ToSvcNum)
          {
            //Case 3: a service has been moved up
            if((Favorites->SvcNum[j] >= FromSvcNum) && (Favorites->SvcNum[j] <= ToSvcNum))
            {
              if(Favorites->SvcNum[j] == FromSvcNum)
                Favorites->SvcNum[j] = ToSvcNum;
              else
                Favorites->SvcNum[j]--;
            }
          }
          else
          {
            //Case 4: a service has been moved down
            if((Favorites->SvcNum[j] <= FromSvcNum) && (Favorites->SvcNum[j] >= ToSvcNum))
            {
              if(Favorites->SvcNum[j] == FromSvcNum)
                Favorites->SvcNum[j] = ToSvcNum;
              else
                Favorites->SvcNum[j]++;
            }
          }
        }
        j++;
      }
    }
    Favorites++;
  }
}

void FlashReindexTimers(int SvcType, int FromSvcNum, int ToSvcNum)
{
  int                   NrTimer, i;
  TYPE_TimerInfo        TimerInfo;

  NrTimer = TAP_Timer_GetTotalNum();
  for(i = NrTimer - 1; i >= 0; i--)
  {
    TAP_Timer_GetInfo(i, &TimerInfo);
    if(TimerInfo.svcType == SvcType)
    {
      if(FromSvcNum == -1)
      {
        //Case 1: a new service has been inserted at ToSvcNum
        if(TimerInfo.svcNum >= ToSvcNum)
        {
          TimerInfo.svcNum++;
          TAP_Timer_Modify(i, &TimerInfo);
        }
      }
      else if(ToSvcNum == -1)
      {
        //Case 2: a service has been deleted at FromSvcNum
        if(TimerInfo.svcNum >= FromSvcNum)
        {
          if(TimerInfo.svcNum == FromSvcNum)
          {
            TAP_Timer_Delete(i);
          }
          else
          {
            TimerInfo.svcNum--;
            TAP_Timer_Modify(i, &TimerInfo);
          }
        }
      }
      else if(FromSvcNum < ToSvcNum)
      {
        //Case 3: a service has been moved up
        if((TimerInfo.svcNum >= FromSvcNum) && (TimerInfo.svcNum <= ToSvcNum))
        {
          if(TimerInfo.svcNum == FromSvcNum)
          {
            TimerInfo.svcNum = ToSvcNum;
            TAP_Timer_Modify(i, &TimerInfo);
          }
          else
          {
            TimerInfo.svcNum--;
            TAP_Timer_Modify(i, &TimerInfo);
          }
        }
      }
      else
      {
        //Case 4: a service has been moved down
        if((TimerInfo.svcNum <= FromSvcNum) && (TimerInfo.svcNum >= ToSvcNum))
        {
          if(TimerInfo.svcNum == FromSvcNum)
          {
            TimerInfo.svcNum = ToSvcNum;
            TAP_Timer_Modify(i, &TimerInfo);
          }
          else
          {
            TimerInfo.svcNum++;
            TAP_Timer_Modify(i, &TimerInfo);
          }
        }
      }
    }
  }
}
