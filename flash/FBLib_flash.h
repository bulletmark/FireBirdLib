#ifndef FBLIB_FLASH_H
#define FBLIB_FLASH_H

  #include "../libFireBird.h"

  #define TIMER_NAME    "FireBirdLib.rec"
  #define TIMER_DATE    0xffff0000          //22.04.2038 00:00
  #define MAXFAVS       30
  #define MAXSAT        255

  typedef struct
  {
    byte                SatIdx;
    byte                VideoStreamType;

    word                TPIdx:10;
    word                TunerNum:2;
    word                SkipFlag:1;
    word                LockFlag:1;
    word                CASFlag:1;
    word                DelFlag:1;

    word                SVCID;
    word                PMTPID;
    word                PCRPID;
    word                VideoPID;
    word                AudioPID;
    word                unknown1;
    dword               NameOffset;
    word                ProviderIdx;
    word                LCN;
    byte                unknown2[6];
    word                AudioStreamType;
  }TYPE_Service_TMSS;

  #define TYPE_Service_TMST   TYPE_Service_TMSS
  #define TYPE_Service_TMSC   TYPE_Service_TMSS

  bool FlashServiceDecode(void *Data, tFlashService *Service);
  bool FlashServiceDecode_ST_TMSC(TYPE_Service_TMSC *Data, tFlashService *Service);
  bool FlashServiceDecode_ST_TMSS(TYPE_Service_TMSS *Data, tFlashService *Service);
  bool FlashServiceDecode_ST_TMST(TYPE_Service_TMST *Data, tFlashService *Service);
  bool FlashServiceDelete(void *Data);
  bool FlashServiceDelServiceName(int SvcType, int SvcNum);
  bool FlashServiceDelete_ST_TMSC(TYPE_Service_TMSC *Data);
  bool FlashServiceDelete_ST_TMSS(TYPE_Service_TMSS *Data);
  bool FlashServiceDelete_ST_TMST(TYPE_Service_TMST *Data);
  bool FlashServiceEncode(void *Data, tFlashService *Service);
  bool FlashServiceEncode_ST_TMSC(TYPE_Service_TMSC *Data, tFlashService *Service);
  bool FlashServiceEncode_ST_TMSS(TYPE_Service_TMSS *Data, tFlashService *Service);
  bool FlashServiceEncode_ST_TMST(TYPE_Service_TMST *Data, tFlashService *Service);

  typedef struct
  {
    byte                  LNBSupply:1;
    byte                  unused1:1;
    byte                  DiSEqC10:3;
    byte                  unused2:3;

    byte                  DiSEqC12;

    word                  UniversalLNB:1;
    word                  Switch22:1;
    word                  LowBand:14;

    word                  HBFrq;
    byte                  DiSEqC12Flags[3];

    byte                  unused3:6;
    byte                  LoopThrough:1;
    byte                  unused4:1;

    byte                  DiSEqC11;
    byte                  unused5[5];
  } TYPE_LNB_TMSS;

  typedef struct
  {
    word                  NrOfTransponders;
    word                  unused1;
    char                  SatName[16];
    TYPE_LNB_TMSS         LNB[2];
    byte                  unknown1[22];
    word                  SatPosition;
    byte                  unused2[8];
  } TYPE_SatInfo_TMSS;

  typedef struct
  {
    word                  NrOfTransponders;
    char                  SatName[16];      //Contains DVBT
  } TYPE_SatInfo_TMST;

  typedef struct
  {
    word                  NrOfTransponders;
  } TYPE_SatInfo_TMSC;

  bool FlashSatTablesDecode_ST_TMSS(TYPE_SatInfo_TMSS *Data, tFlashSatTable *SatTable);
  bool FlashSatTablesDecode_ST_TMST(TYPE_SatInfo_TMST *Data, tFlashSatTable *SatTable);
  bool FlashSatTablesDecode_ST_TMSC(TYPE_SatInfo_TMSC *Data, tFlashSatTable *SatTable);

  typedef struct
  {
    byte                SatIdx;

    word                Polar:1;              // 0=V, 1=H
    word                unused1:3;
    word                ModulationSystem:1;   // 0=DVBS, 1=DVBS2
    word                ModulationType:2;     // 0=Auto, 1=QPSK, 2=8PSK, 3=16QAM
    word                FECMode:4;            // 0x0 = AUTO, 0x1 = 1_2, 0x2 = 2_3, 0x3 = 3_4,
                                              // 0x4 = 5_6 , 0x5 = 7_8, 0x6 = 8_9, 0x7 = 3_5,
                                              // 0x8 = 4_5, 0x9 = 9_10, 0xa = reserved, 0xf = NO_CONV
    word                Pilot:1;
    word                unused2:4;

    byte                unused3;
    dword               Frequency;
    word                SymbolRate;
    word                TSID;

    word                AllowTimeSync:1;
    word                unused4:15;

    word                OriginalNetworkID;
  }__attribute__((packed)) TYPE_TpInfo_TMSS;

  typedef struct
  {
    byte                SatIdx;
    byte                ChannelNr;
    byte                Bandwidth;
    byte                unused1;
    dword               Frequency;
    word                TSID;
    byte                LPHP;
    byte                unused2;
    word                OriginalNetworkID;
    word                NetworkID;
  }__attribute__((packed)) TYPE_TpInfo_TMST;

  typedef struct
  {
    dword               Frequency;
    word                SymbolRate;
    word                TSID;
    word                OriginalNetworkID;
    byte                ModulationType;
    byte                unused1;
  }__attribute__((packed)) TYPE_TpInfo_TMSC;

  bool FlashTransponderTablesDecode_ST_TMSC(TYPE_TpInfo_TMSC *Data, tFlashTransponderTable *TransponderTable);
  bool FlashTransponderTablesDecode_ST_TMSS(TYPE_TpInfo_TMSS *Data, tFlashTransponderTable *TransponderTable);
  bool FlashTransponderTablesDecode_ST_TMST(TYPE_TpInfo_TMST *Data, tFlashTransponderTable *TransponderTable);
  bool FlashTransponderTablesEncode_ST_TMSC(TYPE_TpInfo_TMSC *Data, tFlashTransponderTable *TransponderTable);
  bool FlashTransponderTablesEncode_ST_TMSS(TYPE_TpInfo_TMSS *Data, tFlashTransponderTable *TransponderTable);
  bool FlashTransponderTablesEncode_ST_TMST(TYPE_TpInfo_TMST *Data, tFlashTransponderTable *TransponderTable);


  bool FlashTimeDecode_ST_TMSS(tFlashTimeInfo *Data, tFlashTimeInfo *TimeInfo);
  bool FlashTimeDecode_ST_TMST(tFlashTimeInfo *Data, tFlashTimeInfo *TimeInfo);
  bool FlashTimeDecode_ST_TMSC(tFlashTimeInfo *Data, tFlashTimeInfo *TimeInfo);

  typedef struct
  {
    word                TunerIndex:8;
    word                RecMode:3;
    word                DemuxPath:2;
    word                ManualRec:1;
    word                unused1:2;          //uumd drrr tttt tttt

    byte                SatIndex;

    byte                ServiceType:1;
    byte                ReservationType:3;
    byte                unused2:4;          //uuuu rrrt

    word                ServiceID;
    word                Duration;
    byte                unused3;
    char                FileName[131];
    dword               StartTime;
    dword               EndTime;
    word                PMTPID;
    byte                isRec;
    byte                NameSet;
    byte                unused4;
    byte                EPGMarker;
    word                unused5;
    dword               unknown1;
    dword               EventID1;
    dword               EventID2;
    word                ServiceIndex;
    byte                unused8[8];
    byte                IceTV;
    byte                unused9[5];

    TYPE_TpInfo_TMSS    TpInfo;
  }__attribute__((packed)) TYPE_Timer_TMSS;

  typedef struct
  {
    word                TunerIndex:8;
    word                RecMode:3;
    word                DemuxPath:2;
    word                ManualRec:1;
    word                unused1:2;

    byte                SatIndex;

    byte                ServiceType:1;
    byte                ReservationType:3;
    byte                unused2:4;

    word                ServiceID;
    word                Duration;
    byte                unused3;
    char                FileName[131];
    dword               StartTime;
    dword               EndTime;
    word                PMTPID;
    byte                isRec;
    byte                NameSet;
    byte                unused4;
    byte                EPGMarker;
    word                unused5;
    dword               unknown1;
    dword               EventID1;
    dword               EventID2;
    word                ServiceIndex;
    byte                unused8[8];
    byte                IceTV;
    byte                unused9[13];

    TYPE_TpInfo_TMST    TpInfo;
  }__attribute__((packed)) TYPE_Timer_TMST;

  typedef struct
  {
    word                TunerIndex:8;
    word                RecMode:3;
    word                DemuxPath:2;
    word                ManualRec:1;
    word                unused1:2;

    byte                SatIndex;

    byte                ServiceType:1;
    byte                ReservationType:3;
    byte                unused2:4;

    word                ServiceID;
    word                Duration;
    byte                unused3;
    char                FileName[131];
    dword               StartTime;
    dword               EndTime;
    word                PMTPID;
    byte                isRec;
    byte                NameSet;
    byte                unused4;
    byte                EPGMarker;
    word                unused5;
    dword               unknown1;
    dword               EventID1;
    dword               EventID2;
    word                ServiceIndex;
    byte                unused8[8];
    byte                IceTV;
    byte                unused9[5];
    TYPE_TpInfo_TMST    TpInfo;
  }__attribute__((packed)) TYPE_Timer_TMST200;

  typedef struct
  {
    word                TunerIndex:8;
    word                RecMode:3;
    word                DemuxPath:2;
    word                ManualRec:1;
    word                unused1:2;

    byte                SatIndex;

    byte                ServiceType:1;
    byte                ReservationType:3;
    byte                unused2:4;

    word                ServiceID;
    word                Duration;
    byte                unused3;
    char                FileName[131];
    dword               StartTime;
    dword               EndTime;
    word                PMTPID;
    byte                isRec;
    byte                NameSet;
    byte                unused4;
    byte                EPGMarker;
    word                unused5;
    dword               unknown1;
    dword               EventID1;
    dword               EventID2;
    word                ServiceIndex;
    byte                unused8[8];
    byte                IceTV;
    byte                unused9[5];

    TYPE_TpInfo_TMSC    TpInfo;
  }__attribute__((packed)) TYPE_Timer_TMSC;


  bool FlashTimerDecode_ST_TMSS(TYPE_Timer_TMSS *Data, tFlashTimer *TimerInfo);
  bool FlashTimerDecode_ST_TMST(TYPE_Timer_TMST *Data, tFlashTimer *TimerInfo);
  bool FlashTimerDecode_ST_TMST200(TYPE_Timer_TMST200 *Data, tFlashTimer *TimerInfo);
  bool FlashTimerDecode_ST_TMSC(TYPE_Timer_TMSC *Data, tFlashTimer *TimerInfo);

  bool FlashTimerEncode_ST_TMSS(TYPE_Timer_TMSS *Data, tFlashTimer *TimerInfo);
  bool FlashTimerEncode_ST_TMST(TYPE_Timer_TMST *Data, tFlashTimer *TimerInfo);
  bool FlashTimerEncode_ST_TMST200(TYPE_Timer_TMST200 *Data, tFlashTimer *TimerInfo);
  bool FlashTimerEncode_ST_TMSC(TYPE_Timer_TMSC *Data, tFlashTimer *TimerInfo);

  void FlashReindexTimers(int SvcType, int FromSvcNum, int ToSvcNum);

  typedef struct
  {
    dword               StartTime;
    dword               EndTime;
    word                Duration;

    word                ReservationType:3;  //see TYPE_ReservationType
    word                unknown1:4;
    word                DelOrig:1;
    word                unknown2:1;         //always 1?
    word                NrOfFiles:6;
    word                unknown3:1;
    dword               AutomaticMode;
    char                FileName[50][128];
  } TYPE_AutoDescrambleTimer;

  bool FlashADDecode_ST_TMSS(TYPE_AutoDescrambleTimer *Data, tAutoDescrambleTimer *ADTimer);
  bool FlashADDecode_ST_TMST(TYPE_AutoDescrambleTimer *Data, tAutoDescrambleTimer *ADTimer);
  bool FlashADDecode_ST_TMSC(TYPE_AutoDescrambleTimer *Data, tAutoDescrambleTimer *ADTimer);

  bool FlashADEncode_ST_TMSS(TYPE_AutoDescrambleTimer *Data, tAutoDescrambleTimer *ADTimer);
  bool FlashADEncode_ST_TMST(TYPE_AutoDescrambleTimer *Data, tAutoDescrambleTimer *ADTimer);
  bool FlashADEncode_ST_TMSC(TYPE_AutoDescrambleTimer *Data, tAutoDescrambleTimer *ADTimer);

  void FlashReindexFavorites(int SvcType, int FromSvcNum, int ToSvcNum);

#endif
