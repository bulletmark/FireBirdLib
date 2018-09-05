#include <string.h>
#include "FBLib_rec.h"

void setWord(void *buffer, word Data, bool BigEndian)
{
  TRACEENTER;

  byte                 *p;

  p = (byte*)buffer;
  if(BigEndian)
  {
    p[0] = Data >> 8;
    p[1] = Data & 0xff;
  }
  else
  {
    p[0] = Data & 0xff;
    p[1] = Data >> 8;
  }

  TRACEEXIT;
}

void setDword(void *buffer, dword Data, bool BigEndian)
{
  TRACEENTER;

  byte                 *p;

  p = (byte*)buffer;
  if(BigEndian)
  {
    p[0] =  Data >> 24;
    p[1] = (Data >> 16) & 0xff;
    p[2] = (Data >>  8) & 0xff;
    p[3] =  Data & 0xff;
  }
  else
  {
    p[3] =  Data >> 24;
    p[2] = (Data >> 16) & 0xff;
    p[1] = (Data >>  8) & 0xff;
    p[0] =  Data & 0xff;
  }

  TRACEEXIT;
}

void EncodeExtInfo(byte *Buffer, dword p, tRECHeaderInfo *RECHeaderInfo, bool BigEndian)
{
  TRACEENTER;

  //The extended info structure is identical on all Toppies
  setWord(&Buffer[p + 0x0000], RECHeaderInfo->ExtEventServiceID , BigEndian);
  setWord(&Buffer[p + 0x0002], RECHeaderInfo->ExtEventTextLength, BigEndian);
  setDword(&Buffer[p + 0x0004], RECHeaderInfo->ExtEventEventID, BigEndian);
  Buffer[p + 0x0408] = RECHeaderInfo->ExtEventNrItemizedPairs;
  memcpy(&Buffer[p + 0x0409], RECHeaderInfo->ExtEventUnknown1, 3);

  if(RECHeaderInfo->ExtEventNrItemizedPairs == 0)
  {
    memcpy(&Buffer[p + 0x0008], RECHeaderInfo->ExtEventText, RECHeaderInfo->ExtEventTextLength);
  }
  else
  {
    char               *pStart, *pEnd, *pItems, *pInfo;

    //Find the border between the itemized data and the description
    pStart = RECHeaderInfo->ExtEventText;
    pEnd = pStart + RECHeaderInfo->ExtEventTextLength;
    pItems = pStart;
    while((*pItems != 0) && (pItems < pEnd))
    {
      pItems++;
    }
    if(pItems != pEnd) pItems++;

    pInfo = &Buffer[p + 0x0008];
    memcpy(pInfo, pItems, pEnd - pItems + 1);
    pInfo += (pEnd - pItems + 1);
    memcpy(pInfo, pStart, pItems - pStart + 1);
  }

  TRACEEXIT;
}

void HDD_EncodeRECHeader_ST_S(byte *Buffer, tRECHeaderInfo *RECHeaderInfo)
{
  TRACEENTER;

  dword                 p;
  word                  w;
  byte                  EventTextLength;

  //Header
  p = 0;
  Buffer[p + 0x0000] = 0x54;
  Buffer[p + 0x0001] = 0x46;
  Buffer[p + 0x0002] = 0x72;
  Buffer[p + 0x0003] = 0x63;

  Buffer[p + 0x0004] = 0x50;
  Buffer[p + 0x0005] = 0x00;

  memcpy(&Buffer[p + 0x0006], RECHeaderInfo->HeaderUnknown2, 2);
  setWord(&Buffer[p + 0x0008], RECHeaderInfo->HeaderDuration, TRUE);
  setWord(&Buffer[p + 0x000a], RECHeaderInfo->HeaderSvcNumber, TRUE);
  setWord(&Buffer[p + 0x000c], RECHeaderInfo->HeaderSvcType, TRUE);

  //Service Info
  p = 0x000e;
  Buffer[p + 0x0000] = RECHeaderInfo->SISatIndex;
  Buffer[p + 0x0001] = RECHeaderInfo->SIServiceType;

  w = (RECHeaderInfo->SITPIdx << 6) |
      (RECHeaderInfo->SITunerNum << 4) |
      (RECHeaderInfo->SISkipFlag << 3) |
      (RECHeaderInfo->SILockFlag << 2) |
      (RECHeaderInfo->SICASFlag << 1) |
       RECHeaderInfo->SIDelFlag;
  setWord(&Buffer[p + 0x0002], w, TRUE);

  setWord(&Buffer[p + 0x0004], RECHeaderInfo->SIServiceID, TRUE);
  setWord(&Buffer[p + 0x0006], RECHeaderInfo->SIPMTPID, TRUE);
  setWord(&Buffer[p + 0x0008], RECHeaderInfo->SIPCRPID, TRUE);
  setWord(&Buffer[p + 0x000a], RECHeaderInfo->SIVideoPID, TRUE);
  setWord(&Buffer[p + 0x000c], RECHeaderInfo->SIAudioPID, TRUE);
  strncpy(&Buffer[p + 0x000e], RECHeaderInfo->SISvcName, 24);

  //Transponder Info
  p = 0x0034;
  Buffer[p + 0x0000] = RECHeaderInfo->TPSatIndex;
  Buffer[p + 0x0001] = (RECHeaderInfo->TPPolarization << 7) | (RECHeaderInfo->TPMode << 4);

  memcpy(&Buffer[p + 0x0002], RECHeaderInfo->TPUnknown3, 2);
  setDword(&Buffer[p + 0x0004], RECHeaderInfo->TPFrequency, TRUE);
  setWord(&Buffer[p +  0x0008], RECHeaderInfo->TPSymbolRate, TRUE);
  setWord(&Buffer[p + 0x000a], RECHeaderInfo->TPTSID, TRUE);
  memcpy(&Buffer[p + 0x000c], RECHeaderInfo->TPUnknown5, 2);
  setWord(&Buffer[p + 0x000e], RECHeaderInfo->TPOriginalNetworkID, TRUE);

  //Event Info
  p = 0x0044;
  memcpy(&Buffer[p], RECHeaderInfo->EventUnknown1, 2);
  Buffer[p + 0x0002] = (int)(RECHeaderInfo->EventDuration / 60);
  Buffer[p + 0x0003] = RECHeaderInfo->EventDuration % 60;
  setDword(&Buffer[p + 0x0004], RECHeaderInfo->EventEventID, TRUE);
  setDword(&Buffer[p + 0x0008], RECHeaderInfo->EventStartTime, TRUE);
  setDword(&Buffer[p + 0x000c], RECHeaderInfo->EventEndTime, TRUE);
  Buffer[p + 0x0010] = RECHeaderInfo->EventRunningStatus;
  EventTextLength = strlen(RECHeaderInfo->EventEventName);
  Buffer[p + 0x0011] = EventTextLength;
  Buffer[p + 0x0012] = RECHeaderInfo->EventParentalRate;
  strncpy(&Buffer[p + 0x0013], RECHeaderInfo->EventEventName, EventTextLength);
  strncpy(&Buffer[p + 0x0013 + EventTextLength], RECHeaderInfo->EventEventDescription, 257 - EventTextLength);
  setWord(&Buffer[p + 0x0114], RECHeaderInfo->EventServiceID, TRUE);
  memcpy(&Buffer[p + 0x0116], RECHeaderInfo->EventUnknown2, 14);

  //Extended Event Info
  p = 0x0168;
  EncodeExtInfo(Buffer, p, RECHeaderInfo, TRUE);

  //Crypt Info
  p = 0x0574;
  Buffer[p + 0x0000] = RECHeaderInfo->CryptFlag;
  memcpy(&Buffer[p + 0x0001], RECHeaderInfo->CryptUnknown2, 3);

  //Bookmarks
  p = 0x0578;
  memcpy(&Buffer[p + 0x0000], RECHeaderInfo->Bookmark, 64 * sizeof(dword));
  setDword(&Buffer[p + 0x0100], RECHeaderInfo->Resume, TRUE);

  TRACEEXIT;
}

void HDD_EncodeRECHeader_ST_T(byte *Buffer, tRECHeaderInfo *RECHeaderInfo)
{
  TRACEENTER;

  dword                 p;
  word                  Flags;
  byte                  EventTextLength;

  //Header
  p = 0;
  Buffer[p + 0x0000] = 0x54;
  Buffer[p + 0x0001] = 0x46;
  Buffer[p + 0x0002] = 0x72;
  Buffer[p + 0x0003] = 0x63;

  Buffer[p + 0x0004] = 0x50;
  Buffer[p + 0x0005] = 0x00;

  memcpy(&Buffer[p + 0x0006], RECHeaderInfo->HeaderUnknown2, 2);
  setWord(&Buffer[p + 0x0008], RECHeaderInfo->HeaderDuration, TRUE);
  setWord(&Buffer[p + 0x000a], RECHeaderInfo->HeaderSvcNumber, TRUE);
  setWord(&Buffer[p + 0x000c], RECHeaderInfo->HeaderSvcType, TRUE);

  //Service Info
  p = 0x000e;
  Buffer[p + 0x0000] = RECHeaderInfo->SISatIndex;
  Buffer[p + 0x0001] = RECHeaderInfo->SIServiceType;

  Flags = (RECHeaderInfo->SITPIdx << 6) |
          (RECHeaderInfo->SITunerNum << 4) |
          (RECHeaderInfo->SISkipFlag << 3) |
          (RECHeaderInfo->SILockFlag << 2) |
          (RECHeaderInfo->SICASFlag << 1) |
           RECHeaderInfo->SIDelFlag;
  setWord(&Buffer[p + 0x0002], Flags, TRUE);

  setWord(&Buffer[p + 0x0004], RECHeaderInfo->SIServiceID, TRUE);
  setWord(&Buffer[p + 0x0006], RECHeaderInfo->SIPMTPID, TRUE);
  setWord(&Buffer[p + 0x0008], RECHeaderInfo->SIPCRPID, TRUE);
  setWord(&Buffer[p + 0x000a], RECHeaderInfo->SIVideoPID, TRUE);
  setWord(&Buffer[p + 0x000c], RECHeaderInfo->SIAudioPID, TRUE);
  strncpy(&Buffer[p + 0x000e], RECHeaderInfo->SISvcName, 24);

  //Transponder Info
  p = 0x0034;
  setWord(&Buffer[p + 0x0000], RECHeaderInfo->TPChannelNumber, TRUE);
  Buffer[p + 0x0002] = RECHeaderInfo->TPBandwidth;
  Buffer[p + 0x0003] = RECHeaderInfo->TPUnknown2;
  setDword(&Buffer[p + 0x0004], RECHeaderInfo->TPFrequency, TRUE);
  setWord(&Buffer[p + 0x0008], RECHeaderInfo->TPTSID, TRUE);
  Buffer[p + 0x000a] = RECHeaderInfo->TPLPHPStream;
  Buffer[p + 0x000b] = RECHeaderInfo->TPUnknown4;
  setWord(&Buffer[p + 0x000c], RECHeaderInfo->TPOriginalNetworkID, TRUE);
  setWord(&Buffer[p + 0x000e], RECHeaderInfo->TPNetworkID, TRUE);

  //Event Info
  p = 0x0044;
  memcpy(&Buffer[p], RECHeaderInfo->EventUnknown1, 2);
  Buffer[p + 0x0002] = (int)(RECHeaderInfo->EventDuration / 60);
  Buffer[p + 0x0003] = RECHeaderInfo->EventDuration % 60;
  setDword(&Buffer[p + 0x0004], RECHeaderInfo->EventEventID, TRUE);
  setDword(&Buffer[p + 0x0008], RECHeaderInfo->EventStartTime, TRUE);
  setDword(&Buffer[p + 0x000c], RECHeaderInfo->EventEndTime, TRUE);
  Buffer[p + 0x0010] = RECHeaderInfo->EventRunningStatus;
  EventTextLength = strlen(RECHeaderInfo->EventEventName);
  Buffer[p + 0x0011] = EventTextLength;
  Buffer[p + 0x0012] = RECHeaderInfo->EventParentalRate;
  strncpy(&Buffer[p + 0x0013], RECHeaderInfo->EventEventName, EventTextLength);
  strncpy(&Buffer[p + 0x0013 + EventTextLength], RECHeaderInfo->EventEventDescription, 257 - EventTextLength);
  setWord(&Buffer[p + 0x0114], RECHeaderInfo->EventServiceID, TRUE);
  memcpy(&Buffer[p + 0x0116], RECHeaderInfo->EventUnknown2, 14);

  //Extended Event Info
  p = 0x0168;
  EncodeExtInfo(Buffer, p, RECHeaderInfo, TRUE);

  //Crypt Info
  p = 0x0574;
  Buffer[p + 0x0000] = RECHeaderInfo->CryptFlag;
  memcpy(&Buffer[p + 0x0001], RECHeaderInfo->CryptUnknown2, 3);

  //Bookmarks
  p = 0x0578;
  memcpy(&Buffer[p + 0x0000], RECHeaderInfo->Bookmark, 64 * sizeof(dword));
  setDword(&Buffer[p + 0x0100], RECHeaderInfo->Resume, TRUE);

  TRACEEXIT;
}

void HDD_EncodeRECHeader_ST_C(byte *Buffer, tRECHeaderInfo *RECHeaderInfo)
{
  TRACEENTER;

  dword                 p;
  word                  Flags;
  byte                  EventTextLength;

  //Header
  p = 0;
  Buffer[p + 0x0000] = 0x54;
  Buffer[p + 0x0001] = 0x46;
  Buffer[p + 0x0002] = 0x72;
  Buffer[p + 0x0003] = 0x63;

  Buffer[p + 0x0004] = 0x50;
  Buffer[p + 0x0005] = 0x00;

  memcpy(&Buffer[p + 6], RECHeaderInfo->HeaderUnknown2, 2);
  setWord(&Buffer[p + 0x0008], RECHeaderInfo->HeaderDuration, TRUE);
  setWord(&Buffer[p + 0x000a], RECHeaderInfo->HeaderSvcNumber, TRUE);
  setWord(&Buffer[p + 0x000c], RECHeaderInfo->HeaderSvcType, TRUE);

  //Service Info
  p = 0x000e;
  Buffer[p + 0x0000] = RECHeaderInfo->SISatIndex;
  Buffer[p + 0x0001] = RECHeaderInfo->SIServiceType;

  Flags = (RECHeaderInfo->SITPIdx >> 6) |
          (RECHeaderInfo->SITunerNum << 4) |
          (RECHeaderInfo->SIDelFlag << 3) |
          (RECHeaderInfo->SICASFlag << 2) |
          (RECHeaderInfo->SILockFlag << 1) |
           RECHeaderInfo->SISkipFlag;
  setWord(&Buffer[p + 0x0002], Flags, TRUE);

  setWord(&Buffer[p + 0x0004], RECHeaderInfo->SIServiceID, TRUE);
  setWord(&Buffer[p + 0x0006], RECHeaderInfo->SIPMTPID, TRUE);
  setWord(&Buffer[p + 0x0008], RECHeaderInfo->SIPCRPID, TRUE);
  setWord(&Buffer[p + 0x000a], RECHeaderInfo->SIVideoPID, TRUE);
  setWord(&Buffer[p + 0x000c], RECHeaderInfo->SIAudioPID, TRUE);
  strncpy(&Buffer[p + 0x000e], RECHeaderInfo->SISvcName, 24);

  //Transponder Info
  p = 0x0034;
  setDword(&Buffer[p + 0x0000], RECHeaderInfo->TPFrequency, TRUE);
  setWord(&Buffer[p + 0x0004], RECHeaderInfo->TPSymbolRate, TRUE);
  setWord(&Buffer[p + 0x0006], RECHeaderInfo->TPTSID, TRUE);
  setWord(&Buffer[p + 0x0008], RECHeaderInfo->TPOriginalNetworkID, TRUE);
  Buffer[p + 10] = RECHeaderInfo->TPModulation;
  Buffer[p + 11] = RECHeaderInfo->TPUnknown6;

  //Event Info
  p = 0x0040;
  memcpy(&Buffer[p], RECHeaderInfo->EventUnknown1, 2);
  Buffer[p + 0x0002] = (int)(RECHeaderInfo->EventDuration / 60);
  Buffer[p + 0x0003] = RECHeaderInfo->EventDuration % 60;
  setDword(&Buffer[p + 0x0004], RECHeaderInfo->EventEventID, TRUE);
  setDword(&Buffer[p + 0x0008], RECHeaderInfo->EventStartTime, TRUE);
  setDword(&Buffer[p + 0x000c], RECHeaderInfo->EventEndTime, TRUE);
  Buffer[p + 0x0010] = RECHeaderInfo->EventRunningStatus;
  EventTextLength = strlen(RECHeaderInfo->EventEventName);
  Buffer[p + 0x0011] = EventTextLength;
  Buffer[p + 0x0012] = RECHeaderInfo->EventParentalRate;
  strncpy(&Buffer[p + 0x0013], RECHeaderInfo->EventEventName, EventTextLength);
  strncpy(&Buffer[p + 0x0013 + EventTextLength], RECHeaderInfo->EventEventDescription, 257 - EventTextLength);
  setWord(&Buffer[p + 0x0114], RECHeaderInfo->EventServiceID, TRUE);
  memcpy(&Buffer[p + 0x0116], RECHeaderInfo->EventUnknown2, 14);

  //Extended Event Info
  p = 0x0164;
  EncodeExtInfo(Buffer, p, RECHeaderInfo, TRUE);

  //Crypt Info
  p = 0x0570;
  Buffer[p + 0x0000] = RECHeaderInfo->CryptFlag;
  memcpy(&Buffer[p + 0x0001], RECHeaderInfo->CryptUnknown2, 3);

  //Bookmarks
  p = 0x0574;
  memcpy(&Buffer[p + 0x0000], RECHeaderInfo->Bookmark, 64 * sizeof(dword));
  setDword(&Buffer[p + 0x0100], RECHeaderInfo->Resume, TRUE);

  TRACEEXIT;
}

void HDD_EncodeRECHeader_ST_T5700(byte *Buffer, tRECHeaderInfo *RECHeaderInfo)
{
  TRACEENTER;

  dword                 p;
  word                  Flags;
  byte                  EventTextLength;

  //Header
  p = 0;
  Buffer[p + 0x0000] = 0x54;
  Buffer[p + 0x0001] = 0x46;
  Buffer[p + 0x0002] = 0x72;
  Buffer[p + 0x0003] = 0x63;

  Buffer[p + 0x0004] = 0x50;
  Buffer[p + 0x0005] = 0x00;

  memcpy(&Buffer[p + 6], RECHeaderInfo->HeaderUnknown2, 2);
  setWord(&Buffer[p + 0x0008], RECHeaderInfo->HeaderDuration, TRUE);
  setWord(&Buffer[p + 0x000a], RECHeaderInfo->HeaderSvcNumber, TRUE);
  setWord(&Buffer[p + 0x000c], RECHeaderInfo->HeaderSvcType, TRUE);

  //Service Info
  p = 0x000e;
  Buffer[p + 0x0000] = RECHeaderInfo->SISatIndex;
  Buffer[p + 0x0001] = RECHeaderInfo->SIServiceType;

  Flags = (RECHeaderInfo->SITPIdx    << 6) |
          (RECHeaderInfo->SITunerNum << 4) |
          (RECHeaderInfo->SIDelFlag  << 3) |
          (RECHeaderInfo->SICASFlag  << 2) |
          (RECHeaderInfo->SILockFlag << 1) |
           RECHeaderInfo->SISkipFlag;
  setWord(&Buffer[p + 0x0002], Flags, TRUE);

  setWord(&Buffer[p + 0x0004], RECHeaderInfo->SIServiceID, TRUE);
  setWord(&Buffer[p + 0x0006], RECHeaderInfo->SIPMTPID, TRUE);
  setWord(&Buffer[p + 0x0008], RECHeaderInfo->SIPCRPID, TRUE);
  setWord(&Buffer[p + 0x000a], RECHeaderInfo->SIVideoPID, TRUE);
  setWord(&Buffer[p + 0x000c], RECHeaderInfo->SIAudioPID, TRUE);
  strncpy(&Buffer[p + 0x000e], RECHeaderInfo->SISvcName, 24);

  //Transponder Info
  p = 0x0034;
  setWord(&Buffer[p + 0x0000], RECHeaderInfo->TPChannelNumber, TRUE);
  Buffer[p + 0x0002] = RECHeaderInfo->TPBandwidth;
  Buffer[p + 0x0003] = RECHeaderInfo->TPUnknown2;
  setDword(&Buffer[p + 0x0004], RECHeaderInfo->TPFrequency, TRUE);
  setWord(&Buffer[p + 0x0008], RECHeaderInfo->TPTSID, TRUE);
  Buffer[p + 0x000a] = RECHeaderInfo->TPLPHPStream;
  Buffer[p + 0x000b] = RECHeaderInfo->TPUnknown4;
  setWord(&Buffer[p + 0x000c], RECHeaderInfo->TPOriginalNetworkID, TRUE);
  setWord(&Buffer[p + 0x000e], RECHeaderInfo->TPNetworkID, TRUE);
  memcpy(&Buffer[p + 0x0010], RECHeaderInfo->TPUnknown7, 8);

  //Event Info
  p = 0x004c;
  memcpy(&Buffer[p], RECHeaderInfo->EventUnknown1, 2);
  Buffer[p + 0x0002] = (int)(RECHeaderInfo->EventDuration / 60);
  Buffer[p + 0x0003] = RECHeaderInfo->EventDuration % 60;
  setDword(&Buffer[p + 0x0004], RECHeaderInfo->EventEventID, TRUE);
  setDword(&Buffer[p + 0x0008], RECHeaderInfo->EventStartTime, TRUE);
  setDword(&Buffer[p + 0x000c], RECHeaderInfo->EventEndTime, TRUE);
  Buffer[p + 0x0010] = RECHeaderInfo->EventRunningStatus;
  EventTextLength = strlen(RECHeaderInfo->EventEventName);
  Buffer[p + 0x0011] = EventTextLength;
  Buffer[p + 0x0012] = RECHeaderInfo->EventParentalRate;
  strncpy(&Buffer[p + 0x0013], RECHeaderInfo->EventEventName, EventTextLength);
  strncpy(&Buffer[p + 0x0013 + EventTextLength], RECHeaderInfo->EventEventDescription, 257 - EventTextLength);
  setWord(&Buffer[p + 0x0114], RECHeaderInfo->EventServiceID, TRUE);
  memcpy(&Buffer[p + 0x0116], RECHeaderInfo->EventUnknown2, 14);

  //Extended Event Info
  p = 0x0170;
  EncodeExtInfo(Buffer, p, RECHeaderInfo, TRUE);

  //Crypt Info
  p = 0x057c;
  Buffer[p + 0x0000] = RECHeaderInfo->CryptFlag;
  memcpy(&Buffer[p + 0x0001], RECHeaderInfo->CryptUnknown2, 3);

  //Bookmarks
  p = 0x0580;
  memcpy(&Buffer[p + 0x0000], RECHeaderInfo->Bookmark, 64 * sizeof(dword));
  setDword(&Buffer[p + 0x0100], RECHeaderInfo->Resume, TRUE);

  TRACEEXIT;
}

void HDD_EncodeRECHeader_ST_T5800(byte *Buffer, tRECHeaderInfo *RECHeaderInfo)
{
  TRACEENTER;

  dword                 p;
  word                  Flags;
  byte                  EventTextLength;

  //Header
  p = 0;
  Buffer[p + 0x0000] = 0x54;
  Buffer[p + 0x0001] = 0x46;
  Buffer[p + 0x0002] = 0x72;
  Buffer[p + 0x0003] = 0x63;

  Buffer[p + 0x0004] = 0x50;
  Buffer[p + 0x0005] = 0x10;

  memcpy(&Buffer[p + 6], RECHeaderInfo->HeaderUnknown2, 2);
  setWord(&Buffer[p + 0x0008], RECHeaderInfo->HeaderDuration, TRUE);
  setWord(&Buffer[p + 0x000a], RECHeaderInfo->HeaderSvcNumber, TRUE);
  setWord(&Buffer[p + 0x000c], RECHeaderInfo->HeaderSvcType, TRUE);

  //Service Info
  p = 0x000e;
  Buffer[p + 0x0000] = RECHeaderInfo->SISatIndex;
  Buffer[p + 0x0001] = RECHeaderInfo->SIServiceType;

  Flags = (RECHeaderInfo->SITPIdx    << 6) |
          (RECHeaderInfo->SITunerNum << 4) |
          (RECHeaderInfo->SIDelFlag  << 3) |
          (RECHeaderInfo->SICASFlag  << 2) |
          (RECHeaderInfo->SILockFlag << 1) |
           RECHeaderInfo->SISkipFlag;
  setWord(&Buffer[p + 0x0002], Flags, TRUE);

  setWord(&Buffer[p + 0x0004], RECHeaderInfo->SIServiceID, TRUE);
  setWord(&Buffer[p + 0x0006], RECHeaderInfo->SIPMTPID, TRUE);
  setWord(&Buffer[p + 0x0008], RECHeaderInfo->SIPCRPID, TRUE);
  setWord(&Buffer[p + 0x000a], RECHeaderInfo->SIVideoPID, TRUE);
  setWord(&Buffer[p + 0x000c], RECHeaderInfo->SIAudioPID, TRUE);
  strncpy(&Buffer[p + 0x000e], RECHeaderInfo->SISvcName, 28);

  //Transponder Info
  p = 0x0038;
  setWord(&Buffer[p + 0x0000], RECHeaderInfo->TPChannelNumber, TRUE);
  Buffer[p + 0x0002] = RECHeaderInfo->TPBandwidth;
  Buffer[p + 0x0003] = RECHeaderInfo->TPUnknown2;
  setDword(&Buffer[p + 0x0004], RECHeaderInfo->TPFrequency, TRUE);
  setWord(&Buffer[p + 0x0008], RECHeaderInfo->TPTSID, TRUE);
  Buffer[p + 0x000a] = RECHeaderInfo->TPLPHPStream;
  Buffer[p + 0x000b] = RECHeaderInfo->TPUnknown4;
  setWord(&Buffer[p + 0x000c], RECHeaderInfo->TPOriginalNetworkID, TRUE);
  setWord(&Buffer[p + 0x000e], RECHeaderInfo->TPNetworkID, TRUE);


  //Event Info
  p = 0x0048;
  memcpy(&Buffer[p], RECHeaderInfo->EventUnknown1, 2);
  Buffer[p + 0x0002] = (int)(RECHeaderInfo->EventDuration / 60);
  Buffer[p + 0x0003] = RECHeaderInfo->EventDuration % 60;
  setDword(&Buffer[p + 0x0004], RECHeaderInfo->EventEventID, TRUE);
  setDword(&Buffer[p + 0x0008], RECHeaderInfo->EventStartTime, TRUE);
  setDword(&Buffer[p + 0x000c], RECHeaderInfo->EventEndTime, TRUE);
  Buffer[p + 0x0010] = RECHeaderInfo->EventRunningStatus;
  EventTextLength = strlen(RECHeaderInfo->EventEventName);
  Buffer[p + 0x0011] = EventTextLength;
  Buffer[p + 0x0012] = RECHeaderInfo->EventParentalRate;
  strncpy(&Buffer[p + 0x0013], RECHeaderInfo->EventEventName, EventTextLength);
  strncpy(&Buffer[p + 0x0013 + EventTextLength], RECHeaderInfo->EventEventDescription, 257 - EventTextLength);
  setWord(&Buffer[p + 0x0114], RECHeaderInfo->EventServiceID, TRUE);
  memcpy(&Buffer[p + 0x0116], RECHeaderInfo->EventUnknown2, 10);

  //Extended Event Info
  p = 0x016c;
  EncodeExtInfo(Buffer, p, RECHeaderInfo, TRUE);

  //Crypt Info
  p = 0x0578;
  Buffer[p + 0x0000] = RECHeaderInfo->CryptFlag;
  memcpy(&Buffer[p + 0x0001], RECHeaderInfo->CryptUnknown2, 3);

  //Bookmarks
  p = 0x057c;
  memcpy(&Buffer[p + 0x0000], RECHeaderInfo->Bookmark, 64 * sizeof(dword));
  setDword(&Buffer[p + 0x0100], RECHeaderInfo->Resume, TRUE);

  TRACEEXIT;
}

void HDD_EncodeRECHeader_ST_TMSS(byte *Buffer, tRECHeaderInfo *RECHeaderInfo)
{
  TRACEENTER;

  dword                 p;
  word                  Flags;
  byte                  EventTextLength;

  //Header
  p = 0;
  Buffer[p + 0x0000] = 0x54;
  Buffer[p + 0x0001] = 0x46;
  Buffer[p + 0x0002] = 0x72;
  Buffer[p + 0x0003] = 0x63;

  Buffer[p + 0x0004] = 0x00;
  Buffer[p + 0x0005] = 0x80;

  memcpy(&Buffer[p + 6], RECHeaderInfo->HeaderUnknown2, 2);
  setDword(&Buffer[p + 0x0008], RECHeaderInfo->HeaderStartTime, FALSE);
  setWord(&Buffer[p + 0x000c], RECHeaderInfo->HeaderDuration, FALSE);
  setWord(&Buffer[p + 0x000e], RECHeaderInfo->HeaderDurationSec, FALSE);
  Buffer[p + 0x0010] = (RECHeaderInfo->HeaderFlags & 0xfc) | (RECHeaderInfo->CryptFlag & 0x03);
  Buffer[p + 0x0011] = (RECHeaderInfo->HeaderFlags2 & 0x3f) | (RECHeaderInfo->HeaderCopyFlag ? 0x80 : 0x00) | (RECHeaderInfo->HeaderTSFlag ? 0x40 : 0x00);
  memcpy(&Buffer[p + 0x0012], RECHeaderInfo->HeaderUnknown4, 10);

  //Service Info
  p = 0x001c;
  Buffer[p + 0x0000] = RECHeaderInfo->SISatIndex;
  Buffer[p + 0x0001] = RECHeaderInfo->SIServiceType;

  Flags = (RECHeaderInfo->SISkipFlag << 15) |
          (RECHeaderInfo->SILockFlag << 14) |
          (RECHeaderInfo->SICASFlag << 13) |
          (RECHeaderInfo->SIDelFlag << 12) |
          (RECHeaderInfo->SITunerNum << 10) |
          RECHeaderInfo->SITPIdx;
  setWord(&Buffer[p +0x0002], Flags, FALSE);

  setWord(&Buffer[p + 0x0004], RECHeaderInfo->SIServiceID, FALSE);
  setWord(&Buffer[p + 0x0006], RECHeaderInfo->SIPMTPID, FALSE);
  setWord(&Buffer[p + 0x0008], RECHeaderInfo->SIPCRPID, FALSE);
  setWord(&Buffer[p + 0x000a], RECHeaderInfo->SIVideoPID, FALSE);
  setWord(&Buffer[p + 0x000c], RECHeaderInfo->SIAudioPID, FALSE);

  strncpy(&Buffer[p + 0x000e], RECHeaderInfo->SISvcName, 24);

  Buffer[p + 0x0026] = RECHeaderInfo->SIVideoStreamType;
  Buffer[p + 0x0027] = RECHeaderInfo->SIAudioStreamType;

  //Event Info
  p = 0x0044;
  memcpy(&Buffer[p], RECHeaderInfo->EventUnknown1, 2);
  Buffer[p + 0x0003] = (int)(RECHeaderInfo->EventDuration / 60);
  Buffer[p + 0x0002] = RECHeaderInfo->EventDuration % 60;
  setDword(&Buffer[p + 0x0004], RECHeaderInfo->EventEventID, FALSE);
  setDword(&Buffer[p + 0x0008], RECHeaderInfo->EventStartTime, FALSE);
  setDword(&Buffer[p + 0x000c], RECHeaderInfo->EventEndTime, FALSE);
  Buffer[p + 0x0010] = RECHeaderInfo->EventRunningStatus;
  EventTextLength = strlen(RECHeaderInfo->EventEventName);
  Buffer[p + 0x0011] = EventTextLength;
  Buffer[p + 0x0012] = RECHeaderInfo->EventParentalRate;
  strncpy(&Buffer[p + 0x0013], RECHeaderInfo->EventEventName, EventTextLength);
  strncpy(&Buffer[p + 0x0013 + EventTextLength], RECHeaderInfo->EventEventDescription, 273 - EventTextLength);

  //Extended Event Info
  p = 0x0168;
  EncodeExtInfo(Buffer, p, RECHeaderInfo, FALSE);

  //Transponder info
  p = 0x0574;
  Buffer[p + 0x0000] = RECHeaderInfo->TPSatIndex;

  Flags = (RECHeaderInfo->TPPilot      << 11) |
          (RECHeaderInfo->TPFEC        <<  7) |
          (RECHeaderInfo->TPModulation <<  5) |
          (RECHeaderInfo->TPSystem     <<  4) |
          (RECHeaderInfo->TPMode       <<  1) |
           RECHeaderInfo->TPPolarization;
  setWord(&Buffer[p + 0x0001], Flags, FALSE);

  Buffer[p + 0x0003] = RECHeaderInfo->TPUnknown2;

  setDword(&Buffer[p + 0x0004], RECHeaderInfo->TPFrequency, FALSE);
  setWord(&Buffer[p + 0x0008], RECHeaderInfo->TPSymbolRate, FALSE);
  setWord(&Buffer[p + 0x000a], RECHeaderInfo->TPTSID, FALSE);
  setWord(&Buffer[p + 0x000c], RECHeaderInfo->TPNetworkID, FALSE);
  setWord(&Buffer[p + 0x000e], RECHeaderInfo->TPOriginalNetworkID, FALSE);

  //Crypt Info: see header flags

  //Bookmarks
  p = 0x0584;
  setDword(&Buffer[p + 0x0000], RECHeaderInfo->NrBookmarks, FALSE);
  memcpy(&Buffer[p + 0x0004], RECHeaderInfo->Bookmark, 177 * sizeof(dword));
  setDword(&Buffer[p + 0x02c8], RECHeaderInfo->Resume, FALSE);

  TRACEEXIT;
}

void HDD_EncodeRECHeader_ST_TMST(byte *Buffer, tRECHeaderInfo *RECHeaderInfo)
{
  TRACEENTER;

  dword                 p;
  word                  Flags;
  byte                  EventTextLength;

  //Header
  p = 0;
  Buffer[p + 0x0000] = 0x54;
  Buffer[p + 0x0001] = 0x46;
  Buffer[p + 0x0002] = 0x72;
  Buffer[p + 0x0003] = 0x63;

  Buffer[p + 0x0004] = 0x00;
  Buffer[p + 0x0005] = 0x80;

  memcpy(&Buffer[p + 6], RECHeaderInfo->HeaderUnknown2, 2);
  setDword(&Buffer[p + 0x0008], RECHeaderInfo->HeaderStartTime, FALSE);
  setWord(&Buffer[p + 0x000c], RECHeaderInfo->HeaderDuration, FALSE);
  setWord(&Buffer[p + 0x000e], RECHeaderInfo->HeaderDurationSec, FALSE);
  Buffer[p + 0x0010] = (RECHeaderInfo->HeaderFlags & 0xfc) | (RECHeaderInfo->CryptFlag & 0x03);
  Buffer[p + 0x0011] = (RECHeaderInfo->HeaderFlags2 & 0x3f) | (RECHeaderInfo->HeaderCopyFlag ? 0x80 : 0x00) | (RECHeaderInfo->HeaderTSFlag ? 0x40 : 0x00);
  memcpy(&Buffer[p + 0x0012], RECHeaderInfo->HeaderUnknown4, 10);

  //Service Info
  p = 0x001c;
  Buffer[p + 0x0000] = RECHeaderInfo->SISatIndex;
  Buffer[p + 0x0001] = RECHeaderInfo->SIServiceType;

  Flags = (RECHeaderInfo->SISkipFlag << 15) |
          (RECHeaderInfo->SILockFlag << 14) |
          (RECHeaderInfo->SICASFlag << 13) |
          (RECHeaderInfo->SIDelFlag << 12) |
          (RECHeaderInfo->SITunerNum << 10) |
          RECHeaderInfo->SITPIdx;
  setWord(&Buffer[p +0x0002], Flags, FALSE);

  setWord(&Buffer[p + 0x0004], RECHeaderInfo->SIServiceID, FALSE);
  setWord(&Buffer[p + 0x0006], RECHeaderInfo->SIPMTPID, FALSE);
  setWord(&Buffer[p + 0x0008], RECHeaderInfo->SIPCRPID, FALSE);
  setWord(&Buffer[p + 0x000a], RECHeaderInfo->SIVideoPID, FALSE);
  setWord(&Buffer[p + 0x000c], RECHeaderInfo->SIAudioPID, FALSE);

  strncpy(&Buffer[p + 0x000e], RECHeaderInfo->SISvcName, 24);

  Buffer[p + 0x0026] = RECHeaderInfo->SIVideoStreamType;
  Buffer[p + 0x0027] = RECHeaderInfo->SIAudioStreamType;

  //Event Info
  p = 0x0044;
  memcpy(&Buffer[p], RECHeaderInfo->EventUnknown1, 2);
  Buffer[p + 0x0003] = (int)(RECHeaderInfo->EventDuration / 60);
  Buffer[p + 0x0002] = RECHeaderInfo->EventDuration % 60;
  setDword(&Buffer[p + 0x0004], RECHeaderInfo->EventEventID, FALSE);
  setDword(&Buffer[p + 0x0008], RECHeaderInfo->EventStartTime, FALSE);
  setDword(&Buffer[p + 0x000c], RECHeaderInfo->EventEndTime, FALSE);
  Buffer[p + 0x0010] = RECHeaderInfo->EventRunningStatus;
  EventTextLength = strlen(RECHeaderInfo->EventEventName);
  Buffer[p + 0x0011] = EventTextLength;
  Buffer[p + 0x0012] = RECHeaderInfo->EventParentalRate;
  strncpy(&Buffer[p + 0x0013], RECHeaderInfo->EventEventName, EventTextLength);
  strncpy(&Buffer[p + 0x0013 + EventTextLength], RECHeaderInfo->EventEventDescription, 273 - EventTextLength);

  //Extended Event Info
  p = 0x0168;
  EncodeExtInfo(Buffer, p, RECHeaderInfo, FALSE);

  //Transponder info
  p = 0x0574;
  Buffer[p + 0x0000] = RECHeaderInfo->TPSatIndex;
  Buffer[p + 0x0001] = RECHeaderInfo->TPChannelNumber;
  Buffer[p + 0x0002] = RECHeaderInfo->TPBandwidth;
  Buffer[p + 0x0003] = RECHeaderInfo->TPUnknown2;
  setDword(&Buffer[p + 0x0004], RECHeaderInfo->TPFrequency, FALSE);
  setWord(&Buffer[p + 0x0008], RECHeaderInfo->TPTSID, FALSE);
  Buffer[p + 0x000a] = RECHeaderInfo->TPLPHPStream;
  Buffer[p + 0x000b] = RECHeaderInfo->TPUnknown4;
  setWord(&Buffer[p + 0x000c], RECHeaderInfo->TPOriginalNetworkID, FALSE);
  setWord(&Buffer[p + 0x000e], RECHeaderInfo->TPNetworkID, FALSE);

  //Crypt Info: see header flags

  //Bookmarks
  p = 0x0584;
  setDword(&Buffer[p + 0x0000], RECHeaderInfo->NrBookmarks, FALSE);
  memcpy(&Buffer[p + 0x0004], RECHeaderInfo->Bookmark, 177 * sizeof(dword));
  setDword(&Buffer[p + 0x02c8], RECHeaderInfo->Resume, FALSE);

  TRACEEXIT;
}

void HDD_EncodeRECHeader_ST_TMSC(byte *Buffer, tRECHeaderInfo *RECHeaderInfo)
{
  TRACEENTER;

  dword                 p;
  word                  Flags;
  byte                  EventTextLength;

  //Header
  p = 0;
  Buffer[p + 0x0000] = 0x54;
  Buffer[p + 0x0001] = 0x46;
  Buffer[p + 0x0002] = 0x72;
  Buffer[p + 0x0003] = 0x63;

  Buffer[p + 0x0004] = 0x00;
  Buffer[p + 0x0005] = 0x80;

  memcpy(&Buffer[p + 6], RECHeaderInfo->HeaderUnknown2, 2);
  setDword(&Buffer[p + 0x0008], RECHeaderInfo->HeaderStartTime, FALSE);
  setWord(&Buffer[p + 0x000c], RECHeaderInfo->HeaderDuration, FALSE);
  setWord(&Buffer[p + 0x000e], RECHeaderInfo->HeaderDurationSec, FALSE);
  Buffer[p + 0x0010] = (RECHeaderInfo->HeaderFlags & 0xfc) | (RECHeaderInfo->CryptFlag & 0x03);
  Buffer[p + 0x0011] = (RECHeaderInfo->HeaderFlags2 & 0x3f) | (RECHeaderInfo->HeaderCopyFlag ? 0x80 : 0x00) | (RECHeaderInfo->HeaderTSFlag ? 0x40 : 0x00);
  memcpy(&Buffer[p + 0x0012], RECHeaderInfo->HeaderUnknown4, 10);

  //Service Info
  p = 0x001c;
  Buffer[p + 0x0000] = RECHeaderInfo->SISatIndex;
  Buffer[p + 0x0001] = RECHeaderInfo->SIServiceType;

  Flags = (RECHeaderInfo->SISkipFlag << 15) |
          (RECHeaderInfo->SILockFlag << 14) |
          (RECHeaderInfo->SICASFlag << 13) |
          (RECHeaderInfo->SIDelFlag << 12) |
          (RECHeaderInfo->SITunerNum << 10) |
          RECHeaderInfo->SITPIdx;
  setWord(&Buffer[p +0x0002], Flags, FALSE);

  setWord(&Buffer[p + 0x0004], RECHeaderInfo->SIServiceID, FALSE);
  setWord(&Buffer[p + 0x0006], RECHeaderInfo->SIPMTPID, FALSE);
  setWord(&Buffer[p + 0x0008], RECHeaderInfo->SIPCRPID, FALSE);
  setWord(&Buffer[p + 0x000a], RECHeaderInfo->SIVideoPID, FALSE);
  setWord(&Buffer[p + 0x000c], RECHeaderInfo->SIAudioPID, FALSE);

  strncpy(&Buffer[p + 0x000e], RECHeaderInfo->SISvcName, 24);

  Buffer[p + 0x0026] = RECHeaderInfo->SIVideoStreamType;
  Buffer[p + 0x0027] = RECHeaderInfo->SIAudioStreamType;

  //Event Info
  p = 0x0044;
  memcpy(&Buffer[p], RECHeaderInfo->EventUnknown1, 2);
  Buffer[p + 0x0003] = (int)(RECHeaderInfo->EventDuration / 60);
  Buffer[p + 0x0002] = RECHeaderInfo->EventDuration % 60;
  setDword(&Buffer[p + 0x0004], RECHeaderInfo->EventEventID, FALSE);
  setDword(&Buffer[p + 0x0008], RECHeaderInfo->EventStartTime, FALSE);
  setDword(&Buffer[p + 0x000c], RECHeaderInfo->EventEndTime, FALSE);
  Buffer[p + 0x0010] = RECHeaderInfo->EventRunningStatus;
  EventTextLength = strlen(RECHeaderInfo->EventEventName);
  Buffer[p + 0x0011] = EventTextLength;
  Buffer[p + 0x0012] = RECHeaderInfo->EventParentalRate;
  strncpy(&Buffer[p + 0x0013], RECHeaderInfo->EventEventName, EventTextLength);
  strncpy(&Buffer[p + 0x0013 + EventTextLength], RECHeaderInfo->EventEventDescription, 273 - EventTextLength);

  //Extended Event Info
  p = 0x0168;
  EncodeExtInfo(Buffer, p, RECHeaderInfo, FALSE);

   //Transponder info
  p = 0x0574;
  setDword(&Buffer[p + 0x0000], RECHeaderInfo->TPFrequency << 8, FALSE);
  setWord(&Buffer[p + 0x0004], RECHeaderInfo->TPSymbolRate, FALSE);
  setWord(&Buffer[p + 0x0006], RECHeaderInfo->TPTSID, FALSE);
  setWord(&Buffer[p + 0x0008], RECHeaderInfo->TPOriginalNetworkID, FALSE);
  Buffer[p + 0x000a] = RECHeaderInfo->TPModulation;
  Buffer[p + 0x000b] = RECHeaderInfo->TPUnknown6;

  //Crypt Info: see header flags

  //Bookmarks
  p = 0x0580;
  setDword(&Buffer[p + 0x0000], RECHeaderInfo->NrBookmarks, FALSE);
  memcpy(&Buffer[p + 0x0004], RECHeaderInfo->Bookmark, 177 * sizeof(dword));
  setDword(&Buffer[p + 0x02c8], RECHeaderInfo->Resume, FALSE);

  TRACEEXIT;
}

void HDD_EncodeRECHeader_ST_TF7k7HDPVR(byte *Buffer, tRECHeaderInfo *RECHeaderInfo)
{
  TRACEENTER;

  dword                 p;
  word                  w;
  byte                  EventTextLength;

  //Header
  p = 0x4d0;
  Buffer[p + 0x0000] = 0x54;
  Buffer[p + 0x0001] = 0x46;
  Buffer[p + 0x0002] = 0x72;
  Buffer[p + 0x0003] = 0x63;

  Buffer[p + 0x0004] = 0x50;
  Buffer[p + 0x0005] = 0x00;

  memcpy(&Buffer[p + 0x0006], RECHeaderInfo->HeaderUnknown2, 2);
  setWord(&Buffer[p + 0x0008], RECHeaderInfo->HeaderDuration, FALSE);
  setWord(&Buffer[p + 0x000a], RECHeaderInfo->HeaderSvcNumber, FALSE);
  setWord(&Buffer[p + 0x000c], RECHeaderInfo->HeaderSvcType, FALSE);

  //Service Info
  p = 0x04de;
  Buffer[p + 0x0000] = RECHeaderInfo->SISatIndex;
  Buffer[p + 0x0001] = RECHeaderInfo->SIServiceType;

  w =  RECHeaderInfo->SITPIdx |
      (RECHeaderInfo->SITunerNum << 10) |
      (RECHeaderInfo->SISkipFlag << 12) |
      (RECHeaderInfo->SILockFlag << 13) |
      (RECHeaderInfo->SICASFlag << 14) |
      (RECHeaderInfo->SIDelFlag << 15);
  setWord(&Buffer[p + 0x0002], w, FALSE);

  setWord(&Buffer[p + 0x0004], RECHeaderInfo->SIServiceID, FALSE);
  setWord(&Buffer[p + 0x0006], RECHeaderInfo->SIPMTPID, FALSE);
  setWord(&Buffer[p + 0x0008], RECHeaderInfo->SIPCRPID, FALSE);
  setWord(&Buffer[p + 0x000a], RECHeaderInfo->SIVideoPID, FALSE);
  setWord(&Buffer[p + 0x000c], RECHeaderInfo->SIAudioPID, FALSE);
  strncpy(&Buffer[p + 0x000e], RECHeaderInfo->SISvcName, 28);

  //Transponder Info
  p = 0x0508;
  Buffer[p + 0x0000] = RECHeaderInfo->TPSatIndex;
  Buffer[p + 0x0001] = RECHeaderInfo->TPFlags2 | RECHeaderInfo->TPPolarization | (RECHeaderInfo->TPMode << 1);

  memcpy(&Buffer[p + 0x0002], RECHeaderInfo->TPUnknown3, 2);
  setDword(&Buffer[p + 0x0004], RECHeaderInfo->TPFrequency, FALSE);
  setWord(&Buffer[p +  0x0008], RECHeaderInfo->TPSymbolRate, FALSE);
  setWord(&Buffer[p + 0x000a], RECHeaderInfo->TPTSID, FALSE);
  memcpy(&Buffer[p + 0x000c], RECHeaderInfo->TPUnknown5, 2);
  setWord(&Buffer[p + 0x000e], RECHeaderInfo->TPOriginalNetworkID, FALSE);

  //Event Info
  p = 0x0518;
  memcpy(&Buffer[p], RECHeaderInfo->EventUnknown1, 2);
  Buffer[p + 0x0003] = (int)(RECHeaderInfo->EventDuration / 60);
  Buffer[p + 0x0002] = RECHeaderInfo->EventDuration % 60;
  setDword(&Buffer[p + 0x0004], RECHeaderInfo->EventEventID, FALSE);
  setDword(&Buffer[p + 0x0008], RECHeaderInfo->EventStartTime, FALSE);
  setDword(&Buffer[p + 0x000c], RECHeaderInfo->EventEndTime, FALSE);
  Buffer[p + 0x0010] = RECHeaderInfo->EventRunningStatus;
  EventTextLength = strlen(RECHeaderInfo->EventEventName);
  Buffer[p + 0x0011] = EventTextLength;
  Buffer[p + 0x0012] = RECHeaderInfo->EventParentalRate;
  strncpy(&Buffer[p + 0x0013], RECHeaderInfo->EventEventName, EventTextLength);
  strncpy(&Buffer[p + 0x0013 + EventTextLength], RECHeaderInfo->EventEventDescription, 257 - EventTextLength);
  setWord(&Buffer[p + 0x0114], RECHeaderInfo->EventServiceID, FALSE);
  memcpy(&Buffer[p + 0x0116], RECHeaderInfo->EventUnknown2, 14);

  //Extended Event Info
  p = 0x063c;
  EncodeExtInfo(Buffer, p, RECHeaderInfo, FALSE);

  //Crypt Info
  p = 0x0a48;
  Buffer[p + 0x0000] = RECHeaderInfo->CryptFlag;
  memcpy(&Buffer[p + 0x0001], RECHeaderInfo->CryptUnknown2, 3);

  //Bookmarks
  p = 0x0a4c;
  memcpy(&Buffer[p + 0x0000], RECHeaderInfo->Bookmark, 64 * sizeof(dword));
  setDword(&Buffer[p + 0x0100], RECHeaderInfo->Resume, FALSE);

  TRACEEXIT;
}

bool HDD_EncodeRECHeader(byte *Buffer, tRECHeaderInfo *RECHeaderInfo, SYSTEM_TYPE SystemType)
{
  TRACEENTER;

  bool ret;

  if(SystemType == ST_UNKNOWN) SystemType = GetSystemType();

  memset(Buffer, 0, 8192);
  ret = TRUE;
  switch(SystemType)
  {
    case ST_UNKNOWN:    ret = FALSE; break;
    case ST_S:          HDD_EncodeRECHeader_ST_S(Buffer, RECHeaderInfo); break;
    case ST_T:          HDD_EncodeRECHeader_ST_T(Buffer, RECHeaderInfo); break;
    case ST_C:          HDD_EncodeRECHeader_ST_C(Buffer, RECHeaderInfo); break;
    case ST_T5700:      HDD_EncodeRECHeader_ST_T5700(Buffer, RECHeaderInfo); break;
    case ST_TMSS:       HDD_EncodeRECHeader_ST_TMSS(Buffer, RECHeaderInfo); break;
    case ST_TMST:       HDD_EncodeRECHeader_ST_TMST(Buffer, RECHeaderInfo); break;
    case ST_TMSC:       HDD_EncodeRECHeader_ST_TMSC(Buffer, RECHeaderInfo); break;
    case ST_T5800:      HDD_EncodeRECHeader_ST_T5800(Buffer, RECHeaderInfo); break;
    case ST_ST:         ret = FALSE; break;
    case ST_CT:         ret = FALSE; break;
    case ST_TF7k7HDPVR: HDD_EncodeRECHeader_ST_TF7k7HDPVR(Buffer, RECHeaderInfo); break;
    case ST_NRTYPES:    ret = FALSE; break;
  }

  TRACEEXIT;
  return ret;
}
