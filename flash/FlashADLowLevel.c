#include                <string.h>
#include                "FBLib_flash.h"

bool FlashADDecode(void *Data, tAutoDescrambleTimer *ADTimer)
{
  TRACEENTER;

  bool ret;

  //ADTimer is NULL
  if(!Data || !ADTimer)
  {
    TRACEEXIT;
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

    case ST_TMSS: ret = FlashADDecode_ST_TMSS(Data, ADTimer); break;
    case ST_TMST: ret = FlashADDecode_ST_TMST(Data, ADTimer); break;
    case ST_TMSC: ret = FlashADDecode_ST_TMSC(Data, ADTimer); break;

    case ST_NRTYPES: break;
  }

  TRACEEXIT;
  return ret;
}

bool FlashADDecode_ST_TMSS(TYPE_AutoDescrambleTimer *Data, tAutoDescrambleTimer *ADTimer)
{
  int                        i;

  TRACEENTER;

  memset(ADTimer, 0, sizeof(tAutoDescrambleTimer));
  ADTimer->StartTime        = Data->StartTime;
  ADTimer->EndTime          = Data->EndTime;
  ADTimer->Duration         = Data->Duration;
  ADTimer->ReservationType  = Data->ReservationType;
  ADTimer->DelOrig          = Data->DelOrig;
  ADTimer->NrOfFiles        = Data->NrOfFiles;
  ADTimer->AutomaticMode    = Data->AutomaticMode;
  ADTimer->unknown1         = Data->unknown1;
  ADTimer->unknown2         = Data->unknown2;
  ADTimer->unknown3         = Data->unknown3;

  for(i = 0; i < 50; i++)
    strncpy(ADTimer->FileName[i], Data->FileName[i], MAX_FILE_NAME_SIZE);

  TRACEEXIT;
  return TRUE;
}

bool FlashADDecode_ST_TMSC(TYPE_AutoDescrambleTimer *Data, tAutoDescrambleTimer *ADTimer)
{
  bool ret;

  TRACEENTER;

  ret = FlashADDecode_ST_TMSS(Data, ADTimer);

  TRACEEXIT;
  return ret;
}

bool FlashADDecode_ST_TMST(TYPE_AutoDescrambleTimer *Data, tAutoDescrambleTimer *ADTimer)
{
  bool ret;

  TRACEENTER;

  ret = FlashADDecode_ST_TMSS(Data, ADTimer);

  TRACEEXIT;
  return ret;
}

bool FlashADEncode(void *Data, tAutoDescrambleTimer *ADTimer)
{
  bool ret;

  TRACEENTER;

  //ADTimer is NULL
  if(!Data || !ADTimer)
  {
    TRACEEXIT;
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

    case ST_TMSS: ret = FlashADEncode_ST_TMSS(Data, ADTimer); break;
    case ST_TMST: ret = FlashADEncode_ST_TMST(Data, ADTimer); break;
    case ST_TMSC: ret = FlashADEncode_ST_TMSC(Data, ADTimer); break;

    case ST_NRTYPES: break;
  }

  TRACEEXIT;
  return ret;
}

bool FlashADEncode_ST_TMSS(TYPE_AutoDescrambleTimer *Data, tAutoDescrambleTimer *ADTimer)
{
  int                   i;

  TRACEENTER;

  memset(Data, 0, sizeof(TYPE_AutoDescrambleTimer));
  Data->StartTime        = ADTimer->StartTime;
  Data->EndTime          = ADTimer->EndTime;
  Data->Duration         = ADTimer->Duration;
  Data->ReservationType  = ADTimer->ReservationType;
  Data->DelOrig          = ADTimer->DelOrig;
  Data->NrOfFiles        = ADTimer->NrOfFiles;
  Data->AutomaticMode    = ADTimer->AutomaticMode;
  Data->unknown1         = ADTimer->unknown1;
  Data->unknown2         = ADTimer->unknown2;
  Data->unknown3         = ADTimer->unknown3;

  for(i = 0; i < 50; i++)
    strncpy(Data->FileName[i], ADTimer->FileName[i], MAX_FILE_NAME_SIZE);

  TRACEEXIT;
  return TRUE;
}

bool FlashADEncode_ST_TMSC(TYPE_AutoDescrambleTimer *Data, tAutoDescrambleTimer *ADTimer)
{
  bool ret;

  TRACEENTER;

  ret = FlashADEncode_ST_TMSS(Data, ADTimer);

  TRACEEXIT;
  return ret;
}

bool FlashADEncode_ST_TMST(TYPE_AutoDescrambleTimer *Data, tAutoDescrambleTimer *ADTimer)
{
  bool ret;

  TRACEENTER;

  ret = FlashADEncode_ST_TMSS(Data, ADTimer);

  TRACEEXIT;
  return ret;
}
