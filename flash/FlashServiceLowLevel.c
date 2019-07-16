#include                <string.h>
#include                "FBLib_flash.h"

static bool FlashServiceDecode_ST_TMSS(TYPE_Service_TMSS *Data, tFlashService *Service)
{
  char                 *Text;

  TRACEENTER();

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
  Service->AudioTypeFlag   = Data->AudioTypeFlag;
  Service->AudioAutoSelect = Data->AudioAutoSelect;
  Service->LCN             = Data->LCN;
  Service->AudioStreamType = Data->AudioStreamType;
  Service->NameLock        = Data->NameLock;
  Service->Flags2          = Data->Flags2;
  memcpy(Service->unknown2, Data->unknown2, 6);

  Text = (char*)(FIS_vFlashBlockServiceName() + Data->NameOffset);
  strncpy(Service->ServiceName, Text, MAX_SvcName);

  if(Data->ProviderIdx < 256)
  {
    Text = (char*)(FIS_vFlashBlockProviderInfo() + 21 * Data->ProviderIdx);
    strncpy(Service->ProviderName, Text, 20);
  }

  TRACEEXIT();
  return TRUE;
}

static bool FlashServiceDecode_ST_TMST(TYPE_Service_TMST *Data, tFlashService *Service)
{
  bool ret;

  TRACEENTER();

  //The TV and radio service structures are identical
  ret = FlashServiceDecode_ST_TMSS(Data, Service);

  TRACEEXIT();
  return ret;
}

static bool FlashServiceDecode_ST_TMSC(TYPE_Service_TMSC *Data, tFlashService *Service)
{
  bool ret;

  TRACEENTER();

  //The TV and radio service structures are identical
  ret = FlashServiceDecode_ST_TMSS(Data, Service);

  TRACEEXIT();
  return ret;
}

bool FlashServiceDecode(void *Data, tFlashService *Service)
{
  TRACEENTER();

  bool ret;

  //Service is NULL
  if(!Data || !Service)
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

    case ST_TMSS: ret = FlashServiceDecode_ST_TMSS(Data, Service); break;
    case ST_TMST: ret = FlashServiceDecode_ST_TMST(Data, Service); break;
    case ST_TMSC: ret = FlashServiceDecode_ST_TMSC(Data, Service); break;

    case ST_NRTYPES: break;
  }

  TRACEEXIT();
  return ret;
}


static bool FlashServiceEncode_ST_TMSS(TYPE_Service_TMSS *Data, tFlashService *Service)
{
  bool                  isRadio;
  int                   ServiceIndex;

  char *(*Appl_AddSvcName)(char const*);
  void  (*Appl_DeleteTvSvcName)(unsigned short, bool);
  void  (*Appl_DeleteRadioSvcName)(unsigned short, bool);
  word  (*Appl_SetProviderName)(char const*);

  TRACEENTER();

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
  Data->AudioTypeFlag   = Service->AudioTypeFlag;
  Data->AudioAutoSelect = Service->AudioAutoSelect;
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

  TRACEEXIT();
  return TRUE;
}

static bool FlashServiceEncode_ST_TMST(TYPE_Service_TMST *Data, tFlashService *Service)
{
  bool ret;

  TRACEENTER();

  //The TV and radio service structures are identical
  ret = FlashServiceEncode_ST_TMSS(Data, Service);

  TRACEEXIT();
  return ret;
}

static bool FlashServiceEncode_ST_TMSC(TYPE_Service_TMSC *Data, tFlashService *Service)
{
  bool ret;

  TRACEENTER();

  //The TV and radio service structures are identical
  ret = FlashServiceEncode_ST_TMSS(Data, Service);

  TRACEEXIT();
  return ret;
}

bool FlashServiceEncode(void *Data, tFlashService *Service)
{
  bool ret;

  TRACEENTER();

  //Service is NULL
  if(!Data || !Service)
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

    case ST_TMSS: ret = FlashServiceEncode_ST_TMSS(Data, Service); break;
    case ST_TMST: ret = FlashServiceEncode_ST_TMST(Data, Service); break;
    case ST_TMSC: ret = FlashServiceEncode_ST_TMSC(Data, Service); break;

    case ST_NRTYPES: break;
  }

  TRACEEXIT();
  return ret;
}


static bool FlashServiceDelete_ST_TMSS(TYPE_Service_TMSS *Data)
{
  TYPE_Service_TMSS    *NextData;

  TRACEENTER();

  NextData = Data + 1;

  while(NextData->TunerNum != 0)
  {
    memcpy(Data, NextData, sizeof(TYPE_Service_TMSS));
    Data++;
    NextData++;
  }
  memset(Data, 0, sizeof(TYPE_Service_TMSS));

  TRACEEXIT();
  return TRUE;
}

static bool FlashServiceDelete_ST_TMST(TYPE_Service_TMST *Data)
{
  bool ret;

  TRACEENTER();

  //The TV and radio service structures are identical
  ret = FlashServiceDelete_ST_TMSS(Data);

  TRACEEXIT();
  return ret;
}

static bool FlashServiceDelete_ST_TMSC(TYPE_Service_TMSC *Data)
{
  bool ret;

  TRACEENTER();

  //The TV and radio service structures are identical
  ret = FlashServiceDelete_ST_TMSS(Data);

  TRACEEXIT();
  return ret;
}

bool FlashServiceDelete(void *Data)
{
  bool ret;

  TRACEENTER();

  //Service is NULL
  if(!Data)
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

    case ST_TMSS: ret = FlashServiceDelete_ST_TMSS(Data); break;
    case ST_TMST: ret = FlashServiceDelete_ST_TMST(Data); break;
    case ST_TMSC: ret = FlashServiceDelete_ST_TMSC(Data); break;

    case ST_NRTYPES: break;
  }

  TRACEEXIT();
  return ret;
}

bool FlashServiceDelServiceName(int SvcType, int SvcNum)
{
  void (*Appl_DeleteTvSvcName)(unsigned short, bool);
  void (*Appl_DeleteRadioSvcName)(unsigned short, bool);

  TRACEENTER();

  if(SvcType == SVC_TYPE_Tv)
  {
    Appl_DeleteTvSvcName = (void*)FIS_fwAppl_DeleteTvSvcName();
    if(!Appl_DeleteTvSvcName)
    {
      TRACEEXIT();

      return FALSE;
    }
    Appl_DeleteTvSvcName(SvcNum, FALSE);
  }
  else
  {
    Appl_DeleteRadioSvcName = (void*)FIS_fwAppl_DeleteRadioSvcName();
    if(!Appl_DeleteRadioSvcName)
    {
      TRACEEXIT();

      return FALSE;
    }
    Appl_DeleteRadioSvcName(SvcNum, FALSE);
  }

  TRACEEXIT();
  return TRUE;
}
