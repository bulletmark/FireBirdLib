#ifndef __FBLIB__
  #define __FBLIB__

  //#define STACKTRACE

  #define __FBLIB_RELEASEDATE__ "2014-11-09"

  #define __FBLIB_VERSION__ __FBLIB_RELEASEDATE__

  #define isTMS         1

  #ifdef PC_BASED
    #define inline
    #define __attribute__(a)
  #else
    #include "tap.h"
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
  {                         //Toppy has been bootet by...
    BOOT_FRONT_PANEL,       //... pressing a front panel key
    BOOT_REMOTE_CONTROL,    //... a remote key
    BOOT_TIMER,             //... a timer
    BOOT_FW_REBOOT,         //... Firmware controlled reboot
    BOOT_RESERVED_4,        //... unknown. Possibly used by the front panel, but never seen
    BOOT_POWER,             //... an mains power failure.
    BOOT_ANTIFREEZE         //... an AntiFreeze reboot. Patched front panels only
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
    RT_7100PLUS,
    RT_7260PLUS       //Identical to RT_2100, except that the code for the red key is RKEY_F1
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
  #endif

  bool        InitTAPex(void);
  void        InitTAPexFailedMsg(char *ProgramName);
  tBootReason BootReason(void);
  dword       FirmwareDatMJD(void);
  void        FlushCache(dword *pAddr, int Size);
  bool        FrontPanelEEPROMRead(word Address, byte *Data);   //Only supported with a patched front panel
  bool        FrontPanelEEPROMWrite(word Address, byte Data);   //Only supported with a patched front panel
  bool        FrontPanelGetPatch(byte *Version, byte *Type);
  char       *GetApplVer(void);
  byte       *GetMacAddress(void);
  word        GetSysID(void);
  SYSTEM_TYPE GetSystemType(void);
  char       *GetToppyString(word SysID);
  dword       GetUptime(void);
  bool        isIceTVToppy(void);
  char       *iso639_1(int OSDLan);
  char       *iso639_2(int OSDLan);
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

  //In addition to the Service Status Mask defined in tap.h
  #define SVCSTATUS_MASK_Audio    0x00010000

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
    word                x;
    word                y;
    word                Width;
    word                Height;
    dword               pMemoryOSD;
    byte                byteFormat;
    byte                lutIdx;
    byte                plane;
    byte                unknown;
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
    PLT_Unchanged     = 0,
    PLT_DataFiles     = 1,
    PLT_ProgramFiles  = 2,
    PLT_MP3Files      = 3,
    PLT_MediaFiles    = 4,
  } tPvrListType;

  tAudioTrk *AudioTrackInfo(void);
  bool  CaptureScreen(int BMPwidth, int BMPheight, byte *BMPPixelBuffer, bool bOSD, int Alpha);
  void  DrawOSDLine(word OSDRgn, dword Ax, dword Ay, dword Bx, dword By, dword Color);
  void  DrawScrollbar(word sbRegion, int sbX, int sbY, int sbHeight, int sbCurrent, int sbWindow, int sbMax);
  void  EndMessageWin(void);
  void  FreeOSDRegion(word Region);
  dword GetOSDMapAddress(void);
  word  GetOSDRegionHeight(word Region);
  word  GetOSDRegionWidth(word Region);
  bool  GetPIPPosition(int *North, int *South, int *East, int *West);
  byte  GetStreamFormat(byte Index);
  bool  isAnyOSDVisible(dword CheckX, dword CheckY, dword CheckW, dword CheckH);
  bool  isAnyOSDVisibleEx(dword CheckX, dword CheckY, dword CheckW, dword CheckH, byte Plane);
  bool  isInfoBoxVisible(void);
  bool  isDirectSvcNumVisible(void);
  bool  isOSDRegionAlive(word Region);
  bool  isPIPActive(void);
  void  OSDCopy(word rgn, dword x, dword y, dword w, dword h, word items, eCopyDirection direction);
  bool  PlayMediaFile(char *MediaFileName);
  bool  SaveBitmap(char *FileName, int width, int height, byte* pBuffer);
  void  SetRemoteMode(byte Mode, byte Index, bool Active);
  void  ShowMessageWin(char* title, char* lpMessage1, char* lpMessage2, dword dwDelay);
  void  ShowMessageWindow(char **content, dword pos_x, dword pos_y, byte fntSize, byte align, dword bdcolor, dword titlecolor, dword msgcolor, dword bgcolor, dword delay);
  bool  ShowPvrList(tPvrListType PvrListType);
  void  SoundSinus(word freq, dword durationInMilliseconds, word Amplitude);
  bool  TAP_GetSysOsdControl(TYPE_TapSysOsdId osdId);
  int   TAP_Osd_PutFreeColorGd(word rgn, int x, int y, TYPE_GrData *gd, bool sprite, dword FilterColor);
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
  dword OATH(register byte *data, int len, dword hash);
  dword SuperFastHash(register byte *data, int len, dword hash);
  word  UncompressBlock(byte *pInput, word compCount, byte *pOutput, word BufferSize);
  dword UncompressLoader(byte *pSrc, byte *pDest, void *pPercentFinishedCallback);
  dword UncompressedLoaderSize(byte *pSrc);
  dword UncompressFirmware(byte *pSrc, byte *pDest, void *pPercentFinishedCallback);
  dword UncompressedFirmwareSize(byte *pSrc);
  dword UncompressTFD(byte *pSrc, byte *pDest, void *pPercentFinishedCallback);
  dword UncompressedTFDSize(byte *pSrc);
  dword TFDSize(byte *pTFD);


  /*****************************************************************************************************************************/
  /* curl                                                                                                                      */
  /*****************************************************************************************************************************/

  typedef enum
  {
    CURLE_OK = 0,
    CURLE_UNSUPPORTED_PROTOCOL,    /* 1 */
    CURLE_FAILED_INIT,             /* 2 */
    CURLE_URL_MALFORMAT,           /* 3 */
    CURLE_NOT_BUILT_IN,            /* 4 -  [was obsoleted in August 2007 for 7.17.0, reused in                                            April 2011 for 7.21.5] */
    CURLE_COULDNT_RESOLVE_PROXY,   /* 5 */
    CURLE_COULDNT_RESOLVE_HOST,    /* 6 */
    CURLE_COULDNT_CONNECT,         /* 7 */
    CURLE_FTP_WEIRD_SERVER_REPLY,  /* 8 */
    CURLE_REMOTE_ACCESS_DENIED,    /* 9 -  a service was denied by the server
                                           due to lack of access - when login fails
                                           this is not returned. */
    CURLE_FTP_ACCEPT_FAILED,       /* 10 - [was obsoleted in April 2006 for 7.15.4, reused in Dec 2011 for 7.24.0]*/
    CURLE_FTP_WEIRD_PASS_REPLY,    /* 11 */
    CURLE_FTP_ACCEPT_TIMEOUT,      /* 12 - timeout occurred accepting server
                                           [was obsoleted in August 2007 for 7.17.0,
                                           reused in Dec 2011 for 7.24.0]*/
    CURLE_FTP_WEIRD_PASV_REPLY,    /* 13 */
    CURLE_FTP_WEIRD_227_FORMAT,    /* 14 */
    CURLE_FTP_CANT_GET_HOST,       /* 15 */
    CURLE_OBSOLETE16,              /* 16 - NOT USED */
    CURLE_FTP_COULDNT_SET_TYPE,    /* 17 */
    CURLE_PARTIAL_FILE,            /* 18 */
    CURLE_FTP_COULDNT_RETR_FILE,   /* 19 */
    CURLE_OBSOLETE20,              /* 20 - NOT USED */
    CURLE_QUOTE_ERROR,             /* 21 - quote command failure */
    CURLE_HTTP_RETURNED_ERROR,     /* 22 */
    CURLE_WRITE_ERROR,             /* 23 */
    CURLE_OBSOLETE24,              /* 24 - NOT USED */
    CURLE_UPLOAD_FAILED,           /* 25 - failed upload "command" */
    CURLE_READ_ERROR,              /* 26 - couldn't open/read from file */
    CURLE_OUT_OF_MEMORY,           /* 27 */
    /* Note: CURLE_OUT_OF_MEMORY may sometimes indicate a conversion error
             instead of a memory allocation error if CURL_DOES_CONVERSIONS
             is defined */
    CURLE_OPERATION_TIMEDOUT,      /* 28 - the timeout time was reached */
    CURLE_OBSOLETE29,              /* 29 - NOT USED */
    CURLE_FTP_PORT_FAILED,         /* 30 - FTP PORT operation failed */
    CURLE_FTP_COULDNT_USE_REST,    /* 31 - the REST command failed */
    CURLE_OBSOLETE32,              /* 32 - NOT USED */
    CURLE_RANGE_ERROR,             /* 33 - RANGE "command" didn't work */
    CURLE_HTTP_POST_ERROR,         /* 34 */
    CURLE_SSL_CONNECT_ERROR,       /* 35 - wrong when connecting with SSL */
    CURLE_BAD_DOWNLOAD_RESUME,     /* 36 - couldn't resume download */
    CURLE_FILE_COULDNT_READ_FILE,  /* 37 */
    CURLE_LDAP_CANNOT_BIND,        /* 38 */
    CURLE_LDAP_SEARCH_FAILED,      /* 39 */
    CURLE_OBSOLETE40,              /* 40 - NOT USED */
    CURLE_FUNCTION_NOT_FOUND,      /* 41 */
    CURLE_ABORTED_BY_CALLBACK,     /* 42 */
    CURLE_BAD_FUNCTION_ARGUMENT,   /* 43 */
    CURLE_OBSOLETE44,              /* 44 - NOT USED */
    CURLE_INTERFACE_FAILED,        /* 45 - CURLOPT_INTERFACE failed */
    CURLE_OBSOLETE46,              /* 46 - NOT USED */
    CURLE_TOO_MANY_REDIRECTS ,     /* 47 - catch endless re-direct loops */
    CURLE_UNKNOWN_OPTION,          /* 48 - User specified an unknown option */
    CURLE_TELNET_OPTION_SYNTAX ,   /* 49 - Malformed telnet option */
    CURLE_OBSOLETE50,              /* 50 - NOT USED */
    CURLE_PEER_FAILED_VERIFICATION, /* 51 - peer's certificate or fingerprint wasn't verified fine */
    CURLE_GOT_NOTHING,             /* 52 - when this is a specific error */
    CURLE_SSL_ENGINE_NOTFOUND,     /* 53 - SSL crypto engine not found */
    CURLE_SSL_ENGINE_SETFAILED,    /* 54 - can not set SSL crypto engine as default */
    CURLE_SEND_ERROR,              /* 55 - failed sending network data */
    CURLE_RECV_ERROR,              /* 56 - failure in receiving network data */
    CURLE_OBSOLETE57,              /* 57 - NOT IN USE */
    CURLE_SSL_CERTPROBLEM,         /* 58 - problem with the local certificate */
    CURLE_SSL_CIPHER,              /* 59 - couldn't use specified cipher */
    CURLE_SSL_CACERT,              /* 60 - problem with the CA cert (path?) */
    CURLE_BAD_CONTENT_ENCODING,    /* 61 - Unrecognized/bad encoding */
    CURLE_LDAP_INVALID_URL,        /* 62 - Invalid LDAP URL */
    CURLE_FILESIZE_EXCEEDED,       /* 63 - Maximum file size exceeded */
    CURLE_USE_SSL_FAILED,          /* 64 - Requested FTP SSL level failed */
    CURLE_SEND_FAIL_REWIND,        /* 65 - Sending the data requires a rewind that failed */
    CURLE_SSL_ENGINE_INITFAILED,   /* 66 - failed to initialise ENGINE */
    CURLE_LOGIN_DENIED,            /* 67 - user, password or similar was not accepted and we failed to login */
    CURLE_TFTP_NOTFOUND,           /* 68 - file not found on server */
    CURLE_TFTP_PERM,               /* 69 - permission problem on server */
    CURLE_REMOTE_DISK_FULL,        /* 70 - out of disk space on server */
    CURLE_TFTP_ILLEGAL,            /* 71 - Illegal TFTP operation */
    CURLE_TFTP_UNKNOWNID,          /* 72 - Unknown transfer ID */
    CURLE_REMOTE_FILE_EXISTS,      /* 73 - File already exists */
    CURLE_TFTP_NOSUCHUSER,         /* 74 - No such user */
    CURLE_CONV_FAILED,             /* 75 - conversion failed */
    CURLE_CONV_REQD,               /* 76 - caller must register conversion
                                      callbacks using curl_easy_setopt options
                                      CURLOPT_CONV_FROM_NETWORK_FUNCTION,
                                      CURLOPT_CONV_TO_NETWORK_FUNCTION, and
                                      CURLOPT_CONV_FROM_UTF8_FUNCTION */
    CURLE_SSL_CACERT_BADFILE,      /* 77 - could not load CACERT file, missing or wrong format */
    CURLE_REMOTE_FILE_NOT_FOUND,   /* 78 - remote file not found */
    CURLE_SSH,                     /* 79 - error from the SSH layer, somewhat
                                      generic so the error message will be of
                                      interest when this has happened */

    CURLE_SSL_SHUTDOWN_FAILED,     /* 80 - Failed to shut down the SSL connection */
    CURLE_AGAIN,                   /* 81 - socket is not ready for send/recv,
                                      wait till it's ready and try again (Added
                                      in 7.18.2) */
    CURLE_SSL_CRL_BADFILE,         /* 82 - could not load CRL file, missing or wrong format (Added in 7.19.0) */
    CURLE_SSL_ISSUER_ERROR,        /* 83 - Issuer check failed.  (Added in 7.19.0) */
    CURLE_FTP_PRET_FAILED,         /* 84 - a PRET command failed */
    CURLE_RTSP_CSEQ_ERROR,         /* 85 - mismatch of RTSP CSeq numbers */
    CURLE_RTSP_SESSION_ERROR,      /* 86 - mismatch of RTSP Session Ids */
    CURLE_FTP_BAD_FILE_LIST,       /* 87 - unable to parse FTP file list */
    CURLE_CHUNK_FAILED,            /* 88 - chunk callback reported error */
    CURL_LAST /* never use! */
  } CURLcode;

  /* long may be 32 or 64 bits, but we should never depend on anything else but 32 */
  #define CURLOPTTYPE_LONG          0
  #define CURLOPTTYPE_OBJECTPOINT   10000
  #define CURLOPTTYPE_FUNCTIONPOINT 20000
  #define CURLOPTTYPE_OFF_T         30000

  #define CINIT(na,t,nu) CURLOPT_ ## na = CURLOPTTYPE_ ## t + nu
  //#define CINIT(name,type,number) CURLOPT_/**/name = type + number
  /*
   * This macro-mania below setups the CURLOPT_[what] enum, to be used with
   * curl_easy_setopt(). The first argument in the CINIT() macro is the [what]
   * word.
   */

  typedef enum
  {
    CINIT(FILE, OBJECTPOINT, 1),              /* This is the FILE * or void * the regular output should be written to. */
    CINIT(URL,  OBJECTPOINT, 2),              /* The full URL to get/put */
    CINIT(PORT, LONG, 3),                     /* Port number to connect to, if other than default. */
    CINIT(PROXY, OBJECTPOINT, 4),             /* Name of proxy to use. */
    CINIT(USERPWD, OBJECTPOINT, 5),           /* "name:password" to use when fetching. */
    CINIT(PROXYUSERPWD, OBJECTPOINT, 6),      /* "name:password" to use with proxy. */
    CINIT(RANGE, OBJECTPOINT, 7),             /* Range to get, specified as an ASCII string. */
                                              /* not used */
    CINIT(INFILE, OBJECTPOINT, 9),            /* Specified file stream to upload from (use as input): */
    CINIT(ERRORBUFFER, OBJECTPOINT, 10),      /* Buffer to receive error messages in, must be at least CURL_ERROR_SIZE bytes big. If this is not used,
                                                 error messages go to stderr instead: */
    CINIT(WRITEFUNCTION, FUNCTIONPOINT, 11),  /* Function that will be called to store the output (instead of fwrite). The parameters will use
                                                 fwrite() syntax, make sure to follow them. */
    CINIT(READFUNCTION, FUNCTIONPOINT, 12),   /* Function that will be called to read the input (instead of fread). The parameters will use fread()
                                                 syntax, make sure to follow them. */
    CINIT(TIMEOUT, LONG, 13),                 /* Time-out the read operation after this amount of seconds */

    /* If the CURLOPT_INFILE is used, this can be used to inform libcurl about
     * how large the file being sent really is. That allows better error
     * checking and better verifies that the upload was successful. -1 means
     * unknown size.
     *
     * For large file support, there is also a _LARGE version of the key
     * which takes an off_t type, allowing platforms with larger off_t
     * sizes to handle larger files.  See below for INFILESIZE_LARGE.
     */

    CINIT(INFILESIZE, LONG, 14),
    CINIT(POSTFIELDS, OBJECTPOINT, 15),       /* POST static input fields. */
    CINIT(REFERER, OBJECTPOINT, 16),          /* Set the referrer page (needed by some CGIs) */
    CINIT(FTPPORT, OBJECTPOINT, 17),          /* Set the FTP PORT string (interface name, named or numerical IP address) Use i.e '-' to use default address. */
    CINIT(USERAGENT, OBJECTPOINT, 18),        /* Set the User-Agent string (examined by some CGIs) */

    /* If the download receives less than "low speed limit" bytes/second
     * during "low speed time" seconds, the operations is aborted.
     * You could i.e if you have a pretty high speed connection, abort if
     * it is less than 2000 bytes/sec during 20 seconds.
     */

    CINIT(LOW_SPEED_LIMIT, LONG, 19),         /* Set the "low speed limit" */
    CINIT(LOW_SPEED_TIME, LONG, 20),          /* Set the "low speed time" */
    CINIT(RESUME_FROM, LONG, 21),             /* Set the continuation offset.
                                                 Note there is also a _LARGE version of this key which uses
                                                 off_t types, allowing for large file offsets on platforms which
                                                 use larger-than-32-bit off_t's.  Look below for RESUME_FROM_LARGE. */
    CINIT(COOKIE, OBJECTPOINT, 22),           /* Set cookie in request: */
    CINIT(HTTPHEADER, OBJECTPOINT, 23),       /* This points to a linked list of headers, struct curl_slist kind */
    CINIT(HTTPPOST, OBJECTPOINT, 24),         /* This points to a linked list of post entries, struct curl_httppost */
    CINIT(SSLCERT, OBJECTPOINT, 25),          /* name of the file keeping your private SSL-certificate */
    CINIT(KEYPASSWD, OBJECTPOINT, 26),        /* password for the SSL or SSH private key */
    CINIT(CRLF, LONG, 27),                    /* send TYPE parameter? */
    CINIT(QUOTE, OBJECTPOINT, 28),            /* send linked-list of QUOTE commands */

    /* send FILE * or void * to store headers to, if you use a callback it
       is simply passed to the callback unmodified */
    CINIT(WRITEHEADER, OBJECTPOINT, 29),

    /* point to a file to read the initial cookies from, also enables
       "cookie awareness" */
    CINIT(COOKIEFILE, OBJECTPOINT, 31),

    /* What version to specifically try to use.
       See CURL_SSLVERSION defines below. */
    CINIT(SSLVERSION, LONG, 32),

    /* What kind of HTTP time condition to use, see defines */
    CINIT(TIMECONDITION, LONG, 33),

    /* Time to use with the above condition. Specified in number of seconds
       since 1 Jan 1970 */
    CINIT(TIMEVALUE, LONG, 34),

    /* 35 = OBSOLETE */

    /* Custom request, for customizing the get command like
       HTTP: DELETE, TRACE and others
       FTP: to use a different list command
       */
    CINIT(CUSTOMREQUEST, OBJECTPOINT, 36),

    /* HTTP request, for odd commands like DELETE, TRACE and others */
    CINIT(STDERR, OBJECTPOINT, 37),

    /* 38 is not used */

    /* send linked-list of post-transfer QUOTE commands */
    CINIT(POSTQUOTE, OBJECTPOINT, 39),

    CINIT(WRITEINFO, OBJECTPOINT, 40), /* DEPRECATED, do not use! */

    CINIT(VERBOSE, LONG, 41),      /* talk a lot */
    CINIT(HEADER, LONG, 42),       /* throw the header out too */
    CINIT(NOPROGRESS, LONG, 43),   /* shut off the progress meter */
    CINIT(NOBODY, LONG, 44),       /* use HEAD to get http document */
    CINIT(FAILONERROR, LONG, 45),  /* no output on http error codes >= 300 */
    CINIT(UPLOAD, LONG, 46),       /* this is an upload */
    CINIT(POST, LONG, 47),         /* HTTP POST method */
    CINIT(DIRLISTONLY, LONG, 48),  /* bare names when listing directories */

    CINIT(APPEND, LONG, 50),       /* Append instead of overwrite on upload! */

    /* Specify whether to read the user+password from the .netrc or the URL.
     * This must be one of the CURL_NETRC_* enums below. */
    CINIT(NETRC, LONG, 51),

    CINIT(FOLLOWLOCATION, LONG, 52),  /* use Location: Luke! */

    CINIT(TRANSFERTEXT, LONG, 53), /* transfer data in text/ASCII format */
    CINIT(PUT, LONG, 54),          /* HTTP PUT */

    /* 55 = OBSOLETE */

    /* Function that will be called instead of the internal progress display
     * function. This function should be defined as the curl_progress_callback
     * prototype defines. */
    CINIT(PROGRESSFUNCTION, FUNCTIONPOINT, 56),

    /* Data passed to the progress callback */
    CINIT(PROGRESSDATA, OBJECTPOINT, 57),

    /* We want the referrer field set automatically when following locations */
    CINIT(AUTOREFERER, LONG, 58),

    /* Port of the proxy, can be set in the proxy string as well with:
       "[host]:[port]" */
    CINIT(PROXYPORT, LONG, 59),

    /* size of the POST input data, if strlen() is not good to use */
    CINIT(POSTFIELDSIZE, LONG, 60),

    /* tunnel non-http operations through a HTTP proxy */
    CINIT(HTTPPROXYTUNNEL, LONG, 61),

    /* Set the interface string to use as outgoing network interface */
    CINIT(INTERFACE, OBJECTPOINT, 62),

    /* Set the krb4/5 security level, this also enables krb4/5 awareness.  This
     * is a string, 'clear', 'safe', 'confidential' or 'private'.  If the string
     * is set but doesn't match one of these, 'private' will be used.  */
    CINIT(KRBLEVEL, OBJECTPOINT, 63),

    /* Set if we should verify the peer in ssl handshake, set 1 to verify. */
    CINIT(SSL_VERIFYPEER, LONG, 64),

    /* The CApath or CAfile used to validate the peer certificate
       this option is used only if SSL_VERIFYPEER is true */
    CINIT(CAINFO, OBJECTPOINT, 65),

    /* 66 = OBSOLETE */
    /* 67 = OBSOLETE */

    /* Maximum number of http redirects to follow */
    CINIT(MAXREDIRS, LONG, 68),

    /* Pass a long set to 1 to get the date of the requested document (if
       possible)! Pass a zero to shut it off. */
    CINIT(FILETIME, LONG, 69),

    /* This points to a linked list of telnet options */
    CINIT(TELNETOPTIONS, OBJECTPOINT, 70),

    /* Max amount of cached alive connections */
    CINIT(MAXCONNECTS, LONG, 71),

    CINIT(CLOSEPOLICY, LONG, 72), /* DEPRECATED, do not use! */

    /* 73 = OBSOLETE */

    /* Set to explicitly use a new connection for the upcoming transfer.
       Do not use this unless you're absolutely sure of this, as it makes the
       operation slower and is less friendly for the network. */
    CINIT(FRESH_CONNECT, LONG, 74),

    /* Set to explicitly forbid the upcoming transfer's connection to be re-used
       when done. Do not use this unless you're absolutely sure of this, as it
       makes the operation slower and is less friendly for the network. */
    CINIT(FORBID_REUSE, LONG, 75),

    /* Set to a file name that contains random data for libcurl to use to
       seed the random engine when doing SSL connects. */
    CINIT(RANDOM_FILE, OBJECTPOINT, 76),

    /* Set to the Entropy Gathering Daemon socket pathname */
    CINIT(EGDSOCKET, OBJECTPOINT, 77),

    /* Time-out connect operations after this amount of seconds, if connects are
       OK within this time, then fine... This only aborts the connect phase. */
    CINIT(CONNECTTIMEOUT, LONG, 78),

    /* Function that will be called to store headers (instead of fwrite). The
     * parameters will use fwrite() syntax, make sure to follow them. */
    CINIT(HEADERFUNCTION, FUNCTIONPOINT, 79),

    /* Set this to force the HTTP request to get back to GET. Only really usable
       if POST, PUT or a custom request have been used first.
     */
    CINIT(HTTPGET, LONG, 80),

    /* Set if we should verify the Common name from the peer certificate in ssl
     * handshake, set 1 to check existence, 2 to ensure that it matches the
     * provided hostname. */
    CINIT(SSL_VERIFYHOST, LONG, 81),

    /* Specify which file name to write all known cookies in after completed
       operation. Set file name to "-" (dash) to make it go to stdout. */
    CINIT(COOKIEJAR, OBJECTPOINT, 82),

    /* Specify which SSL ciphers to use */
    CINIT(SSL_CIPHER_LIST, OBJECTPOINT, 83),

    /* Specify which HTTP version to use! This must be set to one of the
       CURL_HTTP_VERSION* enums set below. */
    CINIT(HTTP_VERSION, LONG, 84),

    /* Specifically switch on or off the FTP engine's use of the EPSV command. By
       default, that one will always be attempted before the more traditional
       PASV command. */
    CINIT(FTP_USE_EPSV, LONG, 85),

    /* type of the file keeping your SSL-certificate ("DER", "PEM", "ENG") */
    CINIT(SSLCERTTYPE, OBJECTPOINT, 86),

    /* name of the file keeping your private SSL-key */
    CINIT(SSLKEY, OBJECTPOINT, 87),

    /* type of the file keeping your private SSL-key ("DER", "PEM", "ENG") */
    CINIT(SSLKEYTYPE, OBJECTPOINT, 88),

    /* crypto engine for the SSL-sub system */
    CINIT(SSLENGINE, OBJECTPOINT, 89),

    /* set the crypto engine for the SSL-sub system as default
       the param has no meaning...
     */
    CINIT(SSLENGINE_DEFAULT, LONG, 90),

    /* Non-zero value means to use the global dns cache */
    CINIT(DNS_USE_GLOBAL_CACHE, LONG, 91), /* DEPRECATED, do not use! */

    /* DNS cache timeout */
    CINIT(DNS_CACHE_TIMEOUT, LONG, 92),

    /* send linked-list of pre-transfer QUOTE commands */
    CINIT(PREQUOTE, OBJECTPOINT, 93),

    /* set the debug function */
    CINIT(DEBUGFUNCTION, FUNCTIONPOINT, 94),

    /* set the data for the debug function */
    CINIT(DEBUGDATA, OBJECTPOINT, 95),

    /* mark this as start of a cookie session */
    CINIT(COOKIESESSION, LONG, 96),

    /* The CApath directory used to validate the peer certificate
       this option is used only if SSL_VERIFYPEER is true */
    CINIT(CAPATH, OBJECTPOINT, 97),

    /* Instruct libcurl to use a smaller receive buffer */
    CINIT(BUFFERSIZE, LONG, 98),

    /* Instruct libcurl to not use any signal/alarm handlers, even when using
       timeouts. This option is useful for multi-threaded applications.
       See libcurl-the-guide for more background information. */
    CINIT(NOSIGNAL, LONG, 99),

    /* Provide a CURLShare for mutexing non-ts data */
    CINIT(SHARE, OBJECTPOINT, 100),

    /* indicates type of proxy. accepted values are CURLPROXY_HTTP (default),
       CURLPROXY_SOCKS4, CURLPROXY_SOCKS4A and CURLPROXY_SOCKS5. */
    CINIT(PROXYTYPE, LONG, 101),

    /* Set the Accept-Encoding string. Use this to tell a server you would like
       the response to be compressed. Before 7.21.6, this was known as
       CURLOPT_ENCODING */
    CINIT(ACCEPT_ENCODING, OBJECTPOINT, 102),

    /* Set pointer to private data */
    CINIT(PRIVATE, OBJECTPOINT, 103),

    /* Set aliases for HTTP 200 in the HTTP Response header */
    CINIT(HTTP200ALIASES, OBJECTPOINT, 104),

    /* Continue to send authentication (user+password) when following locations,
       even when hostname changed. This can potentially send off the name
       and password to whatever host the server decides. */
    CINIT(UNRESTRICTED_AUTH, LONG, 105),

    /* Specifically switch on or off the FTP engine's use of the EPRT command (
       it also disables the LPRT attempt). By default, those ones will always be
       attempted before the good old traditional PORT command. */
    CINIT(FTP_USE_EPRT, LONG, 106),

    /* Set this to a bitmask value to enable the particular authentications
       methods you like. Use this in combination with CURLOPT_USERPWD.
       Note that setting multiple bits may cause extra network round-trips. */
    CINIT(HTTPAUTH, LONG, 107),

    /* Set the ssl context callback function, currently only for OpenSSL ssl_ctx
       in second argument. The function must be matching the
       curl_ssl_ctx_callback proto. */
    CINIT(SSL_CTX_FUNCTION, FUNCTIONPOINT, 108),

    /* Set the userdata for the ssl context callback function's third
       argument */
    CINIT(SSL_CTX_DATA, OBJECTPOINT, 109),

    /* FTP Option that causes missing dirs to be created on the remote server.
       In 7.19.4 we introduced the convenience enums for this option using the
       CURLFTP_CREATE_DIR prefix.
    */
    CINIT(FTP_CREATE_MISSING_DIRS, LONG, 110),

    /* Set this to a bitmask value to enable the particular authentications
       methods you like. Use this in combination with CURLOPT_PROXYUSERPWD.
       Note that setting multiple bits may cause extra network round-trips. */
    CINIT(PROXYAUTH, LONG, 111),

    /* FTP option that changes the timeout, in seconds, associated with
       getting a response.  This is different from transfer timeout time and
       essentially places a demand on the FTP server to acknowledge commands
       in a timely manner. */
    CINIT(FTP_RESPONSE_TIMEOUT, LONG, 112),
  #define CURLOPT_SERVER_RESPONSE_TIMEOUT CURLOPT_FTP_RESPONSE_TIMEOUT

    /* Set this option to one of the CURL_IPRESOLVE_* defines (see below) to
       tell libcurl to resolve names to those IP versions only. This only has
       affect on systems with support for more than one, i.e IPv4 _and_ IPv6. */
    CINIT(IPRESOLVE, LONG, 113),

    /* Set this option to limit the size of a file that will be downloaded from
       an HTTP or FTP server.

       Note there is also _LARGE version which adds large file support for
       platforms which have larger off_t sizes.  See MAXFILESIZE_LARGE below. */
    CINIT(MAXFILESIZE, LONG, 114),

    /* See the comment for INFILESIZE above, but in short, specifies
     * the size of the file being uploaded.  -1 means unknown.
     */
    CINIT(INFILESIZE_LARGE, OFF_T, 115),

    /* Sets the continuation offset.  There is also a LONG version of this;
     * look above for RESUME_FROM.
     */
    CINIT(RESUME_FROM_LARGE, OFF_T, 116),

    /* Sets the maximum size of data that will be downloaded from
     * an HTTP or FTP server.  See MAXFILESIZE above for the LONG version.
     */
    CINIT(MAXFILESIZE_LARGE, OFF_T, 117),

    /* Set this option to the file name of your .netrc file you want libcurl
       to parse (using the CURLOPT_NETRC option). If not set, libcurl will do
       a poor attempt to find the user's home directory and check for a .netrc
       file in there. */
    CINIT(NETRC_FILE, OBJECTPOINT, 118),

    /* Enable SSL/TLS for FTP, pick one of:
       CURLUSESSL_TRY     - try using SSL, proceed anyway otherwise
       CURLUSESSL_CONTROL - SSL for the control connection or fail
       CURLUSESSL_ALL     - SSL for all communication or fail
    */
    CINIT(USE_SSL, LONG, 119),

    /* The _LARGE version of the standard POSTFIELDSIZE option */
    CINIT(POSTFIELDSIZE_LARGE, OFF_T, 120),

    /* Enable/disable the TCP Nagle algorithm */
    CINIT(TCP_NODELAY, LONG, 121),

    /* 122 OBSOLETE, used in 7.12.3. Gone in 7.13.0 */
    /* 123 OBSOLETE. Gone in 7.16.0 */
    /* 124 OBSOLETE, used in 7.12.3. Gone in 7.13.0 */
    /* 125 OBSOLETE, used in 7.12.3. Gone in 7.13.0 */
    /* 126 OBSOLETE, used in 7.12.3. Gone in 7.13.0 */
    /* 127 OBSOLETE. Gone in 7.16.0 */
    /* 128 OBSOLETE. Gone in 7.16.0 */

    /* When FTP over SSL/TLS is selected (with CURLOPT_USE_SSL), this option
       can be used to change libcurl's default action which is to first try
       "AUTH SSL" and then "AUTH TLS" in this order, and proceed when a OK
       response has been received.

       Available parameters are:
       CURLFTPAUTH_DEFAULT - let libcurl decide
       CURLFTPAUTH_SSL     - try "AUTH SSL" first, then TLS
       CURLFTPAUTH_TLS     - try "AUTH TLS" first, then SSL
    */
    CINIT(FTPSSLAUTH, LONG, 129),

    CINIT(IOCTLFUNCTION, FUNCTIONPOINT, 130),
    CINIT(IOCTLDATA, OBJECTPOINT, 131),

    /* 132 OBSOLETE. Gone in 7.16.0 */
    /* 133 OBSOLETE. Gone in 7.16.0 */

    /* zero terminated string for pass on to the FTP server when asked for
       "account" info */
    CINIT(FTP_ACCOUNT, OBJECTPOINT, 134),

    /* feed cookies into cookie engine */
    CINIT(COOKIELIST, OBJECTPOINT, 135),

    /* ignore Content-Length */
    CINIT(IGNORE_CONTENT_LENGTH, LONG, 136),

    /* Set to non-zero to skip the IP address received in a 227 PASV FTP server
       response. Typically used for FTP-SSL purposes but is not restricted to
       that. libcurl will then instead use the same IP address it used for the
       control connection. */
    CINIT(FTP_SKIP_PASV_IP, LONG, 137),

    /* Select "file method" to use when doing FTP, see the curl_ftpmethod
       above. */
    CINIT(FTP_FILEMETHOD, LONG, 138),

    /* Local port number to bind the socket to */
    CINIT(LOCALPORT, LONG, 139),

    /* Number of ports to try, including the first one set with LOCALPORT.
       Thus, setting it to 1 will make no additional attempts but the first.
    */
    CINIT(LOCALPORTRANGE, LONG, 140),

    /* no transfer, set up connection and let application use the socket by
       extracting it with CURLINFO_LASTSOCKET */
    CINIT(CONNECT_ONLY, LONG, 141),

    /* Function that will be called to convert from the
       network encoding (instead of using the iconv calls in libcurl) */
    CINIT(CONV_FROM_NETWORK_FUNCTION, FUNCTIONPOINT, 142),

    /* Function that will be called to convert to the
       network encoding (instead of using the iconv calls in libcurl) */
    CINIT(CONV_TO_NETWORK_FUNCTION, FUNCTIONPOINT, 143),

    /* Function that will be called to convert from UTF8
       (instead of using the iconv calls in libcurl)
       Note that this is used only for SSL certificate processing */
    CINIT(CONV_FROM_UTF8_FUNCTION, FUNCTIONPOINT, 144),

    /* if the connection proceeds too quickly then need to slow it down */
    /* limit-rate: maximum number of bytes per second to send or receive */
    CINIT(MAX_SEND_SPEED_LARGE, OFF_T, 145),
    CINIT(MAX_RECV_SPEED_LARGE, OFF_T, 146),

    /* Pointer to command string to send if USER/PASS fails. */
    CINIT(FTP_ALTERNATIVE_TO_USER, OBJECTPOINT, 147),

    /* callback function for setting socket options */
    CINIT(SOCKOPTFUNCTION, FUNCTIONPOINT, 148),
    CINIT(SOCKOPTDATA, OBJECTPOINT, 149),

    /* set to 0 to disable session ID re-use for this transfer, default is
       enabled (== 1) */
    CINIT(SSL_SESSIONID_CACHE, LONG, 150),

    /* allowed SSH authentication methods */
    CINIT(SSH_AUTH_TYPES, LONG, 151),

    /* Used by scp/sftp to do public/private key authentication */
    CINIT(SSH_PUBLIC_KEYFILE, OBJECTPOINT, 152),
    CINIT(SSH_PRIVATE_KEYFILE, OBJECTPOINT, 153),

    /* Send CCC (Clear Command Channel) after authentication */
    CINIT(FTP_SSL_CCC, LONG, 154),

    /* Same as TIMEOUT and CONNECTTIMEOUT, but with ms resolution */
    CINIT(TIMEOUT_MS, LONG, 155),
    CINIT(CONNECTTIMEOUT_MS, LONG, 156),

    /* set to zero to disable the libcurl's decoding and thus pass the raw body
       data to the application even when it is encoded/compressed */
    CINIT(HTTP_TRANSFER_DECODING, LONG, 157),
    CINIT(HTTP_CONTENT_DECODING, LONG, 158),

    /* Permission used when creating new files and directories on the remote
       server for protocols that support it, SFTP/SCP/FILE */
    CINIT(NEW_FILE_PERMS, LONG, 159),
    CINIT(NEW_DIRECTORY_PERMS, LONG, 160),

    /* Set the behaviour of POST when redirecting. Values must be set to one
       of CURL_REDIR* defines below. This used to be called CURLOPT_POST301 */
    CINIT(POSTREDIR, LONG, 161),

    /* used by scp/sftp to verify the host's public key */
    CINIT(SSH_HOST_PUBLIC_KEY_MD5, OBJECTPOINT, 162),

    /* Callback function for opening socket (instead of socket(2)). Optionally,
       callback is able change the address or refuse to connect returning
       CURL_SOCKET_BAD.  The callback should have type
       curl_opensocket_callback */
    CINIT(OPENSOCKETFUNCTION, FUNCTIONPOINT, 163),
    CINIT(OPENSOCKETDATA, OBJECTPOINT, 164),

    /* POST volatile input fields. */
    CINIT(COPYPOSTFIELDS, OBJECTPOINT, 165),

    /* set transfer mode (;type=<a|i>) when doing FTP via an HTTP proxy */
    CINIT(PROXY_TRANSFER_MODE, LONG, 166),

    /* Callback function for seeking in the input stream */
    CINIT(SEEKFUNCTION, FUNCTIONPOINT, 167),
    CINIT(SEEKDATA, OBJECTPOINT, 168),

    /* CRL file */
    CINIT(CRLFILE, OBJECTPOINT, 169),

    /* Issuer certificate */
    CINIT(ISSUERCERT, OBJECTPOINT, 170),

    /* (IPv6) Address scope */
    CINIT(ADDRESS_SCOPE, LONG, 171),

    /* Collect certificate chain info and allow it to get retrievable with
       CURLINFO_CERTINFO after the transfer is complete. (Unfortunately) only
       working with OpenSSL-powered builds. */
    CINIT(CERTINFO, LONG, 172),

    /* "name" and "pwd" to use when fetching. */
    CINIT(USERNAME, OBJECTPOINT, 173),
    CINIT(PASSWORD, OBJECTPOINT, 174),

      /* "name" and "pwd" to use with Proxy when fetching. */
    CINIT(PROXYUSERNAME, OBJECTPOINT, 175),
    CINIT(PROXYPASSWORD, OBJECTPOINT, 176),

    /* Comma separated list of hostnames defining no-proxy zones. These should
       match both hostnames directly, and hostnames within a domain. For
       example, local.com will match local.com and www.local.com, but NOT
       notlocal.com or www.notlocal.com. For compatibility with other
       implementations of this, .local.com will be considered to be the same as
       local.com. A single * is the only valid wildcard, and effectively
       disables the use of proxy. */
    CINIT(NOPROXY, OBJECTPOINT, 177),

    /* block size for TFTP transfers */
    CINIT(TFTP_BLKSIZE, LONG, 178),

    /* Socks Service */
    CINIT(SOCKS5_GSSAPI_SERVICE, OBJECTPOINT, 179),

    /* Socks Service */
    CINIT(SOCKS5_GSSAPI_NEC, LONG, 180),

    /* set the bitmask for the protocols that are allowed to be used for the
       transfer, which thus helps the app which takes URLs from users or other
       external inputs and want to restrict what protocol(s) to deal
       with. Defaults to CURLPROTO_ALL. */
    CINIT(PROTOCOLS, LONG, 181),

    /* set the bitmask for the protocols that libcurl is allowed to follow to,
       as a subset of the CURLOPT_PROTOCOLS ones. That means the protocol needs
       to be set in both bitmasks to be allowed to get redirected to. Defaults
       to all protocols except FILE and SCP. */
    CINIT(REDIR_PROTOCOLS, LONG, 182),

    /* set the SSH knownhost file name to use */
    CINIT(SSH_KNOWNHOSTS, OBJECTPOINT, 183),

    /* set the SSH host key callback, must point to a curl_sshkeycallback
       function */
    CINIT(SSH_KEYFUNCTION, FUNCTIONPOINT, 184),

    /* set the SSH host key callback custom pointer */
    CINIT(SSH_KEYDATA, OBJECTPOINT, 185),

    /* set the SMTP mail originator */
    CINIT(MAIL_FROM, OBJECTPOINT, 186),

    /* set the SMTP mail receiver(s) */
    CINIT(MAIL_RCPT, OBJECTPOINT, 187),

    /* FTP: send PRET before PASV */
    CINIT(FTP_USE_PRET, LONG, 188),

    /* RTSP request method (OPTIONS, SETUP, PLAY, etc...) */
    CINIT(RTSP_REQUEST, LONG, 189),

    /* The RTSP session identifier */
    CINIT(RTSP_SESSION_ID, OBJECTPOINT, 190),

    /* The RTSP stream URI */
    CINIT(RTSP_STREAM_URI, OBJECTPOINT, 191),

    /* The Transport: header to use in RTSP requests */
    CINIT(RTSP_TRANSPORT, OBJECTPOINT, 192),

    /* Manually initialize the client RTSP CSeq for this handle */
    CINIT(RTSP_CLIENT_CSEQ, LONG, 193),

    /* Manually initialize the server RTSP CSeq for this handle */
    CINIT(RTSP_SERVER_CSEQ, LONG, 194),

    /* The stream to pass to INTERLEAVEFUNCTION. */
    CINIT(INTERLEAVEDATA, OBJECTPOINT, 195),

    /* Let the application define a custom write method for RTP data */
    CINIT(INTERLEAVEFUNCTION, FUNCTIONPOINT, 196),

    /* Turn on wildcard matching */
    CINIT(WILDCARDMATCH, LONG, 197),

    /* Directory matching callback called before downloading of an
       individual file (chunk) started */
    CINIT(CHUNK_BGN_FUNCTION, FUNCTIONPOINT, 198),

    /* Directory matching callback called after the file (chunk)
       was downloaded, or skipped */
    CINIT(CHUNK_END_FUNCTION, FUNCTIONPOINT, 199),

    /* Change match (fnmatch-like) callback for wildcard matching */
    CINIT(FNMATCH_FUNCTION, FUNCTIONPOINT, 200),

    /* Let the application define custom chunk data pointer */
    CINIT(CHUNK_DATA, OBJECTPOINT, 201),

    /* FNMATCH_FUNCTION user pointer */
    CINIT(FNMATCH_DATA, OBJECTPOINT, 202),

    /* send linked-list of name:port:address sets */
    CINIT(RESOLVE, OBJECTPOINT, 203),

    /* Set a username for authenticated TLS */
    CINIT(TLSAUTH_USERNAME, OBJECTPOINT, 204),

    /* Set a password for authenticated TLS */
    CINIT(TLSAUTH_PASSWORD, OBJECTPOINT, 205),

    /* Set authentication type for authenticated TLS */
    CINIT(TLSAUTH_TYPE, OBJECTPOINT, 206),

    /* Set to 1 to enable the "TE:" header in HTTP requests to ask for
       compressed transfer-encoded responses. Set to 0 to disable the use of TE:
       in outgoing requests. The current default is 0, but it might change in a
       future libcurl release.

       libcurl will ask for the compressed methods it knows of, and if that
       isn't any, it will not ask for transfer-encoding at all even if this
       option is set to 1.

    */
    CINIT(TRANSFER_ENCODING, LONG, 207),

    /* Callback function for closing socket (instead of close(2)). The callback
       should have type curl_closesocket_callback */
    CINIT(CLOSESOCKETFUNCTION, FUNCTIONPOINT, 208),
    CINIT(CLOSESOCKETDATA, OBJECTPOINT, 209),

    /* allow GSSAPI credential delegation */
    CINIT(GSSAPI_DELEGATION, LONG, 210),

    /* Set the name servers to use for DNS resolution */
    CINIT(DNS_SERVERS, OBJECTPOINT, 211),

    /* Time-out accept operations (currently for FTP only) after this amount
       of miliseconds. */
    CINIT(ACCEPTTIMEOUT_MS, LONG, 212),

    /* Set TCP keepalive */
    CINIT(TCP_KEEPALIVE, LONG, 213),

    /* non-universal keepalive knobs (Linux, AIX, HP-UX, more) */
    CINIT(TCP_KEEPIDLE, LONG, 214),
    CINIT(TCP_KEEPINTVL, LONG, 215),

    /* Enable/disable specific SSL features with a bitmask, see CURLSSLOPT_* */
    CINIT(SSL_OPTIONS, LONG, 216),

    /* set the SMTP auth originator */
    CINIT(MAIL_AUTH, OBJECTPOINT, 217),

    CURLOPT_LASTENTRY /* the last unused */
  } CURLoption;

  #define CURLOPT_WRITEDATA CURLOPT_FILE

  typedef void CURL;

  CURL    *curl_easy_init(void);
  CURLcode curl_easy_perform(CURL *curl);
  CURLcode curl_easy_setopt(CURL *curl, CURLoption option, void *arg);
  CURLcode curl_global_init(long flags);
  void     curl_easy_cleanup(CURL *curl);
  void     curl_global_cleanup(void);


  /*****************************************************************************************************************************/
  /* Debugging                                                                                                                 */
  /*****************************************************************************************************************************/

  void   DumpMemory(byte* p, dword size, int BytesPerLine);
  void   DumpMemoryDword(dword *p, dword size);
  dword *FindGotPointer(dword FunctionAddress);
  void   LogEntry(char *FileName, char *ProgramName, bool Console, eTimeStampFormat TimeStampFormat, char *Text);
  void   LogEntryPrintf(char *FileName, char *ProgramName, bool Console, eTimeStampFormat TimeStampFormat, char *format, ...);
  void   LogEntryGeneric(char *ProgramName, bool Console, char *Text);
  void   LogEntryGenericPrintf(char *ProgramName, bool Console, char *format, ...);
  void   LogEntryFBLibPrintf(bool Console, char *format, ...);
  bool   HookFirmware(char *FirmwareFunctionName, void *RedirectTo, void *PointerToOriginal);
  bool   UnhookFirmware(char *FirmwareFunctionName, void *RedirectTo, void *PointerToOriginal);

  void   CallTraceInit(void);
  void   CallTraceEnable(bool Enable);
  void   CallTraceEnter(char *ProcName);
  void   CallTraceExit(dword *Magic);
  void   CallTraceExitResult(dword *Magic, char *Result);
  void   CallTraceComment(char *Comment);
  void   CallTraceExportStats(char *FileName);
  void   CallTraceResetStats(void);

  #ifdef STACKTRACE
    #define TRACEENTER()    CallTraceEnter((char*)__FUNCTION__)
    #define TRACEEXIT()     CallTraceExit(NULL)
  #else
    #define TRACEENTER()
    #define TRACEEXIT()
  #endif

  bool   CrashCheck_Startup(char *TAPName);
  void   CrashCheck_Shutdown(char *TAPName);
  bool   CrashCheck_isOK(char *TAPName);

  void *TAP_MemAlloc_Chk(char *Comment, dword size);
  int   TAP_Osd_Copy_Chk(char *Comment, word srcRgnNum, word dstRgnNum, dword srcX, dword srcY, dword w, dword h, dword dstX, dword dstY,  bool sprite);
  int   TAP_Osd_Create_Chk(char *Comment, dword x, dword y, dword w, dword h, byte lutIdx, int flag);
  int   TAP_Osd_FillBox_Chk(char *Comment, word rgn, dword x, dword y, dword w, dword h, dword color);
  int   TAP_Osd_PutFreeColorGd_Chk(char *Comment, word rgn, int x, int y, TYPE_GrData * gd, bool sprite, dword FilterColor);
  int   TAP_Osd_PutGd_Chk(char *Comment, word rgn, int x, int y, TYPE_GrData * gd, bool sprite);
  int   TAP_Osd_PutPixel_Chk(char *Comment, word rgn, dword x, dword y, dword pix);
  void  TAP_Osd_RestoreBox_Chk(char *Comment, word rgn, dword x, dword y, dword w, dword h, void *data);
  byte *TAP_Osd_SaveBox_Chk(char *Comment, word rgn, dword x, dword y, dword w, dword h);


  /*****************************************************************************************************************************/
  /* EPG                                                                                                                       */
  /*****************************************************************************************************************************/

  typedef enum
  {
    RST_undefined,
    RST_NotRunning,
    RST_StartsSoon,
    RST_Pausing,
    RST_Running,
    RST_ServiceOffAir,
    RST_reserved1,
    RST_reserved2
  }tRunningStatus;

  typedef struct
  {
    word                EventID;
    byte                DataStatus;
    tRunningStatus      RunningStatus;

    dword               StartTime;              //Local start time
    dword               EndTime;                //Local time
    short               TimeZone;               //Offset from UTC in minutes
    word                duration;               //duration in minutes

    word                SatIndex;
    word                NetworkID;
    word                TSID;
    word                ServiceID;

    TYPE_ServiceType    ServiceType;
    int                 ServiceNum;

    byte                lang[4];

    byte                ParentalRate;
    byte                NameLength;
    byte                ShortEventTextLength;
    word                ExtEventTextLength;

    char                EventName[256];
    char                ShortEventText[256];
    char                ExtEventText[8192];

    dword               citID;

    byte                ContentIdentifier;      //if sourceFlag == 1 then the nibbles are reversed to ETSI and if sourceFlag == 0 then
    byte                sourceFlag;             //the nibble represent Australia-specific descriptions
    word                unknown14;
    word                iceChannel;

    byte                unknown15[6];
  } TYPE_EPGInfo;

  void EPGInfo_FilterReset(void);
  void EPGInfo_FilterTime(dword StartTime, dword EndTime);
  void EPGInfo_FilterChannelByIndex(TYPE_ServiceType SvcType, int SvcNum, bool StartCurrent);
  void EPGInfo_FilterDuration(word MinDuration, word MaxDuration);
  void EPGInfo_FilterGenre(byte *GenreArray, byte GenreArraySize);

  //To prototype for the callback is    bool CallbackFunction(TYPE_EPGInfo*)
  void EPGInfo_FilterCallback(void *CallbackRoutine);
  void EPGInfo_AbortLoad(void);

  int   EPGInfo_FindFirst(TYPE_EPGInfo *EPGData);
  bool  EPGInfo_FindNext(TYPE_EPGInfo *EPGData);
  bool  EPGInfo_FindPrev(TYPE_EPGInfo *EPGData);
  bool  EPGInfo_FindLast(TYPE_EPGInfo *EPGData);
  bool  EPGInfo_FindItem(TYPE_EPGInfo *EPGData, int EPGIndex, bool EPGReset);
  bool  EPGInfo_FindCurrent(byte SvcType, int SvcNum, TYPE_EPGInfo *EPGData);
  void  EPGInfo_Free(void);
  dword EPGInfo_GetNrFreeEntries(void);

  TYPE_TapEvent *GetCurrentEvent(int *curEvent);
  bool isOnMainTuner(int SvcType, int SvcNum);


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
  /* Extended File Attributes                                                                                                  */
  /*****************************************************************************************************************************/

  int  ExtAttribExists(char *FileName, char *AttrName);
  bool ExtAttribGet(char *FileName, char *AttrName, byte *Data, int MaxDataLen, int *DataLen);
  bool ExtAttribRemove(char *FileName, char *AttrName);
  bool ExtAttribSet(char *FileName, char *AttrName, byte *Data, int DataLen);


  /*****************************************************************************************************************************/
  /* ezXML                                                                                                                     */
  /*****************************************************************************************************************************/

  typedef struct ezxml *ezxml_t;

  struct ezxml
  {
    char               *name;     // tag name
    char              **attr;     // tag attributes { name, value, name, value, ... NULL }
    char               *txt;      // tag character content, empty string if none
    size_t              off;      // tag offset from start of parent tag character content
    ezxml_t             next;     // next tag with same name in this section at this depth
    ezxml_t             sibling;  // next tag with different name in same section and depth
    ezxml_t             ordered;  // next tag, same section and depth, in original order
    ezxml_t             child;    // head of sub tag list, NULL if none
    ezxml_t             parent;   // parent tag, NULL if current tag is root tag
    short               flags;    // additional information
  };

  // Given a string of xml data and its length, parses it and creates an ezxml
  // structure. For efficiency, modifies the data by adding null terminators
  // and decoding ampersand sequences. If you don't want this, copy the data and
  // pass in the copy. Returns NULL on failure.
  ezxml_t ezxml_parse_str(char *s, size_t len);

  // a wrapper for ezxml_parse_fd() that accepts a file name
  ezxml_t ezxml_parse_file(const char *file);

  // returns the first child tag (one level deeper) with the given name or NULL if not found
  ezxml_t ezxml_child(ezxml_t xml, const char *name);

  // returns the next tag of the same name in the same section and depth or NULL  if not found
  #define ezxml_next(xml) ((xml) ? xml->next : NULL)

  // Returns the Nth tag with the same name in the same section at the same depth
  // or NULL if not found. An index of 0 returns the tag given.
  ezxml_t ezxml_idx(ezxml_t xml, int idx);

  // returns the name of the given tag
  #define ezxml_name(xml) ((xml) ? xml->name : NULL)

  // returns the given tag's character content or empty string if none
  #define ezxml_txt(xml) ((xml) ? xml->txt : "")

  // returns the value of the requested tag attribute, or NULL if not found
  const char *ezxml_attr(ezxml_t xml, const char *attr);

  // frees the memory allocated for an ezxml structure
  void ezxml_free(ezxml_t xml);

  // returns parser error message or empty string if none
  const char *ezxml_error(ezxml_t xml);


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

  byte   DevFront_SetIlluminate(byte a0, byte Brightness);
  dword  DevHdd_DeviceClose(tDirEntry *hddPlaybackFolder);
  dword  DevHdd_DeviceOpen(tDirEntry **hddPlaybackFolder, tDirEntry *DirEntry);
  int    Appl_CheckRecording(int SvcType, int SvcNum, bool Unknown);
  int    Appl_CheckRecording_Tuner(byte TunerIndex, int SvcType, int SvcNum, bool Unknown);
  void   Appl_ClrTimer(byte *TimerHandle);
  bool   Appl_EvtProc_PincodeKey(dword p1, dword p2);
  void   Appl_ExecProgram(char *FileName);
  bool   Appl_ExportChData(char *FileName);
  void  *Appl_GetCurrentEvent(byte SatIndex, word NetID, word TSID, word ServiceID);
  dword  Appl_GetEvtCount(byte SatIndex, word NetID, word TSID, word ServiceID);
  dword  Appl_GetEvtCountInFreePool(void);
  dword *Appl_GetEvtListHeadInHash(word NetID, word TSID, word ServiceID);
  dword *Appl_GetEvtListHeadInHashByChannelID(ulong64 ChannelID);
  dword *Appl_GetEvtListHeadInUsePool(void);
  bool   Appl_GetIsExternal(void);
  dword  Appl_GetFreeExtRecordSpace(char *MountPath);
  void  *Appl_GetSameTimeEvent(byte SatIndex, word NetID, word TSID, word ServiceID);
  bool   Appl_ImportChData(char *FileName);
  void   Appl_PvrPause(bool p1);
  void   Appl_RestartTimeShiftSvc(bool p1, dword Block);
  void   Appl_SetIsExternal(bool External);
  void   Appl_SetPlaybackSpeed(byte Mode, int Speed, bool p3);
  void   Appl_ShoutCast(void);
  int    Appl_StartPlayback(char *FileName, unsigned int p2, bool p3, bool ScaleInPip);
  int    Appl_StartPlaybackMedia(char *FileName, unsigned int p2, bool p3, bool ScaleInPip);
  dword  Appl_StopPlaying(void);
  void   Appl_StopRecPlaying(bool p1);
  dword  Appl_TimeToLocal(dword UTCTime);
  dword  Appl_WaitEvt(dword Event, dword *a1, dword a2, dword a3, dword Timeout);
  void   Appl_WriteRecInfo(dword Slot);
  byte   ApplChannel_GetAgc(byte TunerIndex, byte *AGC);
  byte   ApplChannel_GetBer(byte TunerIndex, byte *BER);
  dword  ApplHdd_FileCutPaste(char *SourceFileName, unsigned int StartBlock, unsigned int NrBlocks, char *CutFileName);
  dword  ApplHdd_FreeSize(char *MountPath, bool a1);
  word   ApplHdd_GetFileInfo(word p1, int *TotalBlocks, int *CurrentBlock, byte p4, byte p5);
  dword  ApplHdd_GetInfoFromExternalDevice(dword *TotalSpaceMB, dword *FreeSpaceMB, char *MountPath);
  void   ApplHdd_RestoreWorkFolder(void);
  void   ApplHdd_SaveWorkFolder(void);
  dword  ApplHdd_SelectFolder(tDirEntry *FolderStruct, char *FolderPath);
  void   ApplHdd_SetWorkFolder(tDirEntry *FolderStruct);
  void   ApplNewVfd_Stop(void);
  void   ApplPin_Delete(void);
  bool   ApplPin_IsLockPopup(void);
  word   ApplSvc_GetSvcIdx(byte TYPE_ServiceType, byte SatIndex, word TPIndex, word ServiceID, word Start, word NrOfServicesToSearch);
  word   ApplSvc_GetTpIdx(byte SatIndex, word NetworkID, word TSID);
  int    ApplTap_GetEmptyTask(void);
  void   ApplTimer_OptimizeList(void);
  int    DevService_Mute(bool Mute);


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
    byte                  NameLock;
    word                  Flags2;

    //Unidentified fields
    byte                  unknown2[6];
  } tFlashService;

  int  FlashServiceGetTotal(int SvcType);
  bool FlashServiceGetInfo(int SvcType, int SvcNum, tFlashService *Service);
  bool FlashServiceSetInfo(int SvcType, int SvcNum, tFlashService *Service);
  bool FlashServiceAdd(int SvcType, tFlashService *Service);
  int  FlashServiceFind(int SvcType, word ServiceID, word PMTPID, word PCRPID, tFlashService *Service);
  bool FlashServiceFindNum(byte SatIndex, word NetworkID, word TSID, word ServiceID, TYPE_ServiceType *SvcType, int *SvcNum);
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

      word                DST:2;                  //0=off, 3=on
      word                unknown4:14;
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

  int   FlashFavoritesGetTotal(void);
  char *FlashFavoritesGetSelectedGroupName(void);
  bool  FlashFavoritesGetInfo(int FavNum, tFavorites *Favorites);
  bool  FlashFavoritesGetInfoCurrent(tFavorites *Favorites);
  bool  FlashFavoritesSetInfo(int FavNum, tFavorites *Favorites);
  int   FlashFavoritesFindService(int SvcType, int SvcNum);
  void  FlashFavoritesGetParameters(int *NrGroups, int *NrSvcsPerGroup);


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

  #define FONTSDIR      "/ProgramFiles/Settings/Fonts"

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

  dword FM_GetStringWidth(char *Text, tFontData *FontData);
  dword FM_GetStringHeight(char *Text, tFontData *FontData);
  void  FM_PutString(word rgn, dword x, dword y, dword maxX, char * str, dword fcolor, dword bcolor, tFontData *FontData, byte bDot, byte align);
  void  FM_PutStringAA(word rgn, dword x, dword y, dword maxX, char * str, dword fcolor, dword bcolor, tFontData *FontData, byte bDot, byte align, float AntiAliasFactor);
  bool  FM_LoadFontFile(char *FontFileName, tFontData *FontData);
  void  FM_FreeFontFile(tFontData *FontData);

  //Unicode (UTF-8 encoded) version
  typedef struct
  {
    dword               Unicode;
    dword               FileOffset;
    word                Width;
    word                Height;
  }tFontDefUC;

  typedef struct
  {
    dword               Unicode;
    byte               *GlyphData;
    word                Width;
    word                Height;
  }tGlyphCacheUC;

  typedef struct
  {
    int                 FileHandle;
    dword               FontDefEntries;
    tFontDefUC         *FontDef;
    dword               GlyphCacheEntries;
    tGlyphCacheUC      *GlyphCache;
  } tFontDataUC;

  void  FM_MakeFontDir(void);
  bool  FMUC_LoadFontFile(char *FontFileName, tFontDataUC *FontData);
  dword FMUC_GetStringHeight(char *Text, tFontDataUC *FontData);
  dword FMUC_GetStringWidth(char *Text, tFontDataUC *FontData);
  void  FMUC_PutString(word rgn, dword x, dword y, dword maxX, char * str, dword fcolor, dword bcolor, tFontDataUC *FontData, byte bDot, byte align);
  void  FMUC_PutStringAA(word rgn, dword x, dword y, dword maxX, char *str, dword fcolor, dword bcolor, tFontDataUC *FontData, byte bDot, byte align, float AntiAliasFactor);
  void  FMUC_FreeFontFile(tFontDataUC *FontData);


  /*****************************************************************************************************************************/
  /* HDD Functions                                                                                                             */
  /*****************************************************************************************************************************/

  #define TAPFSROOT     "/mnt/hd"
  #define FBLIB_DIR_SIZE 512

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

  typedef enum
  {
    PF_FileNameOnly,      //Get the file name
    PF_TAPPathOnly,       //Get the TAP path w/o file name. The string willend in a "/"
    PF_LinuxPathOnly,     //Get the Linux absolute path w/o file name. The string willend in a "/"
    PF_FullTAPPath,       //Get the full TAP path including file name
    PF_FullLinuxPath      //Get the full absolute Linux path including file name
  }tPathFormat;

  bool        FixInvalidFileName(char *FileName);
  void        ConvertPathType(char *Source, char *Dest, tPathFormat DestFormat);
  tPathFormat GetPathType(char *Source);
  int         HDD_AAM_Disable(void);
  int         HDD_AAM_Enable(byte AAMLevel);
  int         HDD_APM_Disable(void);
  int         HDD_APM_Enable(byte APMLevel);
  bool        HDD_ChangeDir(char *Dir);
  void        HDD_Delete(char *FileName);
  bool        HDD_Exist(char *FileName);
  TYPE_File  *HDD_FappendOpen(char *FileName);
  bool        HDD_FappendWrite(TYPE_File *file, char *data);
  bool        HDD_FindMountPoint(char *File, char *MountPoint);
  bool        HDD_FindMountPointDevice(char *File, char *MountPoint, char *MountDevice);
  int         HDD_FindSymbolicLink(char *pathName, char *returnedPath, char *fullPathName);
  bool        HDD_GetAbsolutePathByTypeFile(TYPE_File *File, char *AbsFileName);
  bool        HDD_GetFileSizeAndInode(char *FileName, __ino64_t *CInode, __off64_t *FileSize);
  dword       HDD_GetFileTimeByFileName(char *FileName);
  dword       HDD_GetFileTimeByTypeFile(TYPE_File *File);
  bool        HDD_GetHddID(char *ModelNo, char *SerialNo, char *FirmwareNo);
  __ino64_t   HDD_GetInodeByFileName(char *Filename);
  __ino64_t   HDD_GetInodeByTypeFile(TYPE_File *File);
  bool        HDD_IdentifyDevice(char *IdentifyDeviceBuffer);
  bool        HDD_Move(char *FileName, char *FromDir, char *ToDir);
  bool        HDD_Recycle(char *FileName);
  bool        HDD_RecycleSF(char *FileName);
  void        HDD_RemoveDir(char *DirPath, bool Recursive);
  bool        HDD_Rename(char *FileName, char *NewFileName);
  int         HDD_Smart_DisableAttributeAutoSave(void);
  int         HDD_Smart_DisableOperations(void);
  int         HDD_Smart_EnableAttributeAutoSave(void);
  int         HDD_Smart_EnableOperations(void);
  int         HDD_Smart_ReadData(word *DataBuf);
  int         HDD_Smart_ReadThresholdData(word *DataBuf);
  int         HDD_Smart_ReturnStatus(void);                  ////if 20 is returned then one or more thresholds have been exceeded; -1 upon error
  bool        HDD_Unrecycle(char *FileName);
  bool        HDD_UnrecycleSF(char *FileName);
  bool        HDD_Write(void *data, dword length, TYPE_File *f);
  tFileInUse  HDD_isFileInUse(char *FileName);
  void        MakeUniqueFileName(char *FileName);
  void        SeparateFileNameComponents(char *FileName, char *Path, char *Name, char *Ext, int *Index, bool *isRec, bool *isDel);


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

  dword        FindInstructionSequence(char *SearchPattern, char *SearchMask, dword StartAddress, dword EndAddress, int EntryPointOffset, bool SearchForPrevADDIUSP);
  inline dword FIS_fwAppl_AddSvcName(void);
  inline dword FIS_fwAppl_CheckRecording(void);
  inline dword FIS_fwAppl_CheckRecording_Tuner(void);
  inline dword FIS_fwAppl_CiMenu(void);
  inline dword FIS_fwAppl_CiplusMenu(void);
  inline dword FIS_fwAppl_ClrTimer(void);
  inline dword FIS_fwAppl_ConvertToValidUTF8Str(void);
  inline dword FIS_fwAppl_DeleteRadioSvcName(void);
  inline dword FIS_fwAppl_DeleteTvSvcName(void);
  inline dword FIS_fwAppl_EnterNormal(void);
  inline dword FIS_fwAppl_EvtProc_PincodeKey(void);
  inline dword FIS_fwAppl_ExecProgram(void);
  inline dword FIS_fwAppl_ExportChData(void);
  inline dword FIS_fwAppl_GetCurrentEvent(void);
  inline dword FIS_fwAppl_GetEvtCount(void);
  inline dword FIS_fwAppl_GetEvtCountInFreePool(void);
  inline dword FIS_fwAppl_GetEvtListHeadInHash(void);
  inline dword FIS_fwAppl_GetEvtListHeadInUsePool(void);
  inline dword FIS_fwAppl_GetFreeExtRecordSpace(void);
  inline dword FIS_fwAppl_GetIsExternal(void);
  inline dword FIS_fwAppl_GetSameTimeEvent(void);
  inline dword FIS_fwAppl_GetStreamFormat(void);
  inline dword FIS_fwAppl_ImportChData(void);
  inline dword FIS_fwAppl_InitTempRec(void);
  inline dword FIS_fwAppl_IsTimeShifting(void);
  inline dword FIS_fwAppl_PvrList(void);
  inline dword FIS_fwAppl_PvrList_SetListType(void);
  inline dword FIS_fwAppl_PvrPause(void);
  inline dword FIS_fwAppl_RestartTimeShiftSvc(void);
  inline dword FIS_fwAppl_SetApplVer(void);
  inline dword FIS_fwAppl_SetIsExternal(void);
  inline dword FIS_fwAppl_SetPlaybackSpeed(void);
  inline dword FIS_fwAppl_SetProviderName(void);
  inline dword FIS_fwAppl_SetTimeShift(void);
  inline dword FIS_fwAppl_ShoutCast(void);
  inline dword FIS_fwAppl_StartPlayback(void);
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
  inline dword FIS_fwApplIcelink_EitFromHdd(void);
  inline dword FIS_fwApplOsd_DrawJpeg(void);
  inline dword FIS_fwApplPin_Delete(void);
  inline dword FIS_fwApplPin_IsLockPopup(void);
  inline dword FIS_fwApplSvc_GetSvcIdx(void);
  inline dword FIS_fwApplSvc_GetTpIdx(void);
  inline dword FIS_fwApplTap_CallEventHandler(void);
  inline dword FIS_fwApplTap_GetEmptyTask(void);
  inline dword FIS_fwApplTimer_OptimizeList(void);
  inline dword FIS_fwApplVfdSendData(void);
  inline dword FIS_fwApplVfdStart(void);
  inline dword FIS_fwApplVfdStop(void);

  inline dword FIS_fwcurl_easy_cleanup(void);
  inline dword FIS_fwcurl_easy_init(void);
  inline dword FIS_fwcurl_easy_perform(void);
  inline dword FIS_fwcurl_easy_setopt(void);
  inline dword FIS_fwcurl_global_cleanup(void);
  inline dword FIS_fwcurl_global_init(void);

  inline dword FIS_fwDevEeprom_GetMacAddr(void);
  inline dword FIS_fwDevEeprom_Info(void);
  inline dword FIS_fwDevFront_PowerOffCancel(void);
  inline dword FIS_fwDevFront_PowerOffReply(void);
  inline dword FIS_fwDevFront_SetIlluminate(void);
  inline dword FIS_fwDevHdd_DeviceClose(void);
  inline dword FIS_fwDevHdd_DeviceOpen(void);
  inline dword FIS_fwDevService_Mute(void);
  inline dword FIS_fwEeprom_DirectWrite(void);

  inline dword FIS_fwezxml_attr(void);
  inline dword FIS_fwezxml_child(void);
  inline dword FIS_fwezxml_error(void);
  inline dword FIS_fwezxml_free(void);
  inline dword FIS_fwezxml_idx(void);
  inline dword FIS_fwezxml_parse_file(void);
  inline dword FIS_fwezxml_parse_str(void);

  inline dword FIS_fwPowerOff(void);
  inline dword FIS_fwPutDevEvt(void);
  inline dword FIS_fwSetIrCode(void);

  inline dword FIS_vApplState(void);
  inline dword FIS_vAudioTrack(void);
  inline dword FIS_vbookmarkTime(void);
  inline dword FIS_vBootReason(void);
  inline dword FIS_vCheckAutoDecTimerId(void);
  inline dword FIS_vciMenuMode(void);
  inline dword FIS_vciplusMenuMode(void);
  inline dword FIS_vCurTapTask(void);
  inline dword FIS_vDirectSvcNumTimerId(void);
  inline dword FIS_vdupEntry(void);
  inline dword FIS_vEEPROM(void);
  inline dword FIS_vEEPROMPin(void);
  inline dword FIS_vEtcInfo(void);
  inline dword FIS_vExtPartitionInfo(void);
  inline dword FIS_vExtTsFolder(void);
  inline dword FIS_vfavName(void);
  inline dword FIS_vFlash(void);
  inline dword FIS_vfrontfd(void);
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
  inline dword FIS_vnDupTimer(void);
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
  inline dword FIS_vPvrPlayInfo(void);
  inline dword FIS_vPvrRecTempInfo(void);
  inline dword FIS_vPvrRecTsInfo(void);
  inline dword FIS_vPvrRecTsPlayInfo(void);
  inline dword FIS_vRECSlotAddress(byte Slot);
  inline dword FIS_vSelectedPartition(void);
  inline dword FIS_vShoutCastInfo(void);
  inline dword FIS_vShoutCastState(void);
  inline dword FIS_vTAPTable(void);
  inline dword FIS_vTapSysOsdCtrl(void);
  inline dword FIS_vTempRecSlot(void);
  inline dword FIS_vTimerEditInfo(void);
  inline dword FIS_vTimerTempInfo(void);
  inline dword FIS_vTopEvent(void);
  inline dword FIS_vVfdBrightTimerId(void);
  inline dword FIS_vVfdTimerId(void);

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

  void          LogoManager_Initialize(void *CallbackRoutine);
  void          LogoManager_MoveExternalUpdates(void);
  char         *LogoManager_ChannelNameToLogoName(char *ChannelName);
  void          LogoManager_Cleanup(void);
  void          LogoManager_CleanupMemory(void);
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
  bool          LogoManager_GetServiceNumByChannelID(ulong64 ChannelID, int *SvcType, int *SvcNum);

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
  byte  *HDD_GetPvrRecTsPlayInfoPointer(byte Slot);
  bool   HDD_GetRecSlotFiles(byte Slot, TYPE_File **RecFile, TYPE_File **InfFile, TYPE_File **NavFile);
  bool   HDD_isAnyRecording(void);
  bool   HDD_isCryptedStream(char *Buffer, dword BufferSize);
  bool   HDD_isExtRecording(void);
  bool   HDD_isRecFileName(char *FileName);
  bool   HDD_isRecording(byte RecSlot);
  char  *HDD_MakeNewRecName(char *fname, word sequence);
  dword  HDD_NumberOfRECSlots(void);

  bool   HDD_RecSlotDecode(byte Slot, tFlashTimer *RecSlot);
  bool   HDD_RecSlotEncode(byte Slot, tFlashTimer *RecSlot);    //The buffer needs to be at least 8kB in size
  bool   HDD_RECSlotSetDuration(byte Slot, word Duration);
  word   HDD_SetExtRecording(bool ExtDisk);

  bool   infData_isAvail(char *infFileName, char *NameTag, dword *PayloadSize);
  bool   infData_Get(char *infFileName, char *NameTag, dword *PayloadSize, byte **Payload);
  bool   infData_GetNameByIndex(char *infFileName, dword NameIndex, char *NameTag);
  bool   infData_Set(char *infFileName, char *NameTag, dword PayloadSize, byte *Payload);
  bool   infData_Delete(char *infFileName, char *NameTag);


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

  void        DeleteAt(char *SourceString, int Pos, int Len);
  void        ExtractLine(char *Text, char *Line);
  size_t      GetLine(char *data, bool strip);
  void        GetStringEncoding(char *Text, bool *hasAnsiChars, bool *hasUTFChars);
  byte       *GetUCPos(byte *String, int CharPos);
  void        InsertAt(char *SourceString, int Pos, char *NewString);
  bool        isUTF8Char(byte *p, byte *BytesPerChar);
  bool        isUTFToppy(void);
  void        LowerCase(char *string);
  void        MakeValidFileName(char *strName, eRemoveChars ControlCharacters);
  char       *ParseLine(char *zeile, size_t *n, char delim);
  void        ReplaceInvalidFileNameChars(char *strName);
  char       *RTrim(char *s);
  void        SeparatePathComponents(char *FullName, char *Path, char *FileName, char *FileExt);
  byte       *SkipCharTableBytes(byte *p);
  byte       *strcpyUC(byte *dest, byte *src);
  bool        StringEndsWith(char *text, char *postfix);
  int         strlenUC(byte *s);
  bool        StrMkISO(byte *SourceString);
  bool        StrMkUTF8(byte *SourceString, byte DefaultISO8859CharSet);
  byte       *strncpyUC(byte *dest, byte *src, size_t n);
  bool        StrReplace(char *String, char *Find, char *Replace);
  void        StrToISO(byte *SourceString, byte *DestString);
  void        StrToISOAlloc(byte *SourceString, byte **DestString);
  bool        StrToUTF8(byte *SourceString, byte *DestString, byte DefaultISO8859CharSet);
  void        UpperCase(char *string);
  dword       UTF8ToUTF32(byte *UTF8Character, byte *BytesPerChar);
  void        UTF32ToUTF8(dword UTF32Character, byte *UTF8Character, byte *BytesPerChar);
  char       *ValidFileName(char *strName, eRemoveChars ControlCharacters);


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
    dword                 Status;             //0x00: 1 = Running, 2 = TAP_Exit(); ???
    dword                 dlopen;             //0x04
    TYPE_File            *file;               //0x08
    dword                 unused1;            //0x0c
    dword                 TAP_Main;           //0x10
    dword                 TAP_EventHandler;   //0x14
    dword                 unused2;            //0x18
    dword                 unused3;            //0x1c
    dword                 unused4;            //0x20
    dword                 unused5;            //0x24
    tDirEntry            *CurrentDir;         //0x28
  } tTMSTAPTaskTable; //44 (0x2c) Bytes * 16 TAPs = 704 bytes

  typedef struct
  {
    dword               TAPID;
    dword               Date;
    char                TAPName[MAX_PROGRAM_NAME];
    char                Author[MAX_AUTHOR_NAME];
    char                Description[MAX_DESCRIPTION];

#ifdef MAX_PROGRAM_VERSION
    char                TAPVersion[MAX_PROGRAM_VERSION];       //This field will only be populated when the TAP has been compiled with a modified tap.h
#endif

  } tTAPInfo;

  dword HDD_TAP_Callback(dword TAPID, void *ProcedureAddress, dword param1, dword param2, dword param3, dword param4);
  bool  HDD_TAP_CheckCollision(void);
  bool  HDD_TAP_Disable(dword TAPID, bool DisableEvents);
  dword HDD_TAP_DisableAll(bool DisableEvents);
  int   HDD_TAP_GetCurrentDir(char* CurrentDir);
  bool  HDD_TAP_GetFileNameByIndex(int Index, char **TAPFileName);
  dword HDD_TAP_GetIDByFileName(char *TAPFileName);
  dword HDD_TAP_GetIDByIndex(int TAPIndex);
  int   HDD_TAP_GetIndexByID(dword TAPID);
  bool  HDD_TAP_GetInfo(char *FileName, tTAPInfo *pTAPInfo);
  void *HDD_TAP_GetStartParameter(void);
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
  void *TAP_MemRealloc(void *ptr, size_t OldSize, size_t NewSize, bool InitMemory);
  void  TAP_EnterNormalNoInfo(void);


  /*****************************************************************************************************************************/
  /* TAP Comm                                                                                                                  */
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

  typedef void* TAPCOM_Channel;

  //Client Funktionen
  TAPCOM_Channel  TAPCOM_OpenChannel(dword TargetID, dword ServiceID, dword ParamBlockVersion, void *ParamBlock);
  TAPCOM_Status   TAPCOM_GetStatus(TAPCOM_Channel Channel);
  dword           TAPCOM_LastAlive(TAPCOM_Channel Channel);
  int             TAPCOM_GetReturnValue(TAPCOM_Channel Channel);
  void            TAPCOM_CloseChannel(TAPCOM_Channel Channel);

  //Server-Funktionen
  TAPCOM_Channel  TAPCOM_GetChannel(dword param1, dword *CallerID, dword *ServiceID, dword *ParamBlockVersion, void  **ParamBlock);                                      // Rückgabewert: Pointer auf (internen) Kommunikationskanal.
  void            TAPCOM_Reject(TAPCOM_Channel Channel);
  void            TAPCOM_Finish(TAPCOM_Channel Channel, int val);
  void            TAPCOM_StillAlive(TAPCOM_Channel Channel);


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

  typedef enum
  {
    DSTR_Undefined,
    DSTR_Firmware,
    DSTR_Europe,
    DSTR_Manual
  } tDSTRule;

  #define DATE(mjd, h, m) ((dword) (((mjd) << 16) | ((h) << 8) | (m)))
  #define MJD(d) ((word) (((d) >> 16) & 0xffff))
  #define TIME(d) ((word) ((d) & 0xffff))
  #define HOUR(d) ((byte) (((d) >> 8) & 0xff))
  #define MINUTE(d) ((byte) ((d) & 0xff))

  dword  AddSec(dword date, byte dateSec, int add);
  dword  AddTime(dword date, int add);
  int    cronRegisterEvent(long frequency, dword firstExecution, void *callback);
  void   cronEventHandler(void);
  bool   cronGetEvent(int Index, int *frequency, dword *nextExecution);
  bool   cronModifyEvent(int Index, int frequency, dword nextExecution);
  bool   cronUnregisterEvent(int Index);
  void   cronUnregisterAllEvents(void);
  char  *DayOfWeek(byte WeekDay);
  dword  DST_FindNextTransition(void);
  dword  DST_CalcTransition(byte ruleOrdinal, byte ruleDay, byte ruleMonth, byte ruleHour, byte ruleMin, dword StartDate);
  void   DST_SetDSTRule(tDSTRule NewDSTRule);
  bool   GetCurrentTimeZone(short *TZOffset, bool *DST);
  bool   isMJD(dword MJD);
  dword  LocalTime2UTC(dword LocalTime, short *Offset); //Uses DST_SetDSTRule()
  dword  Now(byte *Sec);
  dword  TF2UnixTime(dword TFTimeStamp);
  long   TimeDiff(dword FromTime, dword ToTime);
  char  *TimeFormat(dword DateTime, byte Sec, eTimeStampFormat TimeStampFormat);
  bool   TimerPaddingAPICheck(void);
  bool   TimerPaddingGet(short *PrePaddingMin, short *PostPaddingMin);
  bool   TimerPaddingSet(short *PrePaddingMin, short *PostPaddingMin);
  dword  Unix2TFTime(dword UnixTimeStamp);
  dword  UTC2LocalTime(dword UTCTime, short *Offset);   //Uses DST_SetDSTRule()

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
  void OSDMenuSetFont(tFontDataUC *LeftTitle, tFontDataUC *RightTitle, tFontDataUC *ListNumber, tFontDataUC *ListName, tFontDataUC *ListValue, tFontDataUC *Buttons, tFontDataUC *Memo);
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
  void OSDMenuSetCallback(void *OSDCallbackRoutine);

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


  void        OSDMenuButtonsClear(void);
  void        OSDMenuButtonColor(dword Color);
  void        OSDMenuButtonAdd(dword Line, tButtonIcon ButtonIcon, TYPE_GrData *ButtonGd, char *Text);
  tButtonIcon OSDMenuGetButtonIcon(dword key);

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
  bool  OSDMenuItemModifyCustomIndex(int ItemIndex, int CustomIndex);
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
  void OSDMenuWaitSpinnerInit(void);
  void OSDMenuInfoBoxDestroy(void);
  void OSDMenuInfoBoxDestroyNoOSDUpdate(void);
  bool OSDMenuInfoBoxIsVisible(void);

  //Message box
  void  OSDMenuMessageBoxInitialize(char *Title, char *Text);
  void  OSDMenuMessageBoxButtonAdd(char *Text);
  void  OSDMenuMessageBoxButtonSelect(dword SelectedButton);
  void  OSDMenuMessageBoxAllowScrollOver(void);
  void  OSDMenuMessageBoxDoNotEnterNormalMode(bool DoNotEnterNormalMode);
  void  OSDMenuMessageBoxShow(void);
  void  OSDMenuMessageBoxModifyText(char *Text);
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
  void OSDMenuProgressBarDestroyNoOSDUpdate(void);
  bool OSDMenuProgressBarIsVisible(void);

  //Event handling
  bool  OSDMenuEvent(word *event, dword *param1, dword *param2);
  dword OSDMenuGetLastUnprocessedKey(void);


  /*****************************************************************************************************************************/
  /* TMS OSD Keyboard                                                                                                          */
  /*****************************************************************************************************************************/

  void OSDMenuKeyboard_Setup(char *Title, char *Variable, dword MaxLength);
  void OSDMenuKeyboard_LegendButton(dword Line, tButtonIcon ButtonIcon, char *Text);
  void OSDMenuKeyboard_Show(void);
  bool OSDMenuKeyboard_EventHandler(word *event, dword *param1, dword *param2);
  bool OSDMenuKeyboard_isVisible(void);
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

  //#define EVT_USBKEYBOARD   0x0ffe
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
