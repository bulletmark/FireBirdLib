#include <string.h>
#include "FBLib_rec.h"

word getWord(void *buffer, bool NeedsByteSwapping)
{
  TRACEENTER;

  word                  w;
  byte                 *p;

  p = (byte*)buffer;
  if(NeedsByteSwapping)
    w = (p[1] | (p[0] << 8));
  else
    w = (p[0] | (p[1] << 8));

  TRACEEXIT;
  return w;
}

dword getDword(void *buffer, bool NeedsByteSwapping)
{
  TRACEENTER;

  dword                 d;
  byte                 *p;

  p = (byte*)buffer;
  if(NeedsByteSwapping)
    d = (p[3] | (p[2] << 8) | (p[1] << 16) | (p[0] << 24));
  else
    d = (p[0] | (p[1] << 8) | (p[2] << 16) | (p[3] << 24));

  TRACEEXIT;
  return d;
}

bool                    WrongEndian = FALSE;

void DecodeExtInfo(byte *Buffer, dword p, tRECHeaderInfo *RECHeaderInfo)
{
  TRACEENTER;

  //The extended info structure is identical on all Toppies
  RECHeaderInfo->ExtEventServiceID   = getWord(&Buffer[p + 0x0000], WrongEndian);

  RECHeaderInfo->ExtEventTextLength  = getWord(&Buffer[p + 0x0002], WrongEndian);
  if(RECHeaderInfo->ExtEventTextLength > 1023)
  {
    RECHeaderInfo->ExtEventTextLength = 1023;
    Buffer[p + 0x0407] = 0;
  }

  RECHeaderInfo->ExtEventEventID     = getDword(&Buffer[p + 0x0004], WrongEndian);
  RECHeaderInfo->ExtEventNrItemizedPairs = Buffer[p + 0x0408];
  memcpy(RECHeaderInfo->ExtEventUnknown1, &Buffer[p + 0x0409], 3);

  if(RECHeaderInfo->ExtEventNrItemizedPairs == 0)
  {
    memcpy(RECHeaderInfo->ExtEventText, &Buffer[p + 0x0008], RECHeaderInfo->ExtEventTextLength);
  }
  else
  {
    char               *pStart, *pEnd, *pDescr, *pInfo;

    //Find the border between the itemized data and the description
    pStart = &Buffer[p + 0x0008];
    pEnd = pStart + RECHeaderInfo->ExtEventTextLength;
    pDescr = pEnd - 1;
    while((*pDescr != 0) && (pDescr > pStart))
    {
      pDescr--;
    }
    if(pDescr != pStart) pDescr++;

    pInfo = RECHeaderInfo->ExtEventText;
    memcpy(pInfo, pDescr, pEnd - pDescr + 1);
    pInfo += (pEnd - pDescr + 1);
    memcpy(pInfo, pStart, pDescr - pStart + 1);
  }
  StrReplace(RECHeaderInfo->ExtEventText, "\\n", "\x8a");

  TRACEEXIT;
}

void HDD_DecodeRECHeader_ST_S(byte *Buffer, tRECHeaderInfo *RECHeaderInfo)
{
  TRACEENTER;

  dword                 p;
  word                  TPFlags1;
  byte                  EventTextLength;

  //Header
  p = 0;
  memcpy(RECHeaderInfo->HeaderUnknown2, &Buffer[p + 0x0006], 2);
  RECHeaderInfo->HeaderDuration  = getWord(&Buffer[p + 0x0008], WrongEndian);
  RECHeaderInfo->HeaderSvcNumber = getWord(&Buffer[p + 0x000a], WrongEndian);
  RECHeaderInfo->HeaderSvcType   = getWord(&Buffer[p + 0x000c], WrongEndian);

  //Service Info
  p = 0x000e;
  RECHeaderInfo->SISatIndex  =  Buffer[p + 0x0000];
  RECHeaderInfo->SIServiceType = Buffer[p + 0x0001];
  RECHeaderInfo->SITPIdx     =  getWord(&Buffer[p + 0x0002], WrongEndian) >> 6;
  RECHeaderInfo->SITunerNum  = (getWord(&Buffer[p + 0x0002], WrongEndian) >> 4) & 3;
  RECHeaderInfo->SISkipFlag  = (getWord(&Buffer[p + 0x0002], WrongEndian) >> 3) & 1;
  RECHeaderInfo->SILockFlag  = (getWord(&Buffer[p + 0x0002], WrongEndian) >> 2) & 1;
  RECHeaderInfo->SICASFlag   = (getWord(&Buffer[p + 0x0002], WrongEndian) >> 1) & 1;
  RECHeaderInfo->SIDelFlag   = (getWord(&Buffer[p + 0x0002], WrongEndian)     ) & 1;

  RECHeaderInfo->SIServiceID = getWord(&Buffer[p + 0x0004], WrongEndian);
  RECHeaderInfo->SIPMTPID    = getWord(&Buffer[p + 0x0006], WrongEndian);
  RECHeaderInfo->SIPCRPID    = getWord(&Buffer[p + 0x0008], WrongEndian);
  RECHeaderInfo->SIVideoPID  = getWord(&Buffer[p + 0x000a], WrongEndian);
  RECHeaderInfo->SIAudioPID  = getWord(&Buffer[p + 0x000c], WrongEndian);
  strncpy(RECHeaderInfo->SISvcName, &Buffer[p + 0x000e], 24);

  //Transponder Info
  p = 0x0034;
  RECHeaderInfo->TPSatIndex           = Buffer[p + 0x0000];

  TPFlags1                            = Buffer[p + 0x0001];
  RECHeaderInfo->TPPolarization       =  TPFlags1 >> 7;
  RECHeaderInfo->TPMode               = (TPFlags1 >> 4) & 7;

  memcpy(RECHeaderInfo->TPUnknown3, &Buffer[p + 0x0002], 2);
  RECHeaderInfo->TPFrequency          = getDword(&Buffer[p + 0x0004], WrongEndian);
  RECHeaderInfo->TPSymbolRate         = getWord(&Buffer[p + 0x0008], WrongEndian);
  RECHeaderInfo->TPTSID               = getWord(&Buffer[p + 0x000a], WrongEndian);
  memcpy(RECHeaderInfo->TPUnknown5, &Buffer[p + 0x000c], 2);
  RECHeaderInfo->TPOriginalNetworkID  = getWord(&Buffer[p + 0x000e], WrongEndian);

  //Event Info
  p = 0x0044;
  memcpy(RECHeaderInfo->EventUnknown1, &Buffer[p], 2);
  RECHeaderInfo->EventDuration       = 60 * Buffer[p + 0x0002] + Buffer[p + 0x0003];
  RECHeaderInfo->EventEventID        =  getDword(&Buffer[p + 0x0004], WrongEndian);
  RECHeaderInfo->EventStartTime      =  getDword(&Buffer[p + 0x0008], WrongEndian);
  RECHeaderInfo->EventEndTime        =  getDword(&Buffer[p + 0x000c], WrongEndian);
  RECHeaderInfo->EventRunningStatus  = Buffer[p + 0x0010];
  EventTextLength                    = Buffer[p + 0x0011];
  RECHeaderInfo->EventParentalRate   = Buffer[p + 0x0012];
  strncpy(RECHeaderInfo->EventEventName, &Buffer[p + 0x0013], EventTextLength);
  strncpy(RECHeaderInfo->EventEventDescription, &Buffer[p + 0x0013 + EventTextLength], 257 - EventTextLength);
  RECHeaderInfo->EventServiceID      =  getWord(&Buffer[p + 0x0114], WrongEndian);
  memcpy(RECHeaderInfo->EventUnknown2, &Buffer[p + 0x0116], 14);

  //Extended Event Info
  p = 0x0168;
  DecodeExtInfo(Buffer, p, RECHeaderInfo);

  //Crypt Info
  p = 0x0574;
  RECHeaderInfo->CryptFlag = Buffer[p + 0x0000];
  memcpy(RECHeaderInfo->CryptUnknown2, &Buffer[p + 0x0001], 3);

  //Bookmarks
  p = 0x0578;
  memcpy(RECHeaderInfo->Bookmark, &Buffer[p + 0x0000], 64 * sizeof(dword));
  RECHeaderInfo->Resume = getDword(&Buffer[p + 0x0100], WrongEndian);

  TRACEEXIT;
}

void HDD_DecodeRECHeader_ST_T(byte *Buffer, tRECHeaderInfo *RECHeaderInfo)
{
  TRACEENTER;

  dword                 p;
  byte                  EventTextLength;

  //Header
  p = 0;
  memcpy(RECHeaderInfo->HeaderUnknown2, &Buffer[p + 0x0006], 2);
  RECHeaderInfo->HeaderDuration  = getWord(&Buffer[p + 0x0008], WrongEndian);
  RECHeaderInfo->HeaderSvcNumber = getWord(&Buffer[p + 0x000a], WrongEndian);
  RECHeaderInfo->HeaderSvcType   = getWord(&Buffer[p + 0x000c], WrongEndian);

  //Service Info
  p = 0x000e;
  RECHeaderInfo->SISatIndex  =  Buffer[p + 0x0000];
  RECHeaderInfo->SIServiceType = Buffer[p + 0x0001];
  RECHeaderInfo->SITPIdx     =  getWord(&Buffer[p + 0x0002], WrongEndian) >> 6;
  RECHeaderInfo->SITunerNum  = (getWord(&Buffer[p + 0x0002], WrongEndian) >> 4) & 3;
  RECHeaderInfo->SISkipFlag  = (getWord(&Buffer[p + 0x0002], WrongEndian) >> 3) & 1;
  RECHeaderInfo->SILockFlag  = (getWord(&Buffer[p + 0x0002], WrongEndian) >> 2) & 1;
  RECHeaderInfo->SICASFlag   = (getWord(&Buffer[p + 0x0002], WrongEndian) >> 1) & 1;
  RECHeaderInfo->SIDelFlag   = (getWord(&Buffer[p + 0x0002], WrongEndian)     ) & 1;

  RECHeaderInfo->SIServiceID = getWord(&Buffer[p + 0x0004], WrongEndian);
  RECHeaderInfo->SIPMTPID    = getWord(&Buffer[p + 0x0006], WrongEndian);
  RECHeaderInfo->SIPCRPID    = getWord(&Buffer[p + 0x0008], WrongEndian);
  RECHeaderInfo->SIVideoPID  = getWord(&Buffer[p + 0x000a], WrongEndian);
  RECHeaderInfo->SIAudioPID  = getWord(&Buffer[p + 0x000c], WrongEndian);
  strncpy(RECHeaderInfo->SISvcName, &Buffer[p + 0x000e], 24);

  //Transponder Info
  p = 0x0034;
  RECHeaderInfo->TPChannelNumber      = getWord(&Buffer[p + 0x0000], WrongEndian);
  RECHeaderInfo->TPBandwidth          = Buffer[p + 0x0002];
  RECHeaderInfo->TPUnknown2           = Buffer[p + 0x0003];
  RECHeaderInfo->TPFrequency          = getDword(&Buffer[p + 0x0004], WrongEndian);
  RECHeaderInfo->TPTSID               = getWord(&Buffer[p + 0x0008], WrongEndian);
  RECHeaderInfo->TPLPHPStream         = Buffer[p + 0x000a];
  RECHeaderInfo->TPUnknown4           = Buffer[p + 0x000b];
  RECHeaderInfo->TPOriginalNetworkID  = getWord(&Buffer[p + 0x000c], WrongEndian);
  RECHeaderInfo->TPNetworkID          = getWord(&Buffer[p + 0x000e], WrongEndian);

  //Event Info
  p = 0x0044;
  memcpy(RECHeaderInfo->EventUnknown1, &Buffer[p], 2);
  RECHeaderInfo->EventDuration       = 60 * Buffer[p + 0x0002] + Buffer[p + 0x0003];
  RECHeaderInfo->EventEventID        =  getDword(&Buffer[p + 0x0004], WrongEndian);
  RECHeaderInfo->EventStartTime      =  getDword(&Buffer[p + 0x0008], WrongEndian);
  RECHeaderInfo->EventEndTime        =  getDword(&Buffer[p + 0x000c], WrongEndian);
  RECHeaderInfo->EventRunningStatus  = Buffer[p + 0x0010];
  EventTextLength                    = Buffer[p + 0x0011];
  RECHeaderInfo->EventParentalRate   = Buffer[p + 0x0012];
  strncpy(RECHeaderInfo->EventEventName, &Buffer[p + 0x0013], EventTextLength);
  strncpy(RECHeaderInfo->EventEventDescription, &Buffer[p + 0x0013 + EventTextLength], 257 - EventTextLength);
  RECHeaderInfo->EventServiceID      =  getWord(&Buffer[p + 0x0114], WrongEndian);
  memcpy(RECHeaderInfo->EventUnknown2, &Buffer[p + 0x0116], 14);

  //Extended Event Info
  p = 0x0168;
  DecodeExtInfo(Buffer, p, RECHeaderInfo);

  //Crypt Info
  p = 0x0574;
  RECHeaderInfo->CryptFlag = Buffer[p + 0x0000];
  memcpy(RECHeaderInfo->CryptUnknown2, &Buffer[p + 0x0001], 3);

  //Bookmarks
  p = 0x0578;
  memcpy(RECHeaderInfo->Bookmark, &Buffer[p + 0x0000], 64 * sizeof(dword));
  RECHeaderInfo->Resume = getDword(&Buffer[p + 0x0100], WrongEndian);

  TRACEEXIT;
}

void HDD_DecodeRECHeader_ST_C(byte *Buffer, tRECHeaderInfo *RECHeaderInfo)
{
  TRACEENTER;

  dword                 p;
  byte                  EventTextLength;

  //Header
  p = 0;
  memcpy(RECHeaderInfo->HeaderUnknown2, &Buffer[p + 6], 2);
  RECHeaderInfo->HeaderDuration  = getWord(&Buffer[p + 0x0008], WrongEndian);
  RECHeaderInfo->HeaderSvcNumber = getWord(&Buffer[p + 0x000a], WrongEndian);
  RECHeaderInfo->HeaderSvcType   = getWord(&Buffer[p + 0x000c], WrongEndian);

  //Service Info
  p = 0x000e;
  RECHeaderInfo->SISatIndex  =  Buffer[p + 0x0000];
  RECHeaderInfo->SIServiceType = Buffer[p + 0x0001];
  RECHeaderInfo->SITPIdx     =  getWord(&Buffer[p + 0x0002], WrongEndian) >> 6;
  RECHeaderInfo->SITunerNum  = (getWord(&Buffer[p + 0x0002], WrongEndian) >> 4) & 3;
  RECHeaderInfo->SIDelFlag   = (getWord(&Buffer[p + 0x0002], WrongEndian) >> 3) & 1;
  RECHeaderInfo->SICASFlag   = (getWord(&Buffer[p + 0x0002], WrongEndian) >> 2) & 1;
  RECHeaderInfo->SILockFlag  = (getWord(&Buffer[p + 0x0002], WrongEndian) >> 1) & 1;
  RECHeaderInfo->SISkipFlag  = (getWord(&Buffer[p + 0x0002], WrongEndian)     ) & 1;

  RECHeaderInfo->SIServiceID = getWord(&Buffer[p + 0x0004], WrongEndian);
  RECHeaderInfo->SIPMTPID    = getWord(&Buffer[p + 0x0006], WrongEndian);
  RECHeaderInfo->SIPCRPID    = getWord(&Buffer[p + 0x0008], WrongEndian);
  RECHeaderInfo->SIVideoPID  = getWord(&Buffer[p + 0x000a], WrongEndian);
  RECHeaderInfo->SIAudioPID  = getWord(&Buffer[p + 0x000c], WrongEndian);
  strncpy(RECHeaderInfo->SISvcName, &Buffer[p + 0x000e], 24);

  //Transponder Info
  p = 0x0034;
  RECHeaderInfo->TPFrequency          = getDword(&Buffer[p + 0x0000], WrongEndian);
  RECHeaderInfo->TPSymbolRate         = getWord(&Buffer[p + 0x0004], WrongEndian);
  RECHeaderInfo->TPTSID               = getWord(&Buffer[p + 0x0006], WrongEndian);
  RECHeaderInfo->TPOriginalNetworkID  = getWord(&Buffer[p + 0x0008], WrongEndian);
  RECHeaderInfo->TPModulation         = Buffer[p + 0x000a];
  RECHeaderInfo->TPUnknown6           = Buffer[p + 0x000b];

  //Event Info
  p = 0x0040;
  memcpy(RECHeaderInfo->EventUnknown1, &Buffer[p], 2);
  RECHeaderInfo->EventDuration       = 60 * Buffer[p + 0x0002] + Buffer[p + 0x0003];
  RECHeaderInfo->EventEventID        = getDword(&Buffer[p + 0x0004], WrongEndian);
  RECHeaderInfo->EventStartTime      = getDword(&Buffer[p + 0x0008], WrongEndian);
  RECHeaderInfo->EventEndTime        = getDword(&Buffer[p + 0x000c], WrongEndian);
  RECHeaderInfo->EventRunningStatus  = Buffer[p + 0x0010];
  EventTextLength                    = Buffer[p + 0x0011];
  RECHeaderInfo->EventParentalRate   = Buffer[p + 0x0012];
  strncpy(RECHeaderInfo->EventEventName, &Buffer[p + 0x0013], EventTextLength);
  strncpy(RECHeaderInfo->EventEventDescription, &Buffer[p + 0x0013 + EventTextLength], 257 - EventTextLength);
  RECHeaderInfo->EventServiceID      =  getWord(&Buffer[p + 0x0114], WrongEndian);
  memcpy(RECHeaderInfo->EventUnknown2, &Buffer[p + 0x0116], 14);

  //Extended Event Info
  p = 0x0164;
  DecodeExtInfo(Buffer, p, RECHeaderInfo);

  //Crypt Info
  p = 0x0570;
  RECHeaderInfo->CryptFlag = Buffer[p + 0x0000];
  memcpy(RECHeaderInfo->CryptUnknown2, &Buffer[p + 0x0001], 3);

  //Bookmarks
  p = 0x0574;
  memcpy(RECHeaderInfo->Bookmark, &Buffer[p + 0x0000], 64 * sizeof(dword));
  RECHeaderInfo->Resume = getDword(&Buffer[p + 0x0100], WrongEndian);

  TRACEEXIT;
}

void HDD_DecodeRECHeader_ST_T5700(byte *Buffer, tRECHeaderInfo *RECHeaderInfo)
{
  TRACEENTER;

  dword                 p;
  byte                  EventTextLength;

  //Header
  p = 0;
  memcpy(RECHeaderInfo->HeaderUnknown2, &Buffer[p + 6], 2);
  RECHeaderInfo->HeaderDuration  = getWord(&Buffer[p + 0x0008], WrongEndian);
  RECHeaderInfo->HeaderSvcNumber = getWord(&Buffer[p + 0x000a], WrongEndian);
  RECHeaderInfo->HeaderSvcType   = getWord(&Buffer[p + 0x000c], WrongEndian);

  //Service Info
  p = 0x000e;
  RECHeaderInfo->SISatIndex  = Buffer[p + 0x0000];
  RECHeaderInfo->SIServiceType = Buffer[p + 0x0001];
  RECHeaderInfo->SITPIdx     =  getWord(&Buffer[p + 0x0002], WrongEndian) >> 6;
  RECHeaderInfo->SITunerNum  = (getWord(&Buffer[p + 0x0002], WrongEndian) >> 4) & 3;
  RECHeaderInfo->SIDelFlag   = (getWord(&Buffer[p + 0x0002], WrongEndian) >> 3) & 1;
  RECHeaderInfo->SICASFlag   = (getWord(&Buffer[p + 0x0002], WrongEndian) >> 2) & 1;
  RECHeaderInfo->SILockFlag  = (getWord(&Buffer[p + 0x0002], WrongEndian) >> 1) & 1;
  RECHeaderInfo->SISkipFlag  = (getWord(&Buffer[p + 0x0002], WrongEndian)     ) & 1;

  RECHeaderInfo->SIServiceID = getWord(&Buffer[p + 0x0004], WrongEndian);
  RECHeaderInfo->SIPMTPID    = getWord(&Buffer[p + 0x0006], WrongEndian);
  RECHeaderInfo->SIPCRPID    = getWord(&Buffer[p + 0x0008], WrongEndian);
  RECHeaderInfo->SIVideoPID  = getWord(&Buffer[p + 0x000a], WrongEndian);
  RECHeaderInfo->SIAudioPID  = getWord(&Buffer[p + 0x000c], WrongEndian);
  strncpy(RECHeaderInfo->SISvcName, &Buffer[p + 0x000e], 24);

  //Transponder Info
  p = 0x0034;
  RECHeaderInfo->TPChannelNumber      = getWord(&Buffer[p + 0x0000], WrongEndian);
  RECHeaderInfo->TPBandwidth          = Buffer[p + 0x0002];
  RECHeaderInfo->TPUnknown2           = Buffer[p + 0x0003];
  RECHeaderInfo->TPFrequency          = getDword(&Buffer[p + 0x0004], WrongEndian);
  RECHeaderInfo->TPTSID               = getWord(&Buffer[p + 0x0008], WrongEndian);
  RECHeaderInfo->TPLPHPStream         = Buffer[p + 0x000a];
  RECHeaderInfo->TPUnknown4           = Buffer[p + 0x000b];
  RECHeaderInfo->TPOriginalNetworkID  = getWord(&Buffer[p + 0x000c], WrongEndian);
  RECHeaderInfo->TPNetworkID          = getWord(&Buffer[p + 0x000e], WrongEndian);
  memcpy(RECHeaderInfo->TPUnknown7, &Buffer[p + 0x0010], 8);

  //Event Info
  p = 0x004c;
  memcpy(RECHeaderInfo->EventUnknown1, &Buffer[p], 2);
  RECHeaderInfo->EventDuration       = 60 * Buffer[p + 0x0002] + Buffer[p +  3];
  RECHeaderInfo->EventEventID        =  getDword(&Buffer[p + 0x0004], WrongEndian);
  RECHeaderInfo->EventStartTime      =  getDword(&Buffer[p + 0x0008], WrongEndian);
  RECHeaderInfo->EventEndTime        =  getDword(&Buffer[p + 0x000c], WrongEndian);
  RECHeaderInfo->EventRunningStatus  = Buffer[p + 0x0010];
  EventTextLength                    = Buffer[p + 0x0011];
  RECHeaderInfo->EventParentalRate   = Buffer[p + 0x0012];
  strncpy(RECHeaderInfo->EventEventName, &Buffer[p + 0x0013], EventTextLength);
  strncpy(RECHeaderInfo->EventEventDescription, &Buffer[p + 0x0013 + EventTextLength], 257 - EventTextLength);
  RECHeaderInfo->EventServiceID      =  getWord(&Buffer[p + 0x0114], WrongEndian);
  memcpy(RECHeaderInfo->EventUnknown2, &Buffer[p + 0x0116], 14);

  //Extended Event Info
  p = 0x0170;
  DecodeExtInfo(Buffer, p, RECHeaderInfo);

  //Crypt Info
  p = 0x057c;
  RECHeaderInfo->CryptFlag = Buffer[p + 0x0000];
  memcpy(RECHeaderInfo->CryptUnknown2, &Buffer[p + 0x0001], 3);

  //Bookmarks
  p = 0x0580;
  memcpy(RECHeaderInfo->Bookmark, &Buffer[p + 0x0000], 64 * sizeof(dword));
  RECHeaderInfo->Resume = getDword(&Buffer[p + 0x0100], WrongEndian);

  TRACEEXIT;
}

void HDD_DecodeRECHeader_ST_T5800(byte *Buffer, tRECHeaderInfo *RECHeaderInfo)
{
  TRACEENTER;

  dword                 p;
  byte                  EventTextLength;

  //Header
  p = 0;
  memcpy(RECHeaderInfo->HeaderUnknown2, &Buffer[p + 6], 2);
  RECHeaderInfo->HeaderDuration  = getWord(&Buffer[p + 0x0008], WrongEndian);
  RECHeaderInfo->HeaderSvcNumber = getWord(&Buffer[p + 0x000a], WrongEndian);
  RECHeaderInfo->HeaderSvcType   = getWord(&Buffer[p + 0x000c], WrongEndian);

  //Service Info
  p = 0x000e;
  RECHeaderInfo->SISatIndex  = Buffer[p + 0x0000];
  RECHeaderInfo->SIServiceType = Buffer[p + 0x0001];
  RECHeaderInfo->SITPIdx     =  getWord(&Buffer[p + 0x0002], WrongEndian) >> 6;
  RECHeaderInfo->SITunerNum  = (getWord(&Buffer[p + 0x0002], WrongEndian) >> 4) & 3;
  RECHeaderInfo->SIDelFlag   = (getWord(&Buffer[p + 0x0002], WrongEndian) >> 3) & 1;
  RECHeaderInfo->SICASFlag   = (getWord(&Buffer[p + 0x0002], WrongEndian) >> 2) & 1;
  RECHeaderInfo->SILockFlag  = (getWord(&Buffer[p + 0x0002], WrongEndian) >> 1) & 1;
  RECHeaderInfo->SISkipFlag  = (getWord(&Buffer[p + 0x0002], WrongEndian)     ) & 1;

  RECHeaderInfo->SIServiceID = getWord(&Buffer[p + 0x0004], WrongEndian);
  RECHeaderInfo->SIPMTPID    = getWord(&Buffer[p + 0x0006], WrongEndian);
  RECHeaderInfo->SIPCRPID    = getWord(&Buffer[p + 0x0008], WrongEndian);
  RECHeaderInfo->SIVideoPID  = getWord(&Buffer[p + 0x000a], WrongEndian);
  RECHeaderInfo->SIAudioPID  = getWord(&Buffer[p + 0x000c], WrongEndian);
  strncpy(RECHeaderInfo->SISvcName, &Buffer[p + 0x000e], 28);

  //Transponder Info
  p = 0x0038;
  RECHeaderInfo->TPChannelNumber      = getWord(&Buffer[p + 0x0000], WrongEndian);
  RECHeaderInfo->TPBandwidth          = Buffer[p + 0x0002];
  RECHeaderInfo->TPUnknown2           = Buffer[p + 0x0003];
  RECHeaderInfo->TPFrequency          = getDword(&Buffer[p + 0x0004], WrongEndian);
  RECHeaderInfo->TPTSID               = getWord(&Buffer[p + 0x0008], WrongEndian);
  RECHeaderInfo->TPLPHPStream         = Buffer[p + 0x000a];
  RECHeaderInfo->TPUnknown4           = Buffer[p + 0x000b];
  RECHeaderInfo->TPOriginalNetworkID  = getWord(&Buffer[p + 0x000c], WrongEndian);
  RECHeaderInfo->TPNetworkID          = getWord(&Buffer[p + 0x000e], WrongEndian);

  //Event Info
  p = 0x0048;
  memcpy(RECHeaderInfo->EventUnknown1, &Buffer[p], 2);
  RECHeaderInfo->EventDuration       = 60 * Buffer[p + 0x0002] + Buffer[p +  3];
  RECHeaderInfo->EventEventID        =  getDword(&Buffer[p + 0x0004], WrongEndian);
  RECHeaderInfo->EventStartTime      =  getDword(&Buffer[p + 0x0008], WrongEndian);
  RECHeaderInfo->EventEndTime        =  getDword(&Buffer[p + 0x000c], WrongEndian);
  RECHeaderInfo->EventRunningStatus  = Buffer[p + 0x0010];
  EventTextLength                    = Buffer[p + 0x0011];
  RECHeaderInfo->EventParentalRate   = Buffer[p + 0x0012];
  strncpy(RECHeaderInfo->EventEventName, &Buffer[p + 0x0013], EventTextLength);
  strncpy(RECHeaderInfo->EventEventDescription, &Buffer[p + 0x0013 + EventTextLength], 257 - EventTextLength);
  RECHeaderInfo->EventServiceID      =  getWord(&Buffer[p + 0x0114], WrongEndian);
  memcpy(RECHeaderInfo->EventUnknown2, &Buffer[p + 0x0116], 10);

  //Extended Event Info
  p = 0x016c;
  DecodeExtInfo(Buffer, p, RECHeaderInfo);

  //Crypt Info
  p = 0x0578;
  RECHeaderInfo->CryptFlag = Buffer[p + 0x0000];
  memcpy(RECHeaderInfo->CryptUnknown2, &Buffer[p + 0x0001], 3);

  //Bookmarks
  p = 0x057c;
  memcpy(RECHeaderInfo->Bookmark, &Buffer[p + 0x0000], 64 * sizeof(dword));
  RECHeaderInfo->Resume = getDword(&Buffer[p + 0x0100], WrongEndian);

  TRACEEXIT;
}

void HDD_DecodeRECHeader_ST_TMSS(byte *Buffer, tRECHeaderInfo *RECHeaderInfo)
{
  TRACEENTER;

  dword                 p;
  word                  Flags;
  byte                  EventTextLength;

  //Header
  p = 0;
  memcpy(RECHeaderInfo->HeaderUnknown2, &Buffer[p + 6], 2);
  RECHeaderInfo->HeaderStartTime = getDword(&Buffer[p + 0x0008], WrongEndian);
  RECHeaderInfo->HeaderDuration  = getWord(&Buffer[p + 0x000c], WrongEndian);
  RECHeaderInfo->HeaderDurationSec  = getWord(&Buffer[p + 0x000e], WrongEndian);

  RECHeaderInfo->CryptFlag   = Buffer[p + 0x0010] & 0x03;
  RECHeaderInfo->HeaderFlags = Buffer[p + 0x0010] & 0xfc;

  RECHeaderInfo->HeaderCopyFlag = Buffer[p + 0x0011] & 0x80;
  RECHeaderInfo->HeaderTSFlag = Buffer[p + 0x0011] & 0x40;
  RECHeaderInfo->HeaderFlags2 = Buffer[p + 0x0011] & 0x3f;

  memcpy(RECHeaderInfo->HeaderUnknown4, &Buffer[p + 0x0012], 10);

  //Service Info
  p = 0x001c;
  RECHeaderInfo->SISatIndex    =  Buffer[p + 0x0000];
  RECHeaderInfo->SIServiceType =  Buffer[p + 0x0001];

  Flags = getWord(&Buffer[p +0x0002], WrongEndian);
  RECHeaderInfo->SITPIdx     =  Flags & 0x3ff;
  RECHeaderInfo->SITunerNum  = (Flags >> 10) & 3;
  RECHeaderInfo->SIDelFlag   = (Flags >> 12) & 1;
  RECHeaderInfo->SICASFlag   = (Flags >> 13) & 1;
  RECHeaderInfo->SILockFlag  = (Flags >> 14) & 1;
  RECHeaderInfo->SISkipFlag  =  Flags >> 15;

  RECHeaderInfo->SIServiceID = getWord(&Buffer[p + 0x0004], WrongEndian);
  RECHeaderInfo->SIPMTPID    = getWord(&Buffer[p + 0x0006], WrongEndian);
  RECHeaderInfo->SIPCRPID    = getWord(&Buffer[p + 0x0008], WrongEndian);
  RECHeaderInfo->SIVideoPID  = getWord(&Buffer[p + 0x000a], WrongEndian);
  RECHeaderInfo->SIAudioPID  = getWord(&Buffer[p + 0x000c], WrongEndian);

  strncpy(RECHeaderInfo->SISvcName, &Buffer[p + 0x000e], 24);

  RECHeaderInfo->SIVideoStreamType = Buffer[p + 0x0026];
  RECHeaderInfo->SIAudioStreamType = Buffer[p + 0x0027];

  //Event Info
  p = 0x0044;
  memcpy(RECHeaderInfo->EventUnknown1, &Buffer[p], 2);
  RECHeaderInfo->EventDuration       = 60 * Buffer[p +  3] + Buffer[p +  2];
  RECHeaderInfo->EventEventID        = getDword(&Buffer[p + 0x0004], WrongEndian);
  RECHeaderInfo->EventStartTime      = getDword(&Buffer[p + 0x0008], WrongEndian);
  RECHeaderInfo->EventEndTime        = getDword(&Buffer[p + 0x000c], WrongEndian);
  RECHeaderInfo->EventRunningStatus  = Buffer[p + 0x0010];
  EventTextLength                    = Buffer[p + 0x0011];
  RECHeaderInfo->EventParentalRate   = Buffer[p + 0x0012];
  strncpy(RECHeaderInfo->EventEventName, &Buffer[p + 0x0013], EventTextLength);
  strncpy(RECHeaderInfo->EventEventDescription, &Buffer[p + 0x0013 + EventTextLength], 273 - EventTextLength);

  //Extended Event Info
  p = 0x0168;
  DecodeExtInfo(Buffer, p, RECHeaderInfo);

  //Transponder info
  p = 0x0574;
  RECHeaderInfo->TPSatIndex           = Buffer[p];

  Flags                               = getWord(&Buffer[p +  1], WrongEndian);
  RECHeaderInfo->TPPolarization       =  Flags & 0x01;
  RECHeaderInfo->TPMode               = (Flags >>  1) & 0x07;
  RECHeaderInfo->TPSystem             = (Flags >>  4) & 0x01;
  RECHeaderInfo->TPModulation         = (Flags >>  5) & 0x03;
  RECHeaderInfo->TPFEC                = (Flags >>  7) & 0x0f;
  RECHeaderInfo->TPPilot              = (Flags >> 11) & 0x01;

  RECHeaderInfo->TPUnknown2           = Buffer[p + 3];
  RECHeaderInfo->TPFrequency          = getDword(&Buffer[p +  4], WrongEndian);
  RECHeaderInfo->TPSymbolRate         = getWord(&Buffer [p +  8], WrongEndian);
  RECHeaderInfo->TPTSID               = getWord(&Buffer [p + 10], WrongEndian);
  RECHeaderInfo->TPNetworkID          = getWord(&Buffer [p + 12], WrongEndian);
  RECHeaderInfo->TPOriginalNetworkID  = getWord(&Buffer [p + 14], WrongEndian);

  //Crypt Info: see header flags

  //Bookmarks
  p = 0x0584;
  RECHeaderInfo->NrBookmarks = getDword(&Buffer[p + 0x0000], WrongEndian);
  memcpy(RECHeaderInfo->Bookmark, &Buffer[p + 0x0004], 177 * sizeof(dword));
  RECHeaderInfo->Resume = getDword(&Buffer[p + 0x02c8], WrongEndian);

  TRACEEXIT;
}

void HDD_DecodeRECHeader_ST_TMST(byte *Buffer, tRECHeaderInfo *RECHeaderInfo)
{
  TRACEENTER;

  dword                 p;
  word                  Flags;
  byte                  EventTextLength;

  //Header
  p = 0;
  memcpy(RECHeaderInfo->HeaderUnknown2, &Buffer[p + 6], 2);
  RECHeaderInfo->HeaderStartTime = getDword(&Buffer[p + 0x0008], WrongEndian);
  RECHeaderInfo->HeaderDuration  = getWord(&Buffer[p + 0x000c], WrongEndian);
  RECHeaderInfo->HeaderDurationSec  = getWord(&Buffer[p + 0x000e], WrongEndian);

  RECHeaderInfo->CryptFlag = Buffer[p + 0x0010] & 0x03;
  RECHeaderInfo->HeaderFlags = Buffer[p + 0x0010] & 0xfc;

  RECHeaderInfo->HeaderCopyFlag = Buffer[p + 0x0011] & 0x80;
  RECHeaderInfo->HeaderTSFlag = Buffer[p + 0x0011] & 0x40;
  RECHeaderInfo->HeaderFlags2 = Buffer[p + 0x0011] & 0x3f;


  memcpy(RECHeaderInfo->HeaderUnknown4, &Buffer[p + 0x0012], 10);

  //Service Info
  p = 0x001c;
  RECHeaderInfo->SISatIndex    =  Buffer[p + 0x0000];
  RECHeaderInfo->SIServiceType =  Buffer[p + 0x0001];

  Flags = getWord(&Buffer[p +0x0002], WrongEndian);
  RECHeaderInfo->SITPIdx     =  Flags & 0x3ff;
  RECHeaderInfo->SITunerNum  = (Flags >> 10) & 3;
  RECHeaderInfo->SIDelFlag   = (Flags >> 12) & 1;
  RECHeaderInfo->SICASFlag   = (Flags >> 13) & 1;
  RECHeaderInfo->SILockFlag  = (Flags >> 14) & 1;
  RECHeaderInfo->SISkipFlag  =  Flags >> 15;

  RECHeaderInfo->SIServiceID = getWord(&Buffer[p + 0x0004], WrongEndian);
  RECHeaderInfo->SIPMTPID    = getWord(&Buffer[p + 0x0006], WrongEndian);
  RECHeaderInfo->SIPCRPID    = getWord(&Buffer[p + 0x0008], WrongEndian);
  RECHeaderInfo->SIVideoPID  = getWord(&Buffer[p + 0x000a], WrongEndian);
  RECHeaderInfo->SIAudioPID  = getWord(&Buffer[p + 0x000c], WrongEndian);

  strncpy(RECHeaderInfo->SISvcName, &Buffer[p + 0x000e], 24);

  RECHeaderInfo->SIVideoStreamType = Buffer[p + 0x0026];
  RECHeaderInfo->SIAudioStreamType = Buffer[p + 0x0027];

  //Event Info
  p = 0x0044;
  memcpy(RECHeaderInfo->EventUnknown1, &Buffer[p], 2);
  RECHeaderInfo->EventDuration       = 60 * Buffer[p +  3] + Buffer[p +  2];
  RECHeaderInfo->EventEventID        = getDword(&Buffer[p + 0x0004], WrongEndian);
  RECHeaderInfo->EventStartTime      = getDword(&Buffer[p + 0x0008], WrongEndian);
  RECHeaderInfo->EventEndTime        = getDword(&Buffer[p + 0x000c], WrongEndian);
  RECHeaderInfo->EventRunningStatus  = Buffer[p + 0x0010];
  EventTextLength                    = Buffer[p + 0x0011];
  RECHeaderInfo->EventParentalRate   = Buffer[p + 0x0012];
  strncpy(RECHeaderInfo->EventEventName, &Buffer[p + 0x0013], EventTextLength);
  strncpy(RECHeaderInfo->EventEventDescription, &Buffer[p + 0x0013 + EventTextLength], 273 - EventTextLength);

  //Extended Event Info
  p = 0x0168;
  DecodeExtInfo(Buffer, p, RECHeaderInfo);

  //Transponder info
  p = 0x0574;
  RECHeaderInfo->TPSatIndex      = Buffer[p + 0x0000];
  RECHeaderInfo->TPChannelNumber = Buffer[p + 0x0001];
  RECHeaderInfo->TPBandwidth     = Buffer[p + 0x0002];
  RECHeaderInfo->TPUnknown2      = Buffer[p + 0x0003];
  RECHeaderInfo->TPFrequency     = getDword(&Buffer[p + 0x0004], WrongEndian);
  RECHeaderInfo->TPTSID          = getWord(&Buffer[p + 0x0008], WrongEndian);
  RECHeaderInfo->TPLPHPStream    = Buffer[p + 0x000a];
  RECHeaderInfo->TPUnknown4      = Buffer[p + 0x000b];
  RECHeaderInfo->TPOriginalNetworkID  = getWord(&Buffer[p + 0x000c], WrongEndian);
  RECHeaderInfo->TPNetworkID     = getWord(&Buffer[p + 0x000e], WrongEndian);

  //Crypt Info: see header

  //Bookmarks
  p = 0x0584;
  RECHeaderInfo->NrBookmarks = getDword(&Buffer[p + 0x0000], WrongEndian);
  memcpy(RECHeaderInfo->Bookmark, &Buffer[p + 0x0004], 177 * sizeof(dword));
  RECHeaderInfo->Resume = getDword(&Buffer[p + 0x02c8], WrongEndian);

  TRACEEXIT;
}

void HDD_DecodeRECHeader_ST_TMSC(byte *Buffer, tRECHeaderInfo *RECHeaderInfo)
{
  TRACEENTER;

  dword                 p;
  word                  Flags;
  byte                  EventTextLength;

  //Header
  p = 0;
  memcpy(RECHeaderInfo->HeaderUnknown2, &Buffer[p + 6], 2);
  RECHeaderInfo->HeaderStartTime = getDword(&Buffer[p + 0x0008], WrongEndian);
  RECHeaderInfo->HeaderDuration  = getWord(&Buffer[p + 0x000c], WrongEndian);
  RECHeaderInfo->HeaderDurationSec  = getWord(&Buffer[p + 0x000e], WrongEndian);

  RECHeaderInfo->CryptFlag   = Buffer[p + 0x0010] & 0x03;
  RECHeaderInfo->HeaderFlags = Buffer[p + 0x0010] & 0xfc;

  RECHeaderInfo->HeaderCopyFlag = Buffer[p + 0x0011] & 0x80;
  RECHeaderInfo->HeaderTSFlag = Buffer[p + 0x0011] & 0x40;
  RECHeaderInfo->HeaderFlags2 = Buffer[p + 0x0011] & 0x3f;

  memcpy(RECHeaderInfo->HeaderUnknown4, &Buffer[p + 0x0012], 10);

  //Service Info
  p = 0x001c;
  RECHeaderInfo->SISatIndex    =  Buffer[p + 0x0000];
  RECHeaderInfo->SIServiceType =  Buffer[p + 0x0001];

  Flags = getWord(&Buffer[p +0x0002], WrongEndian);
  RECHeaderInfo->SITPIdx     =  Flags & 0x3ff;
  RECHeaderInfo->SITunerNum  = (Flags >> 10) & 3;
  RECHeaderInfo->SIDelFlag   = (Flags >> 12) & 1;
  RECHeaderInfo->SICASFlag   = (Flags >> 13) & 1;
  RECHeaderInfo->SILockFlag  = (Flags >> 14) & 1;
  RECHeaderInfo->SISkipFlag  =  Flags >> 15;

  RECHeaderInfo->SIServiceID = getWord(&Buffer[p + 0x0004], WrongEndian);
  RECHeaderInfo->SIPMTPID    = getWord(&Buffer[p + 0x0006], WrongEndian);
  RECHeaderInfo->SIPCRPID    = getWord(&Buffer[p + 0x0008], WrongEndian);
  RECHeaderInfo->SIVideoPID  = getWord(&Buffer[p + 0x000a], WrongEndian);
  RECHeaderInfo->SIAudioPID  = getWord(&Buffer[p + 0x000c], WrongEndian);

  strncpy(RECHeaderInfo->SISvcName, &Buffer[p + 0x000e], 24);

  RECHeaderInfo->SIVideoStreamType = Buffer[p + 0x0026];
  RECHeaderInfo->SIAudioStreamType = Buffer[p + 0x0027];

  //Event Info
  p = 0x0044;
  memcpy(RECHeaderInfo->EventUnknown1, &Buffer[p], 2);
  RECHeaderInfo->EventDuration       = 60 * Buffer[p +  3] + Buffer[p +  2];
  RECHeaderInfo->EventEventID        = getDword(&Buffer[p + 0x0004], WrongEndian);
  RECHeaderInfo->EventStartTime      = getDword(&Buffer[p + 0x0008], WrongEndian);
  RECHeaderInfo->EventEndTime        = getDword(&Buffer[p + 0x000c], WrongEndian);
  RECHeaderInfo->EventRunningStatus  = Buffer[p + 0x0010];
  EventTextLength                    = Buffer[p + 0x0011];
  RECHeaderInfo->EventParentalRate   = Buffer[p + 0x0012];
  strncpy(RECHeaderInfo->EventEventName, &Buffer[p + 0x0013], EventTextLength);
  strncpy(RECHeaderInfo->EventEventDescription, &Buffer[p + 0x0013 + EventTextLength], 273 - EventTextLength);

  //Extended Event Info
  p = 0x0168;
  DecodeExtInfo(Buffer, p, RECHeaderInfo);

  //Transponder info
  p = 0x0574;
  RECHeaderInfo->TPFrequency          = getDword(&Buffer[p + 0x0000], WrongEndian) >> 8;
  RECHeaderInfo->TPSymbolRate         = getWord(&Buffer[p + 0x0004], WrongEndian);
  RECHeaderInfo->TPTSID               = getWord(&Buffer[p + 0x0006], WrongEndian);
  RECHeaderInfo->TPOriginalNetworkID  = getWord(&Buffer[p + 0x0008], WrongEndian);
  RECHeaderInfo->TPModulation         = Buffer[p + 0x000a];
  RECHeaderInfo->TPUnknown6           = Buffer[p + 0x000b];

  //Crypt Info: see header flags

  //Bookmarks
  p = 0x0580;
  RECHeaderInfo->NrBookmarks = getDword(&Buffer[p + 0x0000], WrongEndian);
  memcpy(RECHeaderInfo->Bookmark, &Buffer[p + 0x0004], 177 * sizeof(dword));
  RECHeaderInfo->Resume = getDword(&Buffer[p + 0x02c8], WrongEndian);

  TRACEEXIT;
}

void HDD_DecodeRECHeader_ST_TF7k7HDPVR(byte *Buffer, tRECHeaderInfo *RECHeaderInfo)
{
  TRACEENTER;

  dword                 p;
  word                  TPFlags1;
  byte                  EventTextLength;

  //Header
  p = 0x4d0;
  memcpy(RECHeaderInfo->HeaderUnknown2, &Buffer[p + 0x0006], 2);
  RECHeaderInfo->HeaderDuration  = getWord(&Buffer[p + 0x0008], WrongEndian);
  RECHeaderInfo->HeaderSvcNumber = getWord(&Buffer[p + 0x000a], WrongEndian);
  RECHeaderInfo->HeaderSvcType   = getWord(&Buffer[p + 0x000c], WrongEndian);

  //Service Info
  p = 0x04de;
  RECHeaderInfo->SISatIndex  =  Buffer[p + 0x0000];
  RECHeaderInfo->SIServiceType = Buffer[p + 0x0001];

  TPFlags1 = getWord(&Buffer[p + 0x0002], WrongEndian);
  RECHeaderInfo->SITPIdx     =  TPFlags1 & 0x3ff;
  RECHeaderInfo->SITunerNum  = (TPFlags1 >> 10) & 3;
  RECHeaderInfo->SISkipFlag  = (TPFlags1 >> 12) & 1;
  RECHeaderInfo->SILockFlag  = (TPFlags1 >> 13) & 1;
  RECHeaderInfo->SICASFlag   = (TPFlags1 >> 14) & 1;
  RECHeaderInfo->SIDelFlag   = (TPFlags1 >> 15) & 1;

  RECHeaderInfo->SIServiceID = getWord(&Buffer[p + 0x0004], WrongEndian);
  RECHeaderInfo->SIPMTPID    = getWord(&Buffer[p + 0x0006], WrongEndian);
  RECHeaderInfo->SIPCRPID    = getWord(&Buffer[p + 0x0008], WrongEndian);
  RECHeaderInfo->SIVideoPID  = getWord(&Buffer[p + 0x000a], WrongEndian);
  RECHeaderInfo->SIAudioPID  = getWord(&Buffer[p + 0x000c], WrongEndian);
  strncpy(RECHeaderInfo->SISvcName, &Buffer[p + 0x000e], 28);

  //Transponder Info
  p = 0x0508;
  RECHeaderInfo->TPSatIndex           = Buffer[p + 0x0000];

  RECHeaderInfo->TPFlags2             = Buffer[p + 0x0001];
  RECHeaderInfo->TPPolarization       =  RECHeaderInfo->TPFlags2 & 1;
  RECHeaderInfo->TPMode               = (RECHeaderInfo->TPFlags2 >> 1) & 7;
  RECHeaderInfo->TPFlags2             = RECHeaderInfo->TPFlags2 & 0x00f0;

  memcpy(RECHeaderInfo->TPUnknown3, &Buffer[p + 0x0002], 2);
  RECHeaderInfo->TPFrequency          = getDword(&Buffer[p + 0x0004], WrongEndian);
  RECHeaderInfo->TPSymbolRate         = getWord(&Buffer[p + 0x0008], WrongEndian);
  RECHeaderInfo->TPTSID               = getWord(&Buffer[p + 0x000a], WrongEndian);
  memcpy(RECHeaderInfo->TPUnknown5, &Buffer[p + 0x000c], 2);
  RECHeaderInfo->TPOriginalNetworkID  = getWord(&Buffer[p + 0x000e], WrongEndian);

  //Event Info
  p = 0x0518;
  memcpy(RECHeaderInfo->EventUnknown1, &Buffer[p], 2);
  RECHeaderInfo->EventDuration       = 60 * Buffer[p + 0x0003] + Buffer[p + 0x0002];
  RECHeaderInfo->EventEventID        = getDword(&Buffer[p + 0x0004], WrongEndian);
  RECHeaderInfo->EventStartTime      = getDword(&Buffer[p + 0x0008], WrongEndian);
  RECHeaderInfo->EventEndTime        = getDword(&Buffer[p + 0x000c], WrongEndian);
  RECHeaderInfo->EventRunningStatus  = Buffer[p + 0x0010];
  EventTextLength                    = Buffer[p + 0x0011];
  RECHeaderInfo->EventParentalRate   = Buffer[p + 0x0012];
  strncpy(RECHeaderInfo->EventEventName, &Buffer[p + 0x0013], EventTextLength);
  strncpy(RECHeaderInfo->EventEventDescription, &Buffer[p + 0x0013 + EventTextLength], 257 - EventTextLength);
  RECHeaderInfo->EventServiceID      =  getWord(&Buffer[p + 0x0114], WrongEndian);
  memcpy(RECHeaderInfo->EventUnknown2, &Buffer[p + 0x0116], 14);

  //Extended Event Info
  p = 0x063c;
  DecodeExtInfo(Buffer, p, RECHeaderInfo);

  //Crypt Info
  p = 0x0a48;
  RECHeaderInfo->CryptFlag = Buffer[p + 0x0000];
  memcpy(RECHeaderInfo->CryptUnknown2, &Buffer[p + 0x0001], 3);

  //Bookmarks
  p = 0x0a4c;
  memcpy(RECHeaderInfo->Bookmark, &Buffer[p + 0x0000], 64 * sizeof(dword));
  RECHeaderInfo->Resume = getDword(&Buffer[p + 0x0100], WrongEndian);

  TRACEEXIT;
}


bool HDD_DecodeRECHeader(byte *Buffer, tRECHeaderInfo *RECHeaderInfo, SYSTEM_TYPE SystemType)
{
  TRACEENTER;

  bool ret;

  if(SystemType == ST_UNKNOWN) SystemType = GetSystemType();

  memset(RECHeaderInfo, 0, sizeof(tRECHeaderInfo));

  //Is this a REC header?
  RECHeaderInfo->HeaderMagic     = (Buffer[0] << 24) | (Buffer[1] << 16) | (Buffer[2] << 8) | Buffer[3];
  if(RECHeaderInfo->HeaderMagic != 0x54467263)
  {
    TRACEEXIT;
    return FALSE;
  }

  RECHeaderInfo->HeaderVersion = getWord(&Buffer[4], FALSE);

  //Check the endianess of the file
  WrongEndian = (RECHeaderInfo->HeaderVersion == 0x0050) || (RECHeaderInfo->HeaderVersion == 0x1050) || (RECHeaderInfo->HeaderVersion == 0x0080);
  if(WrongEndian) RECHeaderInfo->HeaderVersion = getWord(&Buffer[4], TRUE);

  ret = TRUE;
  switch(SystemType)
  {
    case ST_UNKNOWN:    ret = FALSE; break;
    case ST_S:          HDD_DecodeRECHeader_ST_S(Buffer, RECHeaderInfo); break;
    case ST_T:          HDD_DecodeRECHeader_ST_T(Buffer, RECHeaderInfo); break;
    case ST_C:          HDD_DecodeRECHeader_ST_C(Buffer, RECHeaderInfo); break;
    case ST_T5700:      HDD_DecodeRECHeader_ST_T5700(Buffer, RECHeaderInfo); break;
    case ST_TMSS:       HDD_DecodeRECHeader_ST_TMSS(Buffer, RECHeaderInfo); break;
    case ST_TMST:       HDD_DecodeRECHeader_ST_TMST(Buffer, RECHeaderInfo); break;
    case ST_TMSC:       HDD_DecodeRECHeader_ST_TMSC(Buffer, RECHeaderInfo); break;
    case ST_T5800:      HDD_DecodeRECHeader_ST_T5800(Buffer, RECHeaderInfo); break;
    case ST_ST:         ret = FALSE; break;
    case ST_CT:         ret = FALSE; break;
    case ST_TF7k7HDPVR: HDD_DecodeRECHeader_ST_TF7k7HDPVR(Buffer, RECHeaderInfo); break;
    case ST_NRTYPES:    ret = FALSE; break;
  }

  TRACEEXIT;
  return ret;
}
