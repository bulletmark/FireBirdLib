#ifndef FBLIB_EPG_H
#define FBLIB_EPG_H

  #include "../libFireBird.h"
  #include "../time/FBLib_time.h"

  #define MAXEPGRECORDS   10000

  typedef struct
  {
    bool                  TimeFilter;
    dword                 StartTime;
    dword                 EndTime;

    bool                  ChannelFilter;
    word                  NetworkID;
    word                  TSID;
    word                  ServiceID;
    byte                  SatIndex;
    bool                  StartCurrent;

    bool                  DurationFilter;
    word                  MinDuration;
    word                  MaxDuration;

    bool                  GenreFilter;
    byte                 *GenreArray;
    byte                  GenreArraySize;

    bool                  UseCallback;
    void                 *Callback;
  } tEPGFilter;

  typedef struct
  {
    dword              *Next;
    dword              *Prev;
  } tTreeEntry;

  typedef struct
  {
    dword               DataStatus:2;       //0000: ex unknown1d; 0=invalid, 1=data taken from _EIT_AIR.DAT, 2=data taken from OTA
    dword               RunningStatus:3;
    dword               unknown1e:7;        //      always 0
    dword               durationMin:8;
    dword               durationHour:8;
    dword               unknown1a:4;        //      always 0. Possibly unused

    dword               EventID;            //0004
    dword               StartTime;          //0008
    dword               EndTime;            //000c
    byte                NameLength;         //0010
    byte                ParentalRate;       //0011
    word                NetworkID;          //0012
    word                TSID;               //0014
    word                ServiceID;          //0016
    word                SatIndex;           //0018
    byte                unknown6;           //001a: 0 or 0x67 if lang is set
    byte                lang[3];            //001b
    word                unknown7;           //001e: always 0
    tTreeEntry          TreeByHash;         //0020:
    tTreeEntry          TreeFull;           //0028:
    char               *ShortEventText;     //0030
    char               *ExtEventText;       //0034
    byte                unknown10;          //0038: always 0; accessed as byte
    byte                unknown10a;         //0039: possibly a alignment filler
    word                ExtEventTextLength; //003a

    //dword               unknown11;        //003c: addressed as dword by the firmware, not word, and therefore includes unknown12
    dword               unknown11a:8;
    dword               unknown11b:2;       //Ext Event Text available
    dword               unknown11c:1;
    dword               unknown11d:4;       //=unknown11a-1?
    dword               unknown11e:1;
    dword               unknown11f:16;      //possibly unused bits

    dword               citID;              //0040: ex unknown13; an ID of the _citInfo table. The same ID is available in TYPE_Timer_TMSS.unknown1
    //68 Bytes

    byte                ContentIdentifier;  //0044: Content_nibble_level_2 / Content_nibble_level_1
    byte                sourceFlag;         //0045: 0 = FTA, 1 - ICE
    word                unknown14;          //0046
    word                iceChannel;         //0048
    //72 Bytes

    byte                unknown15[6];       //004a
    //80 Bytes
  } TYPE_EvtInfo;

  extern int              EPGInfoCacheEntries;
  extern int              EPGInfoNrEntries;
  extern int              EPGInfoCurrentEntry;
  extern int              EPGInfoCacheFile;
  extern dword            EPGInfoCacheSize;
  extern byte            *EPGInfoCacheMap;
  extern TYPE_EPGInfo    *EPGInfoCache;
  extern tEPGFilter       EPGFilter;
  extern bool             EPGInfoReverseOrder;
  extern dword            EPGInfoStructSize;
  extern char             EPGCacheFile[40];
  extern int              EPGAbortLoad;

  bool  EPGInfo_CreateCache(int NrRecords);
  void  EPGInfo_CloneToCache(dword *TreePointer, byte StructOffset, tEPGFilter *EPGFilter);
  void  EPGInfo_DestroyCache(void);
  dword EPGInfo_CountEvents(dword *TreePointer);
  dword EPGInfo_CalculateStructSize(void);
  void  EPGInfo_CopyData(TYPE_EvtInfo *EvtInfo, TYPE_EPGInfo *EPGInfo, dword EventStartTime, dword EventEndTime, short Offset);

#endif
