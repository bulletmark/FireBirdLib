#include <string.h>
#include "FBLib_rec.h"

word getWord(void *buffer, bool NeedsByteSwapping)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("getWord");
  #endif

  word                  w;
  byte                 *p;

  p = (byte*)buffer;
  if(NeedsByteSwapping)
    w = (p[1] | (p[0] << 8));
  else
    w = (p[0] | (p[1] << 8));

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return w;
}

dword getDword(void *buffer, bool NeedsByteSwapping)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("getDword");
  #endif

  dword                 d;
  byte                 *p;

  p = (byte*)buffer;
  if(NeedsByteSwapping)
    d = (p[3] | (p[2] << 8) | (p[1] << 16) | (p[0] << 24));
  else
    d = (p[0] | (p[1] << 8) | (p[2] << 16) | (p[3] << 24));

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return d;
}

bool                    WrongEndian = FALSE;

void HDD_DecodeRECHeader_ST_S(byte *Buffer, tRECHeaderInfo *RECHeaderInfo)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_DecodeRECHeader_ST_S");
  #endif

  dword                 p;
  word                  TPFlags1;
  byte                  EventTextLength;
  int                   i;

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
  RECHeaderInfo->ExtEventServiceID   = getWord(&Buffer[p + 0x0000], WrongEndian);
  RECHeaderInfo->ExtEventTextLength  = getWord(&Buffer[p + 0x0002], WrongEndian);
  RECHeaderInfo->ExtEventEventID     = getDword(&Buffer[p + 0x0004], WrongEndian);
  memcpy(RECHeaderInfo->ExtEventText, &Buffer[p + 0x0008], RECHeaderInfo->ExtEventTextLength);
  for(i = 0; i < RECHeaderInfo->ExtEventTextLength - 1; i++)
    if(RECHeaderInfo->ExtEventText[i] == '\0') RECHeaderInfo->ExtEventText[i] = ' ';
  StrReplace(RECHeaderInfo->ExtEventText, "\\n", "\x8a");


  //Crypt Info
  p = 0x0570;
  memcpy(RECHeaderInfo->CryptUnknown1, &Buffer[p], 4);
  RECHeaderInfo->CryptFlag = Buffer[p + 0x0004];
  memcpy(RECHeaderInfo->CryptUnknown2, &Buffer[p + 0x0005], 3);

  //Bookmarks
  p = 0x0578;
  memcpy(RECHeaderInfo->Bookmark, &Buffer[p + 0x0000], 64 * sizeof(dword));
  RECHeaderInfo->Resume = getDword(&Buffer[p + 0x0100], WrongEndian);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}

void HDD_DecodeRECHeader_ST_T(byte *Buffer, tRECHeaderInfo *RECHeaderInfo)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_DecodeRECHeader_ST_T");
  #endif

  dword                 p;
  byte                  EventTextLength;
  int                   i;

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
  RECHeaderInfo->ExtEventServiceID   = getWord(&Buffer[p + 0x0000], WrongEndian);
  RECHeaderInfo->ExtEventTextLength  = getWord(&Buffer[p + 0x0002], WrongEndian);
  RECHeaderInfo->ExtEventEventID     = getDword(&Buffer[p + 0x0004], WrongEndian);
  memcpy(RECHeaderInfo->ExtEventText, &Buffer[p + 0x0008], RECHeaderInfo->ExtEventTextLength);
  for(i = 0; i < RECHeaderInfo->ExtEventTextLength - 1; i++)
    if(RECHeaderInfo->ExtEventText[i] == '\0') RECHeaderInfo->ExtEventText[i] = ' ';
  StrReplace(RECHeaderInfo->ExtEventText, "\\n", "\x8a");

  //Crypt Info
  p = 0x0570;
  memcpy(RECHeaderInfo->CryptUnknown1, &Buffer[p], 4);
  RECHeaderInfo->CryptFlag = Buffer[p + 0x0004];
  memcpy(RECHeaderInfo->CryptUnknown2, &Buffer[p + 0x0005], 3);

  //Bookmarks
  p = 0x0578;
  memcpy(RECHeaderInfo->Bookmark, &Buffer[p + 0x0000], 64 * sizeof(dword));
  RECHeaderInfo->Resume = getDword(&Buffer[p + 0x0100], WrongEndian);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}

void HDD_DecodeRECHeader_ST_C(byte *Buffer, tRECHeaderInfo *RECHeaderInfo)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_DecodeRECHeader_ST_C");
  #endif

  dword                 p;
  byte                  EventTextLength;
  int                   i;

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
  RECHeaderInfo->ExtEventServiceID   = getWord(&Buffer[p + 0x0000], WrongEndian);
  RECHeaderInfo->ExtEventTextLength  = getWord(&Buffer[p + 0x0002], WrongEndian);
  RECHeaderInfo->ExtEventEventID     = getDword(&Buffer[p + 0x0004], WrongEndian);
  memcpy(RECHeaderInfo->ExtEventText, &Buffer[p + 0x0008], RECHeaderInfo->ExtEventTextLength);
  for(i = 0; i < RECHeaderInfo->ExtEventTextLength - 1; i++)
    if(RECHeaderInfo->ExtEventText[i] == '\0') RECHeaderInfo->ExtEventText[i] = ' ';
  StrReplace(RECHeaderInfo->ExtEventText, "\\n", "\x8a");

  //Crypt Info
  p = 0x056c;
  memcpy(RECHeaderInfo->CryptUnknown1, &Buffer[p], 4);
  RECHeaderInfo->CryptFlag = Buffer[p + 0x0004];
  memcpy(RECHeaderInfo->CryptUnknown2, &Buffer[p + 0x0005], 3);

  //Bookmarks
  p = 0x0574;
  memcpy(RECHeaderInfo->Bookmark, &Buffer[p + 0x0000], 64 * sizeof(dword));
  RECHeaderInfo->Resume = getDword(&Buffer[p + 0x0100], WrongEndian);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}

void HDD_DecodeRECHeader_ST_T5700(byte *Buffer, tRECHeaderInfo *RECHeaderInfo)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_DecodeRECHeader_ST_T5700");
  #endif

  dword                 p;
  byte                  EventTextLength;
  int                   i;

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
  RECHeaderInfo->ExtEventServiceID   = getWord(&Buffer[p + 0x0000], WrongEndian);
  RECHeaderInfo->ExtEventTextLength  = getWord(&Buffer[p + 0x0002], WrongEndian);
  RECHeaderInfo->ExtEventEventID     = getDword(&Buffer[p + 0x0004], WrongEndian);
  memcpy(RECHeaderInfo->ExtEventText, &Buffer[p + 0x0008], RECHeaderInfo->ExtEventTextLength);
  for(i = 0; i < RECHeaderInfo->ExtEventTextLength - 1; i++)
    if(RECHeaderInfo->ExtEventText[i] == '\0') RECHeaderInfo->ExtEventText[i] = ' ';
  StrReplace(RECHeaderInfo->ExtEventText, "\\n", "\x8a");

  //Crypt Info
  p = 0x0578;
  memcpy(RECHeaderInfo->CryptUnknown1, &Buffer[p], 4);
  RECHeaderInfo->CryptFlag = Buffer[p + 0x0004];
  memcpy(RECHeaderInfo->CryptUnknown2, &Buffer[p + 0x0005], 3);

  //Bookmarks
  p = 0x0580;
  memcpy(RECHeaderInfo->Bookmark, &Buffer[p + 0x0000], 64 * sizeof(dword));
  RECHeaderInfo->Resume = getDword(&Buffer[p + 0x0100], WrongEndian);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}

void HDD_DecodeRECHeader_ST_T5800(byte *Buffer, tRECHeaderInfo *RECHeaderInfo)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_DecodeRECHeader_ST_T5800");
  #endif

  dword                 p;
  byte                  EventTextLength;
  int                   i;

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
  RECHeaderInfo->ExtEventServiceID   = getWord(&Buffer[p + 0x0000], WrongEndian);
  RECHeaderInfo->ExtEventTextLength  = getWord(&Buffer[p + 0x0002], WrongEndian);
  RECHeaderInfo->ExtEventEventID     = getDword(&Buffer[p + 0x0004], WrongEndian);
  memcpy(RECHeaderInfo->ExtEventText, &Buffer[p + 0x0008], RECHeaderInfo->ExtEventTextLength);
  for(i = 0; i < RECHeaderInfo->ExtEventTextLength - 1; i++)
    if(RECHeaderInfo->ExtEventText[i] == '\0') RECHeaderInfo->ExtEventText[i] = ' ';
  StrReplace(RECHeaderInfo->ExtEventText, "\\n", "\x8a");

  //Crypt Info
  p = 0x0574;
  memcpy(RECHeaderInfo->CryptUnknown1, &Buffer[p], 4);
  RECHeaderInfo->CryptFlag = Buffer[p + 0x0004];
  memcpy(RECHeaderInfo->CryptUnknown2, &Buffer[p + 0x0005], 3);

  //Bookmarks
  p = 0x057c;
  memcpy(RECHeaderInfo->Bookmark, &Buffer[p + 0x0000], 64 * sizeof(dword));
  RECHeaderInfo->Resume = getDword(&Buffer[p + 0x0100], WrongEndian);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}

void HDD_DecodeRECHeader_ST_TMSS(byte *Buffer, tRECHeaderInfo *RECHeaderInfo)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_DecodeRECHeader_ST_TMSS");
  #endif

  dword                 p;
  word                  Flags;
  byte                  EventTextLength;
  int                   i;

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

  //Transponder info
  p = 0x0570;
  memcpy(RECHeaderInfo->TPUnknown1, &Buffer[p + 0], 4);
  RECHeaderInfo->TPSatIndex           = Buffer[p +  4];

  Flags                               = getWord(&Buffer[p +  5], WrongEndian);
  RECHeaderInfo->TPPolarization       =  Flags & 0x01;
  RECHeaderInfo->TPMode               = (Flags >>  1) & 0x07;
  RECHeaderInfo->TPSystem             = (Flags >>  4) & 0x01;
  RECHeaderInfo->TPModulation         = (Flags >>  5) & 0x03;
  RECHeaderInfo->TPFEC                = (Flags >>  7) & 0x0f;
  RECHeaderInfo->TPPilot              = (Flags >> 11) & 0x01;

  RECHeaderInfo->TPUnknown2           = Buffer[p + 7];
  RECHeaderInfo->TPFrequency          = getDword(&Buffer[p +  8], WrongEndian);
  RECHeaderInfo->TPSymbolRate         = getWord(&Buffer [p + 12], WrongEndian);
  RECHeaderInfo->TPTSID               = getWord(&Buffer [p + 14], WrongEndian);

  RECHeaderInfo->TPFlags2             = getWord(&Buffer [p + 16], WrongEndian);
  RECHeaderInfo->TPClockSync          = RECHeaderInfo->TPFlags2 & 0x0001;
  RECHeaderInfo->TPFlags2             = RECHeaderInfo->TPFlags2 & 0xfffe;

  RECHeaderInfo->TPOriginalNetworkID  = getWord(&Buffer[p + 18], WrongEndian);

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
  RECHeaderInfo->ExtEventServiceID   = getWord(&Buffer[p + 0x0000], WrongEndian);
  RECHeaderInfo->ExtEventTextLength  = getWord(&Buffer[p + 0x0002], WrongEndian);
  RECHeaderInfo->ExtEventEventID     = getDword(&Buffer[p + 0x0004], WrongEndian);

  if(RECHeaderInfo->ExtEventTextLength > 1024)
  {
    RECHeaderInfo->ExtEventTextLength = strlen(&Buffer[p + 0x0008]);
    if(RECHeaderInfo->ExtEventTextLength > 1024) RECHeaderInfo->ExtEventTextLength = 1024;
  }
  memcpy(RECHeaderInfo->ExtEventText, &Buffer[p + 0x0008], RECHeaderInfo->ExtEventTextLength);
  for(i = 0; i < RECHeaderInfo->ExtEventTextLength - 1; i++)
    if(RECHeaderInfo->ExtEventText[i] == '\0') RECHeaderInfo->ExtEventText[i] = ' ';
  StrReplace(RECHeaderInfo->ExtEventText, "\\n", "\x8a");

  //Crypt Info: see header flags

  //Bookmarks
  p = 0x0584;
  RECHeaderInfo->NrBookmarks = getDword(&Buffer[p + 0x0000], WrongEndian);
  memcpy(RECHeaderInfo->Bookmark, &Buffer[p + 0x0004], 177 * sizeof(dword));
  RECHeaderInfo->Resume = getDword(&Buffer[p + 0x02c8], WrongEndian);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}

void HDD_DecodeRECHeader_ST_TMST(byte *Buffer, tRECHeaderInfo *RECHeaderInfo)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_DecodeRECHeader_ST_TMST");
  #endif

  dword                 p;
  word                  Flags;
  byte                  EventTextLength;
  int                   i;

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
  RECHeaderInfo->ExtEventServiceID   = getWord(&Buffer[p + 0x0000], WrongEndian);
  RECHeaderInfo->ExtEventTextLength  = getWord(&Buffer[p + 0x0002], WrongEndian);
  RECHeaderInfo->ExtEventEventID     = getDword(&Buffer[p + 0x0004], WrongEndian);
  memcpy(RECHeaderInfo->ExtEventText, &Buffer[p + 0x0008], RECHeaderInfo->ExtEventTextLength);
  for(i = 0; i < RECHeaderInfo->ExtEventTextLength - 1; i++)
    if(RECHeaderInfo->ExtEventText[i] == '\0') RECHeaderInfo->ExtEventText[i] = ' ';
  StrReplace(RECHeaderInfo->ExtEventText, "\\n", "\x8a");

  //Transponder info
  p = 0x0570;
  memcpy(RECHeaderInfo->TPUnknown1, &Buffer[p + 0x0000], 4);
  RECHeaderInfo->TPSatIndex      = Buffer[p + 0x0004];
  RECHeaderInfo->TPChannelNumber = Buffer[p + 0x0005];
  RECHeaderInfo->TPBandwidth     = Buffer[p + 0x0006];
  RECHeaderInfo->TPUnknown2      = Buffer[p + 0x0007];
  RECHeaderInfo->TPFrequency     = getDword(&Buffer[p + 0x0008], WrongEndian);
  RECHeaderInfo->TPTSID          = getWord(&Buffer[p + 0x000c], WrongEndian);
  RECHeaderInfo->TPLPHPStream    = Buffer[p + 0x000e];
  RECHeaderInfo->TPUnknown4      = Buffer[p + 0x000f];
  RECHeaderInfo->TPOriginalNetworkID  = getWord(&Buffer[p + 0x0010], WrongEndian);
  RECHeaderInfo->TPNetworkID     = getWord(&Buffer[p + 0x0012], WrongEndian);

  //Crypt Info: see header

  //Bookmarks
  p = 0x0584;
  RECHeaderInfo->NrBookmarks = getDword(&Buffer[p + 0x0000], WrongEndian);
  memcpy(RECHeaderInfo->Bookmark, &Buffer[p + 0x0004], 177 * sizeof(dword));
  RECHeaderInfo->Resume = getDword(&Buffer[p + 0x02c8], WrongEndian);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}

void HDD_DecodeRECHeader_ST_TMSC(byte *Buffer, tRECHeaderInfo *RECHeaderInfo)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_DecodeRECHeader_ST_TMSC");
  #endif

  dword                 p;
  word                  Flags;
  byte                  EventTextLength;
  int                   i;

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
  RECHeaderInfo->ExtEventServiceID   = getWord(&Buffer[p + 0x0000], WrongEndian);
  RECHeaderInfo->ExtEventTextLength  = getWord(&Buffer[p + 0x0002], WrongEndian);
  RECHeaderInfo->ExtEventEventID     = getDword(&Buffer[p + 0x0004], WrongEndian);
  memcpy(RECHeaderInfo->ExtEventText, &Buffer[p + 0x0008], RECHeaderInfo->ExtEventTextLength);
  for(i = 0; i < RECHeaderInfo->ExtEventTextLength - 1; i++)
    if(RECHeaderInfo->ExtEventText[i] == '\0') RECHeaderInfo->ExtEventText[i] = ' ';
  StrReplace(RECHeaderInfo->ExtEventText, "\\n", "\x8a");

  //Transponder info
  p = 0x0570;
  memcpy(RECHeaderInfo->TPUnknown1, &Buffer[p + 0x0000], 4);
  RECHeaderInfo->TPFrequency          = getDword(&Buffer[p + 0x0004], WrongEndian) >> 8;
  RECHeaderInfo->TPSymbolRate         = getWord(&Buffer[p + 0x0008], WrongEndian);
  RECHeaderInfo->TPTSID               = getWord(&Buffer[p + 0x000a], WrongEndian);
  RECHeaderInfo->TPOriginalNetworkID  = getWord(&Buffer[p + 0x000c], WrongEndian);
  RECHeaderInfo->TPModulation         = Buffer[p + 0x000e];
  RECHeaderInfo->TPUnknown6           = Buffer[p + 0x000f];

  //Crypt Info: see header flags

  //Bookmarks
  p = 0x0580;
  RECHeaderInfo->NrBookmarks = getDword(&Buffer[p + 0x0000], WrongEndian);
  memcpy(RECHeaderInfo->Bookmark, &Buffer[p + 0x0004], 177 * sizeof(dword));
  RECHeaderInfo->Resume = getDword(&Buffer[p + 0x02c8], WrongEndian);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}

void HDD_DecodeRECHeader_ST_TF7k7HDPVR(byte *Buffer, tRECHeaderInfo *RECHeaderInfo)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_DecodeRECHeader_ST_TF7k7HDPVR");
  #endif

  dword                 p;
  word                  TPFlags1;
  byte                  EventTextLength;
  int                   i;

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
  RECHeaderInfo->ExtEventServiceID   = getWord(&Buffer[p + 0x0000], WrongEndian);
  RECHeaderInfo->ExtEventTextLength  = getWord(&Buffer[p + 0x0002], WrongEndian);
  RECHeaderInfo->ExtEventEventID     = getDword(&Buffer[p + 0x0004], WrongEndian);
  memcpy(RECHeaderInfo->ExtEventText, &Buffer[p + 0x0008], RECHeaderInfo->ExtEventTextLength);
  for(i = 0; i < RECHeaderInfo->ExtEventTextLength - 1; i++)
    if(RECHeaderInfo->ExtEventText[i] == '\0') RECHeaderInfo->ExtEventText[i] = ' ';
  StrReplace(RECHeaderInfo->ExtEventText, "\\n", "\x8a");

  //Crypt Info
  p = 0x0a44;
  memcpy(RECHeaderInfo->CryptUnknown1, &Buffer[p], 4);
  RECHeaderInfo->CryptFlag = Buffer[p + 0x0004];
  memcpy(RECHeaderInfo->CryptUnknown2, &Buffer[p + 0x0005], 3);

  //Bookmarks
  p = 0x0a4c;
  memcpy(RECHeaderInfo->Bookmark, &Buffer[p + 0x0000], 64 * sizeof(dword));
  RECHeaderInfo->Resume = getDword(&Buffer[p + 0x0100], WrongEndian);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}


bool HDD_DecodeRECHeader(byte *Buffer, tRECHeaderInfo *RECHeaderInfo, SYSTEM_TYPE SystemType)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_DecodeRECHeader");
  #endif

  bool ret;

  if(SystemType == ST_UNKNOWN) SystemType = GetSystemType();

  memset(RECHeaderInfo, 0, sizeof(tRECHeaderInfo));

  //Is this a REC header?
  RECHeaderInfo->HeaderMagic     = (Buffer[0] << 24) | (Buffer[1] << 16) | (Buffer[2] << 8) | Buffer[3];
  if(RECHeaderInfo->HeaderMagic != 0x54467263)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

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

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
