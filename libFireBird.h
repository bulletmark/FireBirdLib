#ifndef __FBLIB__
  #define __FBLIB__

//  #define DEBUG_FIREBIRDLIB

  #define __FBLIB_RELEASEDATE__ "2012-04-08"

  #ifdef _TMSEMU_
    #define __FBLIB_VERSION__ __FBLIB_RELEASEDATE__" TMSEmulator"
  #else
    #define __FBLIB_VERSION__ __FBLIB_RELEASEDATE__
  #endif

  #define isTMS         1

  #ifdef PC_BASED
    #define inline
    #define __attribute__(a)
  #else
    #ifdef _TMSEMU_
      #include "tap_tmsemu.h"
    #else
      #include "tap.h"
    #endif
  #endif

  #undef __USE_LARGEFILE64
  #define __USE_LARGEFILE64
  #undef _LARGEFILE64_SOURCE
  #define _LARGEFILE64_SOURCE
  #define _FILE_OFFSET_BITS     64

  #include              <sys/types.h>

  #ifdef __cplusplus
    extern "C" {
  #endif

  extern word           ApplID;
  extern dword          TAP_TableIndex;


  /*****************************************************************************************************************************/
  /* Main                                                                                                                      */
  /*****************************************************************************************************************************/
  #define TAP_MAX       16

  typedef enum
  {
    ST_UNKNOWN,
    ST_S,
    ST_T,
    ST_C,
    ST_T5700,
    ST_TMSS,
    ST_TMST,
    ST_TMSC,
    ST_T5800,
    ST_ST,
    ST_CT,
    ST_TF7k7HDPVR,
    ST_NRTYPES
  } SYSTEM_TYPE;

  typedef enum
  {
    BOOT_FRONT_PANEL,
    BOOT_REMOTE_CONTROL,
    BOOT_TIMER,
    BOOT_CRASH_REBOOT                  //applied by the AutoReboot TAP only (TF5000)
  } tBootReason;

  typedef enum
  {
    TIMESTAMP_NONE,
    TIMESTAMP_HM,
    TIMESTAMP_HMS,
    TIMESTAMP_YMD,
    TIMESTAMP_YMDHM,
    TIMESTAMP_YMDHMS,
    TIMESTAMP_FNYMDHM
  } eTimeStampFormat;

  //Firmware.dat structure
  typedef struct
  {
    dword                 Magic;                  //0x12345678
    dword                 CompileDate;            //yymd
    word                  ToppyInfoLayoutVersion;
    word                  FWInfoLayoutVersion;
    dword                 NrOfToppyInfoEntries;
    dword                 NrOfFWInfoEntries;
  } tFWDATHeader;

  typedef enum
  {
    DT_LED,
    DT_VFD5500,
    DT_VFDMP
  } DISPLAY_TYPE;

  typedef enum
  {
    RT_5000,
    RT_2100,
    RT_7100PLUS
  } REMOTE_TYPE;

  typedef struct
  {
    word                  SysID;
    word                  unused1;
    char                  Device [256];
    char                  AppType [32];
    SYSTEM_TYPE           SystemType;
    dword                 FlashBase;
    bool                  EMMA;
    bool                  BigEndian;
    bool                  PVR;
    bool                  TAPs;
    DISPLAY_TYPE          DisplayType;
    REMOTE_TYPE           RemoteType;
    dword                 MaxRecStreams;
    byte                  RecExtension;   //0=.rec, 1=.mpg
    byte                  unused2[18];
  } tToppyInfo;

  typedef struct
  {
    word                  SysID;
    word                  unused1;
    dword                 FWgp;
    dword                 FWDate;
    word                  AppVersion;
    word                  unused2;
    dword                 unused3;
    bool                  Beta;
    byte                  MD5 [16];
    byte                  unused4 [32];
  } tFWInfo;

  #define LE16(p)       (p)
  #define LE32(p)       (p)

  #define XDATA                                       //don't use XDATA on the TMS
  #define TS_FILE_NAME_SIZE   MAX_FILE_NAME_SIZE      //the name has changed
  #define ATTR_PARENT         0xf0                    //FindFirst/FindNext doesn't know about ..

  #ifndef PC_BASED
    extern char puffer[];
    #ifndef _TMSEMU_
      void PrintNet(char *puffer);
      #define TAP_PrintNet(...) {sprintf(puffer, __VA_ARGS__); PrintNet(puffer);}
      // Define the following override if you want to stop FBLIB
      // intercepting TAP_Print() [i.e. printf() from TAPs]. Normally,
      // FBLIB intercepts these messages to a local pseudo terminal.
      // Without the interception, TMS directs these to an FTP debug
      // socket.
      #ifndef FB_NO_TAP_PRINT_OVERRIDE
        #define TAP_Print   TAP_PrintNet
      #endif
    #else
      #define TAP_PrintNet(...) {sprintf(puffer, __VA_ARGS__); TAP_Output(puffer);}
    #endif
  #endif

  bool        InitTAPex(void);
  void        InitTAPexFailedMsg(char *ProgramName);
  tBootReason BootReason(void);
  void        TAP_EnterNormalNoInfo(void);
  dword       FirmwareDatMJD(void);
  void        FlushCache(dword *pAddr, int Size);
  char       *GetApplVer(void);
  byte       *GetMacAddress(void);
  word        GetSysID(void);
  SYSTEM_TYPE GetSystemType(void);
  char       *GetToppyString(word SysID);
  dword       GetUptime(void);
  char       *iso639_1(int OSDLan);
  bool        LoadFirmwareDat(tFWDATHeader **FWDatHeader, tToppyInfo **ToppyInfo, tFWInfo **FWInfo);
  bool        PutDevEvent(word Event, dword Param1);


  /*****************************************************************************************************************************/
  /* Audio / Video / OSD                                                                                                       */
  /*****************************************************************************************************************************/

  //Forgotten keys
  #define RKEY_Red      RKEY_NewF1
  #define RKEY_Green    RKEY_F2
  #define RKEY_Yellow   RKEY_F3
  #define RKEY_Blue     RKEY_F4
  #define RKEY_Option   0x10049
  #define RKEY_White    RKEY_Option

  #ifndef TAP_ALPHA
    #define TAP_ALPHA     255
  #endif

  #define _Clip(a)      (a)>255 ? 255 : (a)<0 ? 0 : (a)

  #define YUVR(y,u,v)   ((0x2568*(y) + 0x3343*(u)) >>13)                //0x2000
  #define YUVG(y,u,v)   ((0x2568*(y) - 0x0c92*(v) - 0x1a1e*(u)) >>13)   //0x2000
  #define YUVB(y,u,v)   ((0x2568*(y) + 0x40cf*(v)) >>13)                //0x2000

  #define win_w(w)      ((w) + 51)
  #define win_h(h)      (((h) / 22 + ((h) % 22 ? 1 : 0)) * 22 + 8)
  #define win_l(h)      ((win_h(h) - 8) / 22)

  #define A1555(x)      (((x)>>15)&0x01)
  #define R1555(x)      (((x)>>10)&0x1f)
  #define G1555(x)      (((x)>> 5)&0x1f)
  #define B1555(x)      (((x)>> 0)&0x1f)

  #define A8888(x)      (((x)>>24)&0xff)
  #define R8888(x)      (((x)>>16)&0xff)
  #define G8888(x)      (((x)>> 8)&0xff)
  #define B8888(x)      (((x)>> 0)&0xff)

  #define ARGBtoTMS(a,r,g,b)  a*=0xff;r*=8.2258;g*=8.2258;b*=8.2258
  #define TMStoARGB(a,r,g,b)  a/=0xff;r/=8.2258;g/=8.2258;b/=8.2258

  struct BMP_HEAD
  {
    byte                id[2];
    word                size_l;
    word                size_h;
    word                reserved[2];
    word                offset_l;
    word                offset_h;
  };

  struct BMP_INFO
  {
    long                info_size;
    long                width;
    long                height;
    word                plane;
    word                bits_per_pixel;
    long                compress;
    long                img_size;
    long                x_res;
    long                y_res;
    long                color;
    long                icolor;
  };

  typedef struct
  {
    word        x;
    word        y;
    word        Width;
    word        Height;
    dword       pMemoryOSD;
    byte        byteFormat;
    byte        lutIdx;
    byte        plane;
    byte        unknown;
  } tOSDMapInfo;

  // directions
  typedef enum
  {
    X,
    Y
  } eCopyDirection;

  typedef struct
  {
    byte                  unused1[4677];
    byte                  NrOfTracks;
    byte                  CurrentTrack;
    byte                  unused2;
    word                  PID[64];
    byte                  StreamType[64];
    char                  StreamName[64][32];
    word                  unknown1[64];
    byte                  unused4[64 * 32];
    dword                 unknown2[64];
  } tAudioTrk;

  typedef enum
  {
    PLT_Unchanged,
    PLT_DataFiles,
    PLT_ProgramFiles,
    PLT_MP3Files,
    PLT_MediaFiles,
  } tPvrListType;

  tAudioTrk *AudioTrackInfo(void);
  bool  CaptureScreen(int BMPwidth, int BMPheight, byte *BMPPixelBuffer, bool bOSD, int Alpha);
  void  DrawOSDLine(word OSDRgn, dword Ax, dword Ay, dword Bx, dword By, dword Color);
  void  EndMessageWin(void);
  void  FreeOSDRegion(word Region);
  TYPE_TapEvent *GetCurrentEvent(int *curEvent);
  dword GetOSDMapAddress(void);
  word  GetOSDRegionHeight(word Region);
  word  GetOSDRegionWidth(word Region);
  bool  GetPIPPosition(int *North, int *South, int *East, int *West);
  byte  GetStreamFormat(byte Index);
  bool  isAnyOSDVisible(dword checkX, dword checkY, dword checkW, dword checkH);
  bool  isAnyOSDVisibleEx(dword checkX, dword checkY, dword checkW, dword checkH, byte Plane);
  bool  isInfoBoxVisible(void);
  bool  isDirectSvcNumVisible(void);
  bool  isOSDRegionAlive(word Region);
  bool  isPIPActive(void);
  void  OSDCopy(word rgn, dword x, dword y, dword w, dword h, word items, eCopyDirection direction);
  bool  SaveBitmap(char *strName, int width, int height, byte* pBuffer );
  void  SetRemoteMode(byte Mode, bool Active);
  void  ShowMessageWin(char* title, char* lpMessage1, char* lpMessage2, dword dwDelay);
  void  ShowMessageWindow(char **content, dword pos_x, dword pos_y, byte fntSize, byte align, dword bdcolor, dword titlecolor, dword msgcolor, dword bgcolor, dword delay);
  bool  ShowPvrList(tPvrListType PvrListType);
  void  SoundSinus(word freq, dword durationInMilliseconds, word Amplitude);
  bool  TAP_GetSysOsdControl(TYPE_TapSysOsdId osdId);
  int   TAP_Osd_PutFreeColorGd(word rgn, int x, int y, TYPE_GrData * gd, bool sprite, dword FilterColor);
  byte  TunerGet(int MainSub);
  bool  TunerSet(byte Tuner);


  /*****************************************************************************************************************************/
  /* Compression                                                                                                               */
  /*****************************************************************************************************************************/

  typedef enum
  {
    TFDTYPE_LoaderPgm,
    TFDTYPE_ApplPgm,
    TFDTYPE_FlashData,
    TFDTYPE_EepromData,
    TFDTYPE_FactoryData,
    TFDTYPE_BackgndPict,
  } TFDTYPE;

  word  CompressBlock(byte *pInput, word InBufferSize, byte *pOutput);
  dword CompressTFD(byte *pSrc, dword SourceBufferSize, byte *pDest, word TFDType, word SysID, void *pPercentFinishedCallback);
  dword CompressedTFDSize(byte *pSrc, dword SourceBufferSize, void *pPercentFinishedCallback);
  word  CRC16(word StartValue, void *StartAddress, dword Length);
  dword CRC32(dword StartValue, void *StartAddress, dword Length);
  bool  MD5String(char *inString, byte *Digest);
  bool  MD5File(char *FileName, byte *Digest);
  dword OATH(register unsigned char * data, int len, dword hash);
  dword SuperFastHash(register unsigned char * data, int len, dword hash);
  word  UncompressBlock(byte *pInput, word compCount, byte *pOutput, word bufSize);
  dword UncompressLoader(byte *pSrc, byte *pDest, void *pPercentFinishedCallback);
  dword UncompressedLoaderSize(byte *pSrc);
  dword UncompressFirmware(byte *pSrc, byte *pDest, void *pPercentFinishedCallback);
  dword UncompressedFirmwareSize(byte *pSrc);
  dword UncompressTFD(byte *pSrc, byte *pDest, void *pPercentFinishedCallback);
  dword UncompressedTFDSize(byte *pSrc);
  dword TFDSize(byte *pTFD);


  /*****************************************************************************************************************************/
  /* Debugging                                                                                                                 */
  /*****************************************************************************************************************************/

  void   DumpMemory(unsigned char* p, dword size, int BytesPerLine);
  void   DumpMemoryDword(dword *p, dword size);
  dword *FindGotPointer(dword FunctionAddress);
  void   LogEntry(char *FileName, char *ProgramName, bool Console, eTimeStampFormat TimeStampFormat, char *Text);
  void   LogEntryGeneric(char *ProgramName, bool Console, char *Text);

  bool   HookFirmware(char *FirmwareFunctionName, void *RedirectTo, dword *PointerToOriginal);
  bool   UnhookFirmware(char *FirmwareFunctionName, void *RedirectTo, dword *PointerToOriginal);

  void   CallTraceInit(void);
  void   CallTraceEnable(bool Enable);
  void   CallTraceEnter(char *ProcName);
  void   CallTraceExit(dword *Magic);
  void   CallTraceExitResult(dword *Magic, char *Result);
  void   CallTraceComment(char *Comment);
  void   CallTraceExportStats(char *FileName);
  void   CallTraceResetStats(void);


  void* TAP_MemAlloc_Chk(char *Comment, dword size);
  int   TAP_Osd_Copy_Chk(char *Comment, word srcRgnNum, word dstRgnNum, dword srcX, dword srcY, dword w, dword h, dword dstX, dword dstY,  bool sprite);
  int   TAP_Osd_Create_Chk(char *Comment, dword x, dword y, dword w, dword h, byte lutIdx, int flag);
  int   TAP_Osd_FillBox_Chk(char *Comment, word rgn, dword x, dword y, dword w, dword h, dword color);
  int   TAP_Osd_PutFreeColorGd_Chk(char *Comment, word rgn, int x, int y, TYPE_GrData * gd, bool sprite, dword FilterColor);
  int   TAP_Osd_PutGd_Chk(char *Comment, word rgn, int x, int y, TYPE_GrData * gd, bool sprite);
  int   TAP_Osd_PutPixel_Chk(char *Comment, word rgn, dword x, dword y, dword pix);
  void  TAP_Osd_RestoreBox_Chk(char *Comment, word rgn, dword x, dword y, dword w, dword h, void *data);
  byte* TAP_Osd_SaveBox_Chk(char *Comment, word rgn, dword x, dword y, dword w, dword h);


  /*****************************************************************************************************************************/
  /* ELF file format functions                                                                                                 */
  /*****************************************************************************************************************************/

  bool  ELFOpenFile(char *FileName);
  bool  ELFOpenAbsFile(char *FileName);
  bool  ELFReadELFHeader(void);
  bool  ELFReadSectionHeaders(void);
  bool  ELFReadShstrtabSection(void);
  dword ELFGetSectionIndex(char *SectionName);
  bool  ELFGetSectionAddress(dword SectionIndex, dword *SectionAddress, dword *SectionSize);
  bool  ELFReadDWORD(dword SectionIndex, dword *Data);
  bool  ELFReadData(dword SectionIndex, byte *Data);
  void  ELFCleanup(void);

  /*****************************************************************************************************************************/
  /* Firmware functions                                                                                                        */
  /*****************************************************************************************************************************/

  typedef struct
  {
    dword               Magic; //0xbacaed31
    char               *Path;
    dword               unknown1;
    dword               unknown2;
  }tDirEntry;

  byte  DevFront_SetIlluminate(byte a0, byte Brightness);
  dword DevHdd_DeviceClose(tDirEntry **hddPlaybackFolder);
  dword DevHdd_DeviceOpen(tDirEntry **hddPlaybackFolder, tDirEntry *DirEntry);
  int   Appl_CheckRecording(int SvcType, int SvcNum, bool Unknown);
  int   Appl_CheckRecording_Tuner(byte TunerIndex, int SvcType, int SvcNum, bool Unknown);
  void  Appl_ClrTimer(byte *TimerHandle);
  dword Appl_GetFreeExtRecordSpace(char *MountPath);
  void  Appl_ShoutCast(void);
  dword Appl_StopPlaying(void);
  dword Appl_WaitEvt(uint Event, uint *a1, uint a2, uint a3, uint Timeout);
  byte  ApplChannel_GetAgc(unsigned char TunerIndex, unsigned char *AGC);
  byte  ApplChannel_GetBer(unsigned char TunerIndex, unsigned char *BER);
  dword ApplHdd_FileCutPaste(char  const* SourceFileName, unsigned int StartBlock, unsigned int NrBlocks, char const* CutFileName);
  dword ApplHdd_FreeSize(char *MountPath, bool a1);
  dword ApplHdd_GetInfoFromExternalDevice(dword *TotalSpaceMB, dword *FreeSpaceMB, char  const *MountPath);
  void  ApplHdd_RestoreWorkFolder(void);
  void  ApplHdd_SaveWorkFolder(void);
  dword ApplHdd_SelectFolder(tDirEntry *FolderStruct, char const *FolderPath);
  void  ApplHdd_SetWorkFolder(tDirEntry *FolderStruct);
  void  ApplNewVfd_Stop(void);
  void  ApplTimer_OptimizeList(void);


  /*****************************************************************************************************************************/
  /* Flash & EEPROM                                                                                                            */
  /*****************************************************************************************************************************/

  typedef struct
  {
    byte                  SatIndex;
    byte                  VideoStreamType;
    bool                  FlagDelete;
    bool                  FlagCAS;
    bool                  FlagLock;
    bool                  FlagSkip;
    byte                  Tuner;
    word                  TransponderIndex;
    word                  ServiceID;
    word                  PMTPID;
    word                  PCRPID;
    word                  VideoPID;
    word                  AudioPID;
    word                  LCN;
    word                  AudioStreamType;
    char                  ServiceName[MAX_SvcName];
    char                  ProviderName[40];

    //Unidentified fields
    word                  unknown1;
    byte                  unknown2[6];
  } tFlashService;

  int  FlashServiceGetTotal(int SvcType);
  bool FlashServiceGetInfo(int SvcType, int SvcNum, tFlashService *Service);
  bool FlashServiceSetInfo(int SvcType, int SvcNum, tFlashService *Service);
  bool FlashServiceAdd(int SvcType, tFlashService *Service);
  int  FlashServiceFind(int SvcType, word ServiceID, word PMTPID, word PCRPID, tFlashService *Service);
  bool FlashServiceDel(int SvcType, int SvcNum);
  bool FlashServiceMove(int SvcType, int FromSvcNum, int ToSvcNum);

  bool FlashServiceDecode(void *Data, tFlashService *Service);
  bool FlashServiceEncode(void *Data, tFlashService *Service);

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
  } tFlashLNB;

  typedef struct
  {
    word                  NrOfTransponders;
    word                  unused1;
    char                  SatName[16];
    tFlashLNB             LNB[2];
    byte                  unknown1[22];
    word                  SatPosition;
    byte                  unused2[8];
  } tFlashSatTable;

  int   FlashSatTablesGetTotal(void);
  bool  FlashSatTablesGetInfo(int SatNum, tFlashSatTable *SatTable);
  bool  FlashSatTablesDecode(void *Data, tFlashSatTable *SatTable);

  typedef struct
  {
    byte                  SatIndex;                   //*1
    dword                 Frequency;                  //*1, 2
    word                  SymbolRate;                 //*1, 2
    byte                  ChannelNr;
    byte                  Bandwidth;
    word                  TSID;                       //*1, 2
    word                  OriginalNetworkID;          //*1, 2
    word                  NetworkID;                  //*1, 2
    bool                  Pilot;                      //*1
    byte                  FEC;                        //*1: 0x0 = AUTO, 0x1 = 1_2, 0x2 = 2_3, 0x3 = 3_4,
                                                      //    0x4 = 5_6 , 0x5 = 7_8, 0x6 = 8_9, 0x7 = 3_5,
                                                      //    0x8 = 4_5, 0x9 = 9_10, 0xa = reserved, 0xf = NO_CONV
    byte                  Modulation;                 //*1: m from Flags1: 0=Auto, 1=QPSK, 2=8PSK, 3=16QAM
                                                      //*2: 0=16QAM, 1=32QAM, 2=64QAM, 3=128QAM, 4=256QAM
    byte                  ModSystem;                  //*1: 0=DVBS, 1=DVBS2
    byte                  Polarisation;               //*1: 0=V, 1=H
    byte                  LPHP;
    bool                  ClockSync;                  //*1

    word                  unused1;                    //*1
    word                  unused2;                    //*2
    byte                  unused3;                    //*1
    word                  unused4;                    //*1
  } tFlashTransponderTable;

  int  FlashTransponderTablesGetTotal(int SatNum);
  bool FlashTransponderTablesGetInfo(int SatNum, int TransponderNum, tFlashTransponderTable *TransponderTable);
  bool FlashTransponderTablesSetInfo(int SatNum, int TransponderNum, tFlashTransponderTable *TransponderTable);
  int  FlashTransponderTablesAdd(int SatNum, tFlashTransponderTable *TransponderTable);
  bool FlashTransponderTablesDel(int SatNum, int TransponderNum);
  int  FlashTransponderFindIndex(dword SatIndex, dword NetworkID, dword TSID);
  int  FlashTransponderFindIndex2(dword SatIndex, dword NetworkID, dword TSID, byte ModSystem);

  bool FlashTransponderTablesDecode(void *Data, tFlashTransponderTable *TransponderTable);
  bool FlashTransponderTablesEncode(void *Data, tFlashTransponderTable *TransponderTable);

  typedef struct
  {
    short               UTCOffset;
    word                SleepTimer;

    byte                unknown1:3;
    byte                GMTCollection:3;        //0=Normal, 1=CAS Only, 2=User Select
    byte                Mode:1;                 //0=Auto, 1=Manual
    byte                unknown2:1;

    byte                unknown3;

    byte                DST:2;                  //0=off, 3=on
    byte                unknown4:6;

    char                unknown5;
  }tFlashTimeInfo;

  bool FlashTimeGetInfo(tFlashTimeInfo *TimeInfo);
  bool FlashTimeDecode(tFlashTimeInfo *Data, tFlashTimeInfo *TimeInfo);

  typedef struct
  {
    byte                TunerIndex;
    byte                RecMode;
    byte                DemuxPath;
    byte                ManualRec;
    byte                unused1;
    byte                SatIndex;
    byte                ServiceType;
    byte                ReservationType;
    byte                unused2;
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
    tFlashTransponderTable    TpInfo;
  }tFlashTimer;

  bool FlashTimerGetInfo(int TimerIndex, tFlashTimer *TimerInfo);
  bool FlashTimerSetInfo(int TimerIndex, tFlashTimer *TimerInfo);
  bool FlashTimerDecode(void *Data, tFlashTimer *TimerInfo);
  bool FlashTimerEncode(void *Data, tFlashTimer *TimerInfo);
  int  FlashTimerStructSize(void);


  typedef struct
  {
    dword               StartTime;
    dword               EndTime;
    word                Duration;
    TYPE_ReservationType ReservationType;
    bool                DelOrig;
    word                NrOfFiles;
    dword               AutomaticMode;
    char                FileName[50][128];

    word                unknown1;
    word                unknown2;           //always 1?
    word                unknown3;
  } tAutoDescrambleTimer;

  bool FlashADGetInfo(tAutoDescrambleTimer *ADTimer);
  bool FlashADDecode(void *Data, tAutoDescrambleTimer *ADTimer);
  bool FlashADSetInfo(tAutoDescrambleTimer *ADTimer);
  bool FlashADEncode(void *Data, tAutoDescrambleTimer *ADTimer);


  typedef struct
  {
    char                GroupName[12];
    word                SvcNum[100];
    byte                SvcType[100];
    byte                NrEntries;
    byte                unused1;
  } tFavorites;

  int  FlashFavoritesGetTotal(void);
  bool FlashFavoritesGetInfo(int FavNum, tFavorites *Favorites);
  bool FlashFavoritesSetInfo(int FavNum, tFavorites *Favorites);
  int  FlashFavoritesFindService(int SvcType, int SvcNum);


  dword FIS_vFlashBlockAutoDec(void);
  dword FIS_vFlashBlockDLNAData(void);
  dword FIS_vFlashBlockFavoriteGroup(void);
  dword FIS_vFlashBlockGameSaveData(void);
  dword FIS_vFlashBlockLanIPConfig(void);
  dword FIS_vFlashBlockNetwork(void);
  dword FIS_vFlashBlockNetworkUpdateConfig(void);
  dword FIS_vFlashBlockOTAInfo(void);
  dword FIS_vFlashBlockProviderInfo(void);
  dword FIS_vFlashBlockRadioServices(void);
  dword FIS_vFlashBlockSatInfo(void);
  dword FIS_vFlashBlockServerData(void);
  dword FIS_vFlashBlockServiceName(void);
  dword FIS_vFlashBlockTVServices(void);
  dword FIS_vFlashBlockTimeInfo(void);
  dword FIS_vFlashBlockTimer(void);
  dword FIS_vFlashBlockTransponderInfo(void);

  //typedef enum
  //{
  //  delete,
  //  insert
  //} ReindexType;

  //bool                  FlashAddFavourite (char *FavName, word Idx, bool TVService);
  //void                  FlashDeleteFavourites (void);
  //dword                 FlashFindCASServices (bool TVService, bool *FlagArray, dword *NewFlags);
  //dword                 FlashFindEndOfServiceNameTableAddress (void);
  //dword                 FlashFindEndOfServiceTableAddress(bool TVService);
  //dword                 FlashFindServiceByLCN (char* LCN, bool TVService, bool *FlagArray, dword *NewFlags);
  //dword                 FlashFindServiceByName (char* ChannelName, bool TVService, bool *FlagArray, dword *NewFlags);
  //dword                 FlashFindServiceByPartOfName (char* ChannelName, bool TVService, bool *FlagArray, dword *NewFlags);
  //SYSTEM_TYPE           FlashGetType (void);
  //dword                 FlashInitialize (dword SystemID);
  void                  FlashProgram(void);
  //void                  FlashReindexFavourites (word ServiceIndex, int ServiceType, ReindexType itype);
  //void                  FlashReindexTimers (word ServiceIndex, int ServiceType, ReindexType itype);
  //dword                 FlashRemoveCASServices (bool TVService);
  //dword                 FlashRemoveServiceByIndex (int ChannelIndex, bool TVService);
  //dword                 FlashRemoveServiceByIndexString (char* ChannelIndex, bool TVService);
  //dword                 FlashRemoveServiceByLCN (char* LCN, bool TVService);
  //dword                 FlashRemoveServiceByName (char* ChannelName, bool TVService);
  //dword                 FlashRemoveServiceByPartOfName (char* ChannelName, bool TVService);
  //dword                 FlashRemoveServiceByUHF (char* UHFChannel, bool TVService, bool UseAUSChannelCoding);
  dword                 GetEEPROMAddress(void);
  word                  GetEEPROMPin(void);
  bool                  SetEEPROMPin(word NewPin);

  //TYPE_SatInfoSTMS     *FlashGetSatelliteByIndex (byte SatIdx);
  //TYPE_ServiceTMS      *FlashGetServiceByIndex (word ServiceIdx, bool TVService);
  //TYPE_ServiceTMS      *FlashGetServiceByName (char* ChannelName, bool TVService);
  //TYPE_TpInfoSTMS      *FlashGetTransponderSByIndex (word TpIdx, byte SatIdx);
  //word                  FlashServiceAddressToServiceIndex (TYPE_ServiceTMS *ServiceAddress);


  /*****************************************************************************************************************************/
  /* FontManager                                                                                                               */
  /*****************************************************************************************************************************/

  typedef struct
  {
    dword                 Width;
    dword                 Height;
    dword                 BitmapIndex;
  } tFontDef;

  typedef struct
  {
    byte                 *pFontData;
    tFontDef              FontDef[191];
  } tFontData;

  dword FM_GetStringWidth(const char *Text, tFontData *FontData);
  dword FM_GetStringHeight(const char *Text, tFontData *FontData);
  void  FM_PutString(word rgn, dword x, dword y, dword maxX, const char * str, dword fcolor, dword bcolor, tFontData *FontData, byte bDot, byte align);
  void  FM_PutStringAA(word rgn, dword x, dword y, dword maxX, const char * str, dword fcolor, dword bcolor, tFontData *FontData, byte bDot, byte align, float AntiAliasFactor);
  bool  FM_LoadFontFile(char *FontFileName, tFontData *FontData);
  void  FM_FreeFontFile(tFontData *FontData);


  /*****************************************************************************************************************************/
  /* HDD Functions                                                                                                             */
  /*****************************************************************************************************************************/

  #define TAPFSROOT     "/mnt/hd"
  #define FBLIB_DIR_SIZE 256

  //Some of them are missing in the TF5k hdd.h and alle are missing in the TMS hdd.h
  #ifndef SEEK_SET
    #define SEEK_SET  0	/* set file offset to offset */
  #endif

  #ifndef SEEK_CUR
    #define SEEK_CUR  1	/* set file offset to current plus offset */
  #endif

  #ifndef SEEK_END
    #define SEEK_END  2	/* set file offset to EOF plus offset */
  #endif

  typedef enum
  {
    FIU_No,
    FIU_Playback,
    FIU_PlayMP3,
    FIU_RecSlot1,
    FIU_RecSlot2,
    FIU_RecSlot3,
    FIU_RecSlot4,
  }tFileInUse;

  typedef struct
  {
    char                DevPath[10];
    char                MountPath[10];
    char                DevName[16];
    dword               SizeMB;
    dword               PartType; //1 = jfs, 4 = FAT32, 5 = NTFS
  }textPartitionInfo;   //used by the _extPartitionInfo struct

  void       FixInvalidFileName(char *FileName);
  int        HDD_AAM_Disable(void);
  int        HDD_AAM_Enable(byte AAMLevel);
  int        HDD_APM_Disable(void);
  int        HDD_APM_Enable(byte APMLevel);
  bool       HDD_ChangeDir(char *Dir);
  void       HDD_Delete(char *FileName);
  TYPE_File *HDD_FappendOpen(char *filename);
  bool       HDD_FappendWrite(TYPE_File *file, char *data);
  bool       HDD_GetAbsolutePathByTypeFile(TYPE_File *File, char *AbsFileName);

  #ifdef _TMSEMU_
    bool     HDD_GetFileSizeAndInode(char *Directory, char *FileName, dword *CInode, off_t *FileSize);
  #else
    bool     HDD_GetFileSizeAndInode(char *Directory, char *FileName, dword *CInode, __off64_t *FileSize);
  #endif

  dword      HDD_GetFileTimeByAbsFileName(char *FileName);
  dword      HDD_GetFileTimeByRelFileName(char *FileName);
  dword      HDD_GetFileTimeByTypeFile(TYPE_File *File);
  bool       HDD_GetHddID(char *ModelNo, char *SerialNo, char *FirmwareNo);
  dword      HDD_GetInodeByAbsFileName(char *Filename);
  dword      HDD_GetInodeByRelFileName(char *Filename);
  dword      HDD_GetInodeByTypeFile(TYPE_File *File);
  bool       HDD_IdentifyDevice(char *IdentifyDeviceBuffer);
  bool       HDD_isExtRecording(void);
  bool       HDD_Move(char *FileName, char *FromDir, char *ToDir);
  void       HDD_Recycle(char *FileName);
  void       HDD_RemoveDir(char *DirPath, bool Recursive);
  void       HDD_Rename(char *FileName, char *NewFileName);
  word       HDD_SetExtRecording(bool ExtDisk);
  int        HDD_Smart_DisableAttributeAutoSave(void);
  int        HDD_Smart_DisableOperations(void);
  int        HDD_Smart_EnableAttributeAutoSave(void);
  int        HDD_Smart_EnableOperations(void);
  int        HDD_Smart_ReadData(word *DataBuf);
  int        HDD_Smart_ReadThresholdData(word *DataBuf);
  int        HDD_Smart_ReturnStatus(void);                  ////if 20 is returned then one or more thresholds have been exceeded; -1 upon error
  void       HDD_Unrecycle(char *FileName);
  bool       HDD_Write(void *data, dword length, TYPE_File *f);
  tFileInUse HDD_isFileInUse(char *FileName);
  void       MakeUniqueFileName(char *FileName);
  void       SeparateFileNameComponents(char *FileName, char *Name, char *Ext, int *Index, bool *isRec, bool *isDel);


  /*****************************************************************************************************************************/
  /* INI Files                                                                                                                 */
  /*****************************************************************************************************************************/

  typedef enum
  {
    INILOCATION_NotFound,
    INILOCATION_NewFile,           // returned by INIOpenFile only
    INILOCATION_AtCurrentDir,
    INILOCATION_AtAppName,
    INILOCATION_AtSettings,
    INILOCATION_AtProgramFiles,
    INILOCATION_NrENUMs
  } INILOCATION;

  INILOCATION INIOpenFile(char *FileName, char *AppName);
  bool        INISaveFile(char *FileName, INILOCATION INILocation, char *AppName);
  void        INICloseFile(void);
  bool        INIKeyExists(char *Key);
  bool        INIGetRGB(char *Key, byte *Red, byte *Green, byte *Blue, dword DefaultValue);
  bool        INIGetARGB(char *Key, byte *Alpha, byte *Red, byte *Green, byte *Blue, dword DefaultValue);
  bool        INIGetRGB8(char *Key, byte *Red, byte *Green, byte *Blue, dword DefaultValue);
  bool        INIGetARGB8(char *Key, byte *Alpha, byte *Red, byte *Green, byte *Blue, dword DefaultValue);
  byte        INIGetHexByte(char *Key, byte DefaultValue, byte MinValue, byte MaxValue);
  dword       INIGetHexDWord(char *Key, dword DefaultValue, dword MinValue, dword MaxValue);
  word        INIGetHexWord(char *Key, word DefaultValue, word MinValue, word MaxValue);
  long int    INIGetInt(char *Key, long int DefaultValue, long int MinValue, long int MaxValue);
  bool        INIGetString(char *Key, char *Value, char *DefaultValue, dword MaxLength);
  void        INIKillKey(char *Key);
  INILOCATION INILocateFile(char *FileName, char *AppName);
  void        INISetRGB(char *Key, byte Red, byte Green, byte Blue);
  void        INISetRGB8(char *Key, byte Red, byte Green, byte Blue);
  void        INISetARGB(char *Key, byte Alpha, byte Red, byte Green, byte Blue);
  void        INISetARGB8(char *Key, byte Alpha, byte Red, byte Green, byte Blue);
  void        INISetHexByte(char *Key, byte Value);
  void        INISetHexDWord(char *Key, dword Value);
  void        INISetHexWord(char *Key, word Value);
  void        INISetInt(char *Key, long int Value);
  void        INISetString(char *Key, char *Value);

  INILOCATION LangLoadStrings(char *LangFile, dword NrStrings, int FallbackLang, char *AppName);
  void        LangUnloadStrings(void);
  char       *LangGetString(dword StringID);
  char       *LangGetStringDefault(dword StringID, char *DefaultString);


  /*****************************************************************************************************************************/
  /* InstuctionSequences                                                                                                       */
  /*****************************************************************************************************************************/

  dword TryResolve(char *Function);

  inline dword FIS_fwAppl_AddSvcName(void);
  inline dword FIS_fwAppl_CheckRecording(void);
  inline dword FIS_fwAppl_CheckRecording_Tuner(void);
  inline dword FIS_fwAppl_ClrTimer(void);
  inline dword FIS_fwAppl_DeleteRadioSvcName(void);
  inline dword FIS_fwAppl_DeleteTvSvcName(void);
  inline dword FIS_fwAppl_EnterNormal(void);
  inline dword FIS_fwAppl_ExecProgram(void);
  inline dword FIS_fwAppl_ExportChData(void);
  inline dword FIS_fwAppl_GetFreeExtRecordSpace(void);
  inline dword FIS_fwAppl_GetIsExternal(void);
  inline dword FIS_fwAppl_GetStreamFormat(void);
  inline dword FIS_fwAppl_ImportChData(void);
  inline dword FIS_fwAppl_InitTempRec(void);
  inline dword FIS_fwAppl_IsTimeShifting(void);
  inline dword FIS_fwAppl_PvrList(void);
  inline dword FIS_fwAppl_PvrList_SetListType(void);
  inline dword FIS_fwAppl_RestartTimeShiftSvc(void);
  inline dword FIS_fwAppl_SetApplVer(void);
  inline dword FIS_fwAppl_SetIsExternal(void);
  inline dword FIS_fwAppl_SetProviderName(void);
  inline dword FIS_fwAppl_SetTimeShift(void);
  inline dword FIS_fwAppl_ShoutCast(void);
  inline dword FIS_fwAppl_StartPlaybackMedia(void);
  inline dword FIS_fwAppl_StartTempRec(void);
  inline dword FIS_fwAppl_StopPlaying(void);
  inline dword FIS_fwAppl_StopRecPlaying(void);
  inline dword FIS_fwAppl_StopTempRec(void);
  inline dword FIS_fwAppl_TimeToLocal(void);
  inline dword FIS_fwAppl_WaitEvt(void);
  inline dword FIS_fwAppl_WriteFlash(void);
  inline dword FIS_fwAppl_WriteRecInfo(void);
  inline dword FIS_fwApplChannel_GetAgc(void);
  inline dword FIS_fwApplChannel_GetBer(void);
  inline dword FIS_fwApplHdd_FileCutPaste(void);
  inline dword FIS_fwApplHdd_FreeSize(void);
  inline dword FIS_fwApplHdd_GetFileInfo(void);
  inline dword FIS_fwApplHdd_GetInfoFromExternalDevice(void);
  inline dword FIS_fwApplHdd_RestoreWorkFolder(void);
  inline dword FIS_fwApplHdd_SaveWorkFolder(void);
  inline dword FIS_fwApplHdd_SelectFolder(void);
  inline dword FIS_fwApplHdd_SetWorkFolder(void);
  inline dword FIS_fwApplOsd_DrawJpeg(void);
  inline dword FIS_fwApplTap_CallEventHandler(void);
  inline dword FIS_fwApplTap_GetEmptyTask(void);
  inline dword FIS_fwApplTimer_OptimizeList(void);
  inline dword FIS_fwApplTimeToLocal(void);
  inline dword FIS_fwApplVfdSendData(void);
  inline dword FIS_fwApplVfdStart(void);
  inline dword FIS_fwApplVfdStop(void);
  inline dword FIS_fwDevEeprom_GetMacAddr(void);
  inline dword FIS_fwDevEeprom_Info(void);
  inline dword FIS_fwDevFront_PowerOffCancel(void);
  inline dword FIS_fwDevFront_PowerOffReply(void);
  inline dword FIS_fwDevFront_SetIlluminate(void);
  inline dword FIS_fwDevHdd_DeviceClose(void);
  inline dword FIS_fwDevHdd_DeviceOpen(void);
  inline dword FIS_fwEeprom_DirectWrite(void);
  inline dword FIS_fwPowerOff(void);
  inline dword FIS_fwPutDevEvt(void);
  inline dword FIS_fwSetIrCode(void);

  inline dword FIS_vApplState(void);
  inline dword FIS_vAudioTrack(void);
  inline dword FIS_vBootReason(void);
  inline dword FIS_vCheckAutoDecTimerId(void);
  inline dword FIS_vCurTapTask(void);
  inline dword FIS_vDirectSvcNumTimerId(void);
  inline dword FIS_vEEPROM(void);
  inline dword FIS_vEEPROMPin(void);
  inline dword FIS_vEtcInfo(void);
  inline dword FIS_vExtPartitionInfo(void);
  inline dword FIS_vExtTsFolder(void);
  inline dword FIS_vVfdTimerId(void);
  inline dword FIS_vFlash(void);
  inline dword FIS_vGrid(void);
  inline dword FIS_vHddDivxFolder(void);
  inline dword FIS_vhddRecordFile(void);
  inline dword FIS_vHddTapFolder(void);
  inline dword FIS_vHddTsFolder(void);
  inline dword FIS_vIboxTimerId(void);
  inline dword FIS_vIsAllPartitionInvalid(void);
  inline dword FIS_vIsPipActive(void);
  inline dword FIS_vIsPopUpOn(void);
  inline dword FIS_vMACAddress(void);
  inline dword FIS_vnExtPartition(void);
  inline dword FIS_vnPipSvcNum(void);
  inline dword FIS_vnRadioSvc(void);
  inline dword FIS_vnTvSvc(void);
  inline dword FIS_vOsdMap(void);
  inline dword FIS_vOsdOutBuf(void);
  inline dword FIS_vParentalInfo(void);
  inline dword FIS_vPhotoAlbumInfo(void);
  inline dword FIS_vPipH(void);
  inline dword FIS_vPipSvcNum(void);
  inline dword FIS_vPipW(void);
  inline dword FIS_vPipX(void);
  inline dword FIS_vPipY(void);
  inline dword FIS_vPvrRecTsInfo(void);
  inline dword FIS_vPvrRecTsPlayInfo(void);
  inline dword FIS_vRECSlotAddress(byte Slot);
  inline dword FIS_vSelectedPartition(void);
  inline dword FIS_vShoutCastInfo(void);
  inline dword FIS_vShoutCastState(void);
  inline dword FIS_vTAPTable(void);
  inline dword FIS_vTapSysOsdCtrl(void);
  inline dword FIS_vTimerEditInfo(void);
  inline dword FIS_vTimerTempInfo(void);
  inline dword FIS_vTopEvent(void);
  inline dword FIS_vVfdBrightTimerId(void);

  /*****************************************************************************************************************************/
  /* LogoManager                                                                                                               */
  /*****************************************************************************************************************************/

  #define LOGOROOT        "/ProgramFiles/Settings/Logos"
  #define LOGOPACK        "LogoPack.tar"
  #define LOGOCACHE       "Logo.cache"
  #define LOGOCACHEID     "LGC"
  #define LOGOCACHEVERSION 2
  #define LILNAME         "Logos.lil"

  typedef enum
  {
    LGST_3pgstyle,
    LGST_QtstyleBlue,
    LGST_QtstyleGrey,
    LGST_QtstyleTMS,
    LGST_TransBlack,
    LGST_TransIBBlue,
    LGST_TransIBGrey,
    LGST_TransQTBlue,
    LGST_TransQTGrey,
    LGST_NRITEMS
  } tLogoStyle;

  typedef enum
  {
    LGSZ_qtl,
    LGSZ_ibl,
    LGSZ_qsl,
    LGSZ_NRITEMS
  } tLogoSize;

  typedef enum
  {
    LGAR_43,
    LGAR_169,
    LGAR_NRITEMS
  } tLogoAspect;

  void          LogoManager_Initialize(void *Callback);
  void          LogoManager_MoveExternalUpdates(void);
  char         *LogoManager_ChannelNameToLogoName(char *ChannelName);
  void          LogoManager_Cleanup(void);
  bool          LogoManager_LogoCacheLoad(void);
  void          LogoManager_LogoCacheRebuild(void);
  TYPE_GrData  *LogoManager_GetLogoByChannelID(ulong64 ChannelID, tLogoStyle LogoStyle, tLogoSize LogoSize, tLogoAspect LogoAR);
  TYPE_GrData  *LogoManager_GetLogoByLogoName(char *LogoName, tLogoStyle LogoStyle, tLogoSize LogoSize, tLogoAspect LogoAR);
  TYPE_GrData  *LogoManager_GetLogoByChannelName(char *ChannelName, tLogoStyle LogoStyle, tLogoSize LogoSize, tLogoAspect LogoAR);
  TYPE_GrData  *LogoManager_GetLogoByChannel(int SvcType, int SvcNum, tLogoStyle LogoStyle, tLogoSize LogoSize, tLogoAspect LogoAR);
  char         *LogoManager_GetDirectory(tLogoStyle LogoStyle, tLogoAspect LogoAR);
  char         *LogoManager_GetPathToLogoByChannelID(ulong64 ChannelID, tLogoStyle LogoStyle, tLogoSize LogoSize, tLogoAspect LogoAR);
  bool          LogoManager_LogosAvailable(tLogoStyle LogoStyle);
  int           LogoManager_UpdateLIL(void);
  void          LogoManager_ProcessLILAdd(char *AddFileName);
  ulong64       LogoManager_CalculateChannelID(word SatLongitude, word NetworkID, word TSID, word ServiceID);
  ulong64       LogoManager_GetChannelID(int SvcType, int SvcNum);

  //The callback parameter may point to the following prototype
  // void Callback(int CallbackType, int Param);
  //
  //It gets called under the following circumstances:
  //  * Reports the number of successfully loaded logos (CallbackType=0, Param1=number of logos)
  //  * A new logo package (Logos.tar) has been found (CallbackType=1, Param1=0)
  //  * The cache file needs to be rebuilt (CallbackType=2, Param1 reflects the progress)
  //  * The number of of lgoo files found during the rebuild (CallbackType=4, Param1 is the number of files)
  //  * The cache rebuild has finished (CallbackType=3, Param1=0)
  //  * An error occurs (CallbackType=-1, Param1 reports one of the following errors:
  //    * 0: failed to reserve memory for LogoData
  //    * 1: cache file is invalid
  //    * 2: failed to open a logo file


  /*****************************************************************************************************************************/
  /* REC Stream functions                                                                                                      */
  /*****************************************************************************************************************************/

  //ST_S       = 1
  //ST_ST      = 2
  //ST_T       = 3
  //ST_C       = 4
  //ST_CT      = 5
  //ST_T5700   = 6
  //ST_T5800   = 7
  //ST_TMSS    = 8
  //ST_TMST    = 9
  //ST_TMSC    = a

  typedef struct
  {
    dword               HeaderMagic;                 //123456789a
    word                HeaderVersion;               //123456789a
    dword               HeaderStartTime;             //       89a
    word                HeaderDuration;              //13467  89a
    word                HeaderDurationSec;           //       89a
    word                HeaderSvcNumber;             //13467
    word                HeaderSvcType;               //13467
    byte                HeaderFlags;                 //       89a
    bool                HeaderCopyFlag;              //       89a
    bool                HeaderTSFlag;                //       89a
    byte                HeaderFlags2;                //       89a
    byte                HeaderUnknown1[4];           //
    byte                HeaderUnknown2[2];           //13467  89a
    byte                HeaderUnknown4[10];          //       89a

    byte                SISatIndex;                  //13467  89a
    byte                SIServiceType;               //13467  89a
    word                SITPIdx;                     //13467  89a
    byte                SITunerNum;                  //13467  89a
    byte                SIDelFlag;                   //13467  89a
    byte                SICASFlag;                   //13467  89a
    byte                SILockFlag;                  //13467  89a
    byte                SISkipFlag;                  //13467  89a
    word                SIServiceID;                 //13467  89a
    word                SIPMTPID;                    //13467  89a
    word                SIPCRPID;                    //13467  89a
    word                SIVideoPID;                  //13467  89a
    word                SIAudioPID;                  //13467  89a
    char                SISvcName[28];               //13467  89a
    byte                SIVideoStreamType;           //       89a
    byte                SIAudioStreamType;           //       89a

    byte                TPSatIndex;                  //1      89a
    word                TPFlags2;                    //       8
    byte                TPPolarization;              //1      8
    byte                TPMode;                      //1      8
    byte                TPSystem;                    //       8
    byte                TPModulation;                //4      8
    byte                TPFEC;                       //       8
    byte                TPPilot;                     //       8
    word                TPChannelNumber;             //367    9a
    byte                TPBandwidth;                 //367    9a
    byte                TPLPHPStream;                //367    9a
    dword               TPFrequency;                 //13467  89a
    word                TPSymbolRate;                //14     8
    word                TPTSID;                      //13467  89a
    word                TPOriginalNetworkID;         //3467   89a
    word                TPNetworkID;                 //367    9a
    byte                TPClockSync;                 //       8
    byte                TPUnknown1[4];               //       89a
    byte                TPUnknown2;                  //367    89a
    byte                TPUnknown3[2];               //1
    byte                TPUnknown4;                  //367    9a
    byte                TPUnknown5[2];               //1
    byte                TPUnknown6;                  //4
    byte                TPUnknown7[8];               //6

    dword               EventDuration;               //13467  89a
    dword               EventEventID;                //13467  89a
    dword               EventStartTime;              //13467  89a
    dword               EventEndTime;                //13467  89a
    byte                EventRunningStatus;          //13467  89a
    byte                EventParentalRate;           //13467  89a
    char                EventEventName[273];         //13467  89a
    char                EventEventDescription[273];  //13467  89a
    word                EventServiceID;              //13467
    byte                EventUnknown1[2];            //13467  89a
    byte                EventUnknown2[14];           //13467

    word                ExtEventServiceID;           //13467  89a
    dword               ExtEventEventID;             //13467  89a
    word                ExtEventTextLength;          //13467  89a
    char                ExtEventText[1024];          //13467  89a
    byte                ExtEventUnknown1[6];         //
    byte                ExtEventUnknown2[2];         //13467

    byte                CryptFlag;                   //13467  89a
    byte                CryptUnknown1[4];           //13467
    byte                CryptUnknown2[3];           //13467

    dword               NrBookmarks;                 //13467
    dword               Bookmark[177];               //13467  89a
    dword               Resume;                      //13467  89a
  } tRECHeaderInfo;

  char  *GetRecExtension(void);
  bool   HDD_DecodeRECHeader(byte *Buffer, tRECHeaderInfo *RECHeaderInfo, SYSTEM_TYPE SystemType);
  bool   HDD_EncodeRECHeader(byte *Buffer, tRECHeaderInfo *RECHeaderInfo, SYSTEM_TYPE SystemType);
  int    HDD_FindPCR(byte *pBuffer, dword BufferSize, word PID);   //Returns the PCR in minutes
  byte  *HDD_GetPvrRecTsInfoPointer(byte Slot);
  bool   HDD_GetRecSlotFiles(byte Slot, TYPE_File **RecFile, TYPE_File **InfFile, TYPE_File **NavFile);
  bool   HDD_isAnyRecording(void);
  bool   HDD_isCryptedStream(char *Buffer, dword BufferSize);
  bool   HDD_isRecording(byte RecSlot);
  char  *HDD_MakeNewRecName(char *fname, word sequence);
  dword  HDD_NumberOfRECSlots(void);

  bool   HDD_RecSlotDecode(byte Slot, tFlashTimer *RecSlot);
  bool   HDD_RecSlotEncode(byte Slot, tFlashTimer *RecSlot);    //The buffer needs to be at least 8kB in size
  bool   HDD_RECSlotSetDuration(byte Slot, word Duration);

  /*****************************************************************************************************************************/
  /* Shutdown                                                                                                                  */
  /*****************************************************************************************************************************/

  typedef enum
  {
    TaskPlayback   = 0xe601,
    TaskRecordings = 0xe602,
    TaskVideo      = 0xe503,
    TaskAudio      = 0xe603,
    TaskPower      = 0xef00
  } TaskEnum;

  bool Shutdown(TaskEnum Task);
  bool Reboot(bool StopRecordings);
  bool SDS(void);
  void SDSTerminate(void);


  /*****************************************************************************************************************************/
  /* Strings                                                                                                                   */
  /*****************************************************************************************************************************/

  typedef enum
  {
    ControlChars         = 1,
    LFChars              = 2,
    InvalidFileNameChars = 4,
    NonPrintableChars    = 8
  } eRemoveChars;

  byte    CharToISO(byte *p);
  dword   CharToUTF8(byte *p);
  void    DeleteAt(char *SourceString, int Pos, int Len);
  void    ExtractLine(char *Text, char *Line);
  size_t  GetLine(char *data, bool strip);
  void    InsertAt(char *SourceString, int Pos, char *NewString);
  bool    isUTF8Char(byte *p);
  void    LowerCase(char *string);
  void    MakeValidFileName(char *strName, eRemoveChars ControlCharacters);
  char   *ParseLine(char *zeile, size_t *n, char delim);
  void    ReplaceInvalidFileNameChars(char *strName);
  char   *RTrim(char *s);
  void    SeparatePathComponents(char *FullName, char *Path, char *FileName, char *FileExt);
  bool    StringEndsWith(char *text, char *postfix);
  void    StrToISO(byte *SourceString, byte *DestString);
  void    StrToUTF8(byte *SourceString, byte *DestString);
  bool    StrMkISO(byte *SourceString);
  bool    StrMkUTF8(byte *SourceString);
  bool    StrReplace(char *String, char *Find, char *Replace);
  void    UpperCase(char *string);
  char   *ValidFileName(char *strName, eRemoveChars ControlCharacters);


  /*****************************************************************************************************************************/
  /* String database                                                                                                           */
  /*****************************************************************************************************************************/

  typedef struct
  {
    dword                 DBSize;
    char                 *DB;
    char                 *DBPtr;
    char                 *DBEnd;
  } tStringDB;

  bool  StringDBInit(tStringDB *StringDB, dword InitialSize);
  char *StringDBGet(tStringDB *StringDB, dword Index);
  dword StringDBAdd(tStringDB *StringDB, char *Text);
  int   StringDBCountRecords(tStringDB *StringDB);
  dword StringDBCurrent(tStringDB *StringDB);
  dword StringDBFirst(tStringDB *StringDB);
  dword StringDBNext(tStringDB *StringDB);
  dword StringDBPrev(tStringDB *StringDB);
  bool  StringDBDel(tStringDB *StringDB);
  bool  StringDBLoad(tStringDB *StringDB, char *FileName);
  bool  StringDBLoadFromFile(tStringDB *StringDB, TYPE_File *f);
  bool  StringDBSave(tStringDB *StringDB, char *FileName);
  bool  StringDBSaveToFile(tStringDB *StringDB, TYPE_File *f);
  bool  StringDBEOF(tStringDB *StringDB);
  bool  StringDBDestroy(tStringDB *StringDB);


  /*****************************************************************************************************************************/
  /* TAPs                                                                                                                      */
  /*****************************************************************************************************************************/

  typedef struct
  {
    dword                 Status; //1 = Running, 2 = TAP_Exit(); ???
    dword                 unknown1;
    TYPE_File             *file;
    dword                 unknown3;
    dword                 TAP_Main;
    dword                 TAP_EventHandler;
    dword                 unknown6;
    dword                 unknown7;
    dword                 unknown8;
    dword                 unknown9;
    tDirEntry            *CurrentDir;
  } tTMSTAPTaskTable; //44 Bytes * 16 TAPs = 704 bytes

  typedef struct
  {
    dword               TAPID;
    dword               Date;
    char                TAPName[64];
    char                Author[64];
    char                Description[128];
  } tTAPInfo;

  dword HDD_TAP_Callback(dword TAPID, void *ProcedureAddress, dword param1, dword param2, dword param3, dword param4);
  bool  HDD_TAP_Disable(dword TAPID, bool DisableEvents);
  dword HDD_TAP_DisableAll(bool DisableEvents);
  int   HDD_TAP_GetCurrentDir(char* CurrentDir);
  bool  HDD_TAP_GetFileNameByIndex(int Index, char **TAPFileName);
  dword HDD_TAP_GetIDByFileName(char *TAPFileName);
  dword HDD_TAP_GetIDByIndex(int TAPIndex);
  int   HDD_TAP_GetIndexByID(dword TAPID);
  bool  HDD_TAP_GetInfo(char *FileName, tTAPInfo *pTAPInfo);
  bool  HDD_TAP_GetInfoByAbsPath(char *AbsFileName, tTAPInfo *pTAPInfo);
  void* HDD_TAP_GetStartParameter(void);
  bool  HDD_TAP_PopDir(void);
  bool  HDD_TAP_PushDir(void);
  dword HDD_TAP_SendEvent(dword TAPID, bool AllowParamInterception, word event, dword param1, dword param2);
  dword HDD_TAP_Start(char *TAPFileName, bool BatchMode, void* ParameterBlock, dword *TAPID);
  bool  HDD_TAP_StartedByTAP(void);
  void  HDD_TAP_Terminate(dword TAPID);
  bool  HDD_TAP_isAnyRunning(void);
  bool  HDD_TAP_isBatchMode(void);
  dword HDD_TAP_isDisabled(dword TAPID);
  bool  HDD_TAP_isDisabledAll(void);
  bool  HDD_TAP_isRunning(dword TAPID);
  bool  KeyTranslate(bool Enable, void *EventHandler);
  bool  NoAutoStartTAP(void);


  /*****************************************************************************************************************************/
  /* TAP Comm                                                                                                                  */
  /*   Mainly developed by asrael                                                                                              */
  /*****************************************************************************************************************************/

  #define EVT_TAPCOM           0xFFF
  // Ergänzt die event codes in tap.h, da dort alle auf 00 enden, besteht die Hoffnung,
  // dass 0xFFF auch in zukünftigen API-Versionen nicht verwendet wird.

  // Die folgenden Konstanten werden in TAPCOM_OpenChannel und TAPCOM_GetChannel
  // verwendet, um die Anwendung zu identifizieren, für die eine Nachricht
  // bestimmt ist.

  #define TAPCOM_App_BROADCAST      0
  // Kann verwendet werden, um eine Nachricht an alle TAPs zu schicken, die TAPCOM
  // unterstützen.

  #define TAPCOM_NO_RETURN_VALUE 0x80000000


  typedef enum
  {
    TAPCOM_Status_OPEN,                   //Sobald der Block angelegt wird
    TAPCOM_Status_SERVER_NOT_AVAILABLE,   //Falls das Server-TAP nicht geladen ist (statt OPEN)
    TAPCOM_Status_ACKNOWLEDGED,           //Sobald der Server via ProcessEvent zugreift
    TAPCOM_Status_REJECTED,               //Dem Server unbekannter Befehl oder gerade nicht ausführbar
    TAPCOM_Status_FINISHED,               //Von Server abgeschlossen
    TAPCOM_Status_VERSIONMISMATCH,        //Die TAPCOM-Versionen des Servers und des Clients passen nicht zusammen
    TAPCOM_Status_NO_CHANNEL              //Keine gültige Verbindung
  } TAPCOM_Status;

  typedef void* TAPCOM_Channel;           // Zeiger, der intern als Kommunikationskanal verwendet wird


  //Client Funktionen

  TAPCOM_Channel TAPCOM_OpenChannel(      // setzt Remote Procedure Call an andere Anwendung ab

    dword TargetID,                       // ID der gewählten Anwendung (siehe oben)
    dword ServiceID,                      // Service-ID der gewählten Anwendung
    dword ParamBlockVersion,              // Version des Parameterblocks
    void *ParamBlock                      // Pointer auf die zu übertragenden Daten.

  );                                      // Rückgabewert: Pointer auf (internen) Kommunikationskanal. Dieser muss an die


  TAPCOM_Status TAPCOM_GetStatus(         // Liefert den Status des Kommunikationskanals

    TAPCOM_Channel Channel                // der von TAPCOM_OpenChannel zurückgegebene Kanal

  );                                      // Rückgabewert: Status des Kanals


  dword TAPCOM_LastAlive(                 // Liefert den Zeitpunkt der letzten Serveraktivität (siehe: TAPCOM_StillAlive)

    TAPCOM_Channel Channel                // der von TAPCOM_OpenChannel zurückgegebene Kanal

  );                                      // Rückgabewert: Tickcount der letzten Serveraktivität


  int TAPCOM_GetReturnValue(              // Kann vom Client aus aufgerufen werden, um abzufragen,
                                          // ob der Server den RPC ausgeführt oder zurückgewiesen hat.

    TAPCOM_Channel Channel                // der von TAPCOM_OpenChannel zurückgegebene Kanal

  );                                      // Rückgabewert: der vom Server gesetzte Rückgabewert


  void TAPCOM_CloseChannel(               // Kann vom Client aufgerufen werden, um Message-Puffer nach Abschluss der
                                          // Kommunikation freizugeben.

    TAPCOM_Channel Channel                // der von TAPCOM_OpenChannel zurückgegebene Kanal

  );


  //Server-Funktionen
  TAPCOM_Channel TAPCOM_GetChannel(       // Liefert Informationen über den vom Client gesendeten Befehl

    dword param1,                         // Wird vom Event geliefert und enthält die Adresse zum Messagebuffer
    dword *CallerID,                      // ID der aufrufenden Clients (siehe oben)
    dword *ServiceID,                     // ID des gewünschten Services, frei definierbar
    dword *ParamBlockVersion,             // Version des Parameterblocks
    void  **ParamBlock                    // Rückgabe der Adresse, an der eventuelle Parameter für den Service stehen

  );                                      // Rückgabewert: Pointer auf (internen) Kommunikationskanal.


  void TAPCOM_Reject(                     // Der Server kennt den Befehl nicht oder kann diesen gerade nicht abarbeiten

    TAPCOM_Channel Channel                // der von TAPCOM_GetChannel zurückgegebene Kanal

  );

  void TAPCOM_Finish(                     // Kann vom Server aus aufgerufen werden, um dem Client ein Ergebnis vom Typ int
                                          // des RPCs zu übermitteln.

    TAPCOM_Channel Channel,               // der von TAPCOM_GetChannel zurückgegebene Kanal
    int            val                    // der Rückgabewert vom Server

  );


  void TAPCOM_StillAlive(                 // Dauert die Befehlsverarbeitung länger, kann der Server dem Client mitteilen,
                                          // dass er noch aktiv ist (siehe: TAPCOM_LastAlive)

    TAPCOM_Channel Channel                // der von TAPCOM_GetChannel zurückgegebene Kanal

  );


  /*****************************************************************************************************************************/
  /* tapapifix                                                                                                                 */
  /*****************************************************************************************************************************/

  // missing items
  #define LAN_Persian           LAN_Iran
  #define LAN_Suomi             (LAN_Persian + 1)
  #define LAN_Slovak            (LAN_Persian + 2)
  #define LAN_Thai              (LAN_Persian + 3)
  #define LAN_Czech             (LAN_Persian + 4)
  #define LAN_Bulgarian         (LAN_Persian + 5)


  /*****************************************************************************************************************************/
  /* Time Functions                                                                                                            */
  /*****************************************************************************************************************************/

  #define DATE(mjd, h, m) ((dword) (((mjd) << 16) | ((h) << 8) | (m)))
  #define MJD(d) ((word) (((d) >> 16) & 0xffff))
  #define TIME(d) ((word) ((d) & 0xffff))
  #define HOUR(d) ((byte) (((d) >> 8) & 0xff))
  #define MINUTE(d) ((byte) ((d) & 0xff))

  dword  AddSec(dword date, byte dateSec, int add);
  dword  AddTime(dword date, int add);
  char  *DayOfWeek(byte WeekDay);
  bool   isMJD(dword MJD);
  dword  Now(byte *Sec);
  dword  TF2UnixTime(dword TFTimeStamp);
  long   TimeDiff(dword FromTime, dword ToTime);
  char  *TimeFormat(dword DateTime, byte Sec, eTimeStampFormat TimeStampFormat);
  dword  Unix2TFTime(dword UnixTimeStamp);
  dword  UTCtoLocal(dword UTCTime);


  /*****************************************************************************************************************************/
  /* TMS OSD Menu                                                                                                              */
  /*   Menu, dialog box and message box                                                                                        */
  /*****************************************************************************************************************************/

  typedef enum
  {
    CT_Standard,
    CT_Dark,
    CT_Box,
    CT_NRITEMS
  } tCursorType;

  //Main OSD
  void OSDMenuInitialize(bool AllowScrollingOfLongText, bool HasValueColumn, bool NumberedItems, bool ScrollLoop, char *TitleLeft, char *TitleRight);
  void OSDMenuSetFont(tFontData *LeftTitle, tFontData *RightTitle, tFontData *ListNumber, tFontData *ListName, tFontData *ListValue, tFontData *Buttons, tFontData *Memo);
  void OSDMenuSetCursor(tCursorType CursorType);
  void OSDMenuUpdate(bool SuppressOSDSync);
  void OSDMenuModifyTitleLeft(char *Text);
  void OSDMenuModifyTitleRight(char *Text);
  void OSDMenuModifyItemLongTextScrolling(bool AllowScrollingOfLongText);
  void OSDMenuModifyItemValueColumn(bool HasValueColumn);
  void OSDMenuModifyItemNumbered(bool NumberedItems);
  void OSDMenuModifyScrollLoop(bool ScrollLoop);
  void OSDMenuLogo(dword X, dword Y, TYPE_GrData *LogoGd);
  void OSDMenuDestroy(void);
  void OSDMenuDestroyNoOSDUpdate(void);
  bool OSDMenuIsVisible(void);

  //Callback function for custom menu drawings
  void OSDMenuSetCallback(void *OSDCallbackProcedure);

  //void OSDCallbackProcedure(tOSDCB OSDCBType, word OSDRgn);

  typedef enum
  {
    OSDCB_Title,
    OSDCB_List,
    OSDCB_Buttons,
    OSDCB_Logo
  } tOSDCB;


  //Buttons

  typedef enum
  {
    BI_None,
    BI_0,
    BI_1,
    BI_2,
    BI_3,
    BI_4,
    BI_5,
    BI_6,
    BI_7,
    BI_8,
    BI_9,
    BI_AR,
    BI_Audio,
    BI_Aux,
    BI_Blue,
    BI_Cut,
    BI_Down,
    BI_Exit,
    BI_Fav,
    BI_Ffwd,
    BI_FileList,
    BI_Green,
    BI_Guide,
    BI_Info,
    BI_JumpEnd,
    BI_JumpStart,
    BI_Left,
    BI_List,
    BI_M,
    BI_Menu,
    BI_Mute,
    BI_Ok,
    BI_Option,
    BI_Pause,
    BI_Play,
    BI_ProgMinus,
    BI_ProgPlus,
    BI_Recall,
    BI_Record,
    BI_Red,
    BI_Right,
    BI_Rwd,
    BI_Sat,
    BI_Select,
    BI_Sleep,
    BI_Step,
    BI_Stop,
    BI_Subtitle,
    BI_TTX,
    BI_TV_Radio,
    BI_Up,
    BI_VF,
    BI_VolMinus,
    BI_VolPlus,
    BI_White,
    BI_Yellow,
    BI_NoUse,
    BI_UserDefined
  } tButtonIcon;


  void OSDMenuButtonsClear(void);
  void OSDMenuButtonColor(dword Color);
  void OSDMenuButtonAdd(dword Line, tButtonIcon ButtonIcon, TYPE_GrData *ButtonGd, char *Text);

  //Cursor Functions
  bool  OSDMenuSelectItem(int ItemIndex);
  bool  OSDMenuSelectTopItem(int TopIndex);
  int   OSDMenuGetCurrentItem(void);
  dword OSDMenuItemGetTopIndex(void);
  int   OSDMenuScrollUp(void);
  int   OSDMenuScrollPageUp(void);
  int   OSDMenuScrollDown(void);
  int   OSDMenuScrollPageDown(void);
  int   OSDMenuScrollHome(void);
  int   OSDMenuScrollEnd(void);

  //Items
  void  OSDMenuItemsClear(void);
  bool  OSDMenuItemAdd(char *Name, char *Value, TYPE_GrData *pNameIconGd, TYPE_GrData *pValueIconGd, bool Selectable, bool ValueArrows, dword ID);
  bool  OSDMenuItemModifyName(int ItemIndex, char *Text);
  bool  OSDMenuItemModifyValue(int ItemIndex, char *Text);
  void  OSDMenuItemModifyValueXPos(dword NewValueXPos);
  bool  OSDMenuItemModifyNameIcon(int ItemIndex, TYPE_GrData *pNameIconGd);
  bool  OSDMenuItemModifyValueIcon(int ItemIndex, TYPE_GrData *pValueIconGd);
  bool  OSDMenuItemModifySelectable(int ItemIndex, bool Selectable);
  bool  OSDMenuItemModifyColorPatch(int ItemIndex, dword Color); //set to 0 to disable
  bool  OSDMenuItemModifyTextColor(int ItemIndex, dword Color);
  bool  OSDMenuItemModifyID(int ItemIndex, dword ID);
  char *OSDMenuItemGetValue(int ItemIndex);
  char *OSDMenuItemGetName(int ItemIndex);
  dword OSDMenuItemGetID(int ItemIndex);
  char *OSDMenuItemGetCurrentValue(void);
  char *OSDMenuItemGetCurrentName(void);
  dword OSDMenuItemGetCurrentID(void);
  dword OSDMenuItemGetNrOfItems(void);
  void  OSDMenuItemSortNameColumn(bool Ascending, bool CaseSensitive);
  void  OSDMenuItemSortValueColumn(bool Ascending, bool CaseSensitive);
  void  OSDMenuItemSortID(bool Ascending);
  int   OSDMenuItemFindName(char *Text);
  int   OSDMenuItemFindValue(char *Text);

  //Menu Stack
  bool OSDMenuPush(void);
  bool OSDMenuPop(void);
  void OSDMenuSaveMyRegion(word Rgn);

  //Memo
  void OSDMemoInitialize(bool ScrollLoop, char *TitleLeft, char *TitleRight, char *Text);

  //Info box
  void OSDMenuInfoBoxShow(char *Title, char *Text, dword Timeout);
  void OSDMenuInfoBoxDestroy(void);
  void OSDMenuInfoBoxDestroyNoOSDUpdate(void);
  bool OSDMenuInfoBoxIsVisible(void);

  //Message box
  void  OSDMenuMessageBoxInitialize(char *Title, char *Text);
  void  OSDMenuMessageBoxButtonAdd(char *Text);
  void  OSDMenuMessageBoxButtonSelect(dword SelectedButton);
  void  OSDMenuMessageBoxDoNotEnterNormalMode(bool DoNotEnterNormalMode);
  void  OSDMenuMessageBoxShow(void);
  void  OSDMenuMessageBoxDestroy(void);
  void  OSDMenuMessageBoxDestroyNoOSDUpdate(void);
  bool  OSDMenuMessageBoxIsVisible(void);
  dword OSDMenuMessageBoxLastButton(void);

  //Color Picker
  void  OSDMenuColorPickerShow(char *Title, dword DefaultColor);
  void  OSDMenuColorPickerDestroy(void);
  bool  OSDMenuColorPickerIsVisible(void);
  dword OSDMenuColorPickerColor(void);

  //Progress bar
  void OSDMenuProgressBarShow(char *Title, char *Text, dword Value, dword MaxValue, TYPE_GrData *DifferentProgressBar);
  void OSDMenuProgressBarDestroy(void);
  bool OSDMenuProgressBarIsVisible(void);

  //Event handling
  bool OSDMenuEvent(word *event, dword *param1, dword *param2);


  /*****************************************************************************************************************************/
  /* TMS OSD Keyboard                                                                                                          */
  /*****************************************************************************************************************************/

  void OSDMenuKeyboard_Setup(char *Titel, char *Variable, dword MaxLength);
  void OSDMenuKeyboard_LegendButton(dword Line, tButtonIcon ButtonIcon, char *Text);
  bool OSDMenuKeyboard_EventHandler(word *event, dword *param1, dword *param2);
  void OSDMenuKeyboard_Destroy(void);


  /*****************************************************************************************************************************/
  /* TMS VFD Routines                                                                                                          */
  /*****************************************************************************************************************************/

  typedef enum
  {
    VFD_AC3,
    VFD_AM,
    VFD_Attn,
    VFD_CDCenter,
    VFD_Clock,
    VFD_Colon,
    VFD_Dolby,
    VFD_Dollar,
    VFD_FFwd,
    VFD_HDD,
    VFD_HDDFull,
    VFD_JumpStart,
    VFD_JumpEnd,
    VFD_MP3,
    VFD_Mute,
    VFD_Network,
    VFD_Pause,
    VFD_Play,
    VFD_PM,
    VFD_Power,
    VFD_Radio,
    VFD_REC,
    VFD_Slot1,
    VFD_Slot2,
    VFD_RepeatLeft,
    VFD_RepeatRight,
    VFD_Rwd,
    VFD_Satellite,
    VFD_TimeShift,
    VFD_TV
  } tVFDIcon;

  typedef enum
  {
    CS_8859_1,
    CS_8859_5,
    CS_8859_1_HAPPY
  } tVFDCharset;

  bool VFD_GetControl(bool GiveControl);
  bool VFD_isInUseByTAP(void);
  bool VFD_Clear(void);
  bool VFD_SetLargeText(char *Text);
  bool VFD_SetSmallText(char *Text);
  bool VFD_Update(void);
  bool VFD_EnableCD(bool Enable);
  bool VFD_SetCDValue(int Percent);
  bool VFD_EnableHDD(bool Enable);
  bool VFD_SetHDDValue(int Percent);
  bool VFD_SetIcon(tVFDIcon VFDIcon, bool On);
  bool VFD_EnableCDAnimation(bool Enable);
  bool VFD_CDAnimation(bool Forward);
  bool VFD_SetCharacterSet(tVFDCharset VFDCharset);

  /*****************************************************************************************************************************/
  /* USB Keyboard                                                                                                              */
  /*****************************************************************************************************************************/

  #define EVT_USBKEYBOARD   0x0ffe

  #define EVT_TMSREMOTEASCII 0x0ffd

  /*****************************************************************************************************************************/
  /* MIPS OpCodes                                                                                                              */
  /*****************************************************************************************************************************/

  #define REL_ADDR(x)     (((dword)(x) & 0x0fffffff) >> 2)
  #define ABS_ADDR(x)     (((x & JMP_ADDRMASK) << 2) | 0x80000000)

  #define ADD_SP_CMD      0x27BD0000
  #define ADD_SP_MASK     0xFFFF0000
  #define ADDIU_A0_CMD    0x24040000
  #define ADDIU_GP_CMD    0x279C0000
  #define ADDIU_S1_CMD    0x24110000
  #define ADDIU_CMD       0x24000000
  #define BASE_MASK       0xFFE00000
  #define CMD_MASK        0xFC000000
  #define JAL_CMD         0x0C000000
  #define JMP_ADDRMASK    0x03FFFFFF
  #define JMP_CMD         0x08000000
  #define JR_RA_CMD       0x03E00008
  #define LBU_CMD         0x90000000
  #define LUI_A0_CMD      0x3c040000
  #define LUI_A1_CMD      0x3C050000
  #define LUI_A2_CMD      0x3C060000
  #define LUI_CMD         0x3C000000
  #define LUI_GP_CMD      0x3C1C0000
  #define LUI_S0_CMD      0x3C100000
  #define LUI_S1_CMD      0x3C110000
  #define LUI_S3_CMD      0x3C130000
  #define LUI_S4_CMD      0x3C140000
  #define LUI_S6_CMD      0x3C160000
  #define LUI_T0_CMD      0x3C080000
  #define LUI_T1_CMD      0x3C090000
  #define LUI_T8_CMD      0x3C180000
  #define LUI_T9_CMD      0x3C190000
  #define LW_GP_CMD       0x8F800000
  #define LW_S7T9_CMD     0x8F370000
  #define LW_T1_SP_CMD    0x8FA90000
  #define MOVE_A0_48      0x24040030
  #define MOVE_A0_CMD     0x34040000
  #define MOVE_A2_48      0x24060030
  #define MOVE_T9_RA      0x03E02020
  #define NOP_CMD         0x00000000
  #define OR_A1_CMD       0x34A50000
  #define OR_T8_CMD       0x37180000
  #define ORI_A0_CMD      0x34840000
  #define ORI_A1_CMD      0x34A50000
  #define ORI_A2_CMD      0x34C60000
  #define ORI_GP_CMD      0x379C0000
  #define ORI_S0_CMD      0x36100000
  #define ORI_S1_CMD      0x36310000
  #define ORI_S3_CMD      0x36730000
  #define ORI_S4_CMD      0x36940000
  #define ORI_S6_CMD      0x36D60000
  #define ORI_T0_CMD      0x35080000
  #define ORI_T1_CMD      0x35290000
  #define REG_MASK        0x03FF0000
  #define SB_0_GP_CMD     0xA3800000
  #define SW_RA_SP_CMD    0xAFBF0000
  #define SW_S5T9_CMD     0xAF350000
  #define SW_S7T9_CMD     0xAF370000

  #ifdef __cplusplus
    }
  #endif
#endif
