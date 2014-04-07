#ifndef FBLIB_HDD_H
#define FBLIB_HDD_H

#include                <sys/types.h>
#include                "tap.h"
#include                "../libFireBird.h"

//HDD Functions
//               CCD DD
//               SSA AA
//               102 10
//ATA Controller H/W Address: 1011 0000 0000 0001 0010 1101 0... ..xx
//
//
//                      CS1 CS0 DA2 DA1 DA0 R/W
//Data Port (DMA)       0   0   X   X   X   RW                      0xB0012D00

//Data Reg (PIO)        0   1   0   0   0   RW                      0xB0012D20
//Error Reg             0   1   0   0   1   R (W=Feature Reg)       0xB0012D24
//Feature Reg           0   1   0   0   1   W (R=Error Reg)         0xB0012D24
//SectorCount Reg       0   1   0   1   0   RW                      0xB0012D28
//LBALow Reg            0   1   0   1   1   RW                      0xB0012D2C
//LBAMid Reg            0   1   1   0   0   RW                      0xB0012D30
//LBAHigh Reg           0   1   1   0   1   RW                      0xB0012D34
//Device Reg            0   1   1   1   0   RW                      0xB0012D38
//Status Reg            0   1   1   1   1   R (W=Command Reg)       0xB0012D3C
//Command Reg           0   1   1   1   1   W (R=Status)            0xB0012D3C
//
//Alternate Status Reg  1   0   1   1   0   R (W=Control)           0xB0012D58
//Device Control Reg    1   0   1   1   0   W (R=Alternate Status)  0xB0012D58
//Invalid               1   1   X   X   X   X                       0xB0012D60-0xB0012D7F

#define oTAP_Hdd_ReadSectorDMA  0x00
#define oTAP_Hdd_WriteSectorDMA 0x01
#define oTAP_Hdd_Move           0x13

#define FBHDIO_DRIVE_CMD_HDR_SIZE       (4 * sizeof(unsigned char))
#define FBHDIO_DRIVE_TASK_HDR_SIZE      (8 * sizeof(unsigned char))
#define WIN_SMART                       0xB0
#define SMART_READ_VALUES               0xD0
#define SMART_READ_THRESHOLDS           0xD1
#define SMART_STATUS                    0xDA
#define SMART_AUTOSAVE                  0xD2
#define WIN_SETFEATURES                 0xEF
#define SETFEATURES_EN_AAM              0x42	/* Enable Automatic Acoustic Management */
#define SETFEATURES_DIS_AAM             0xC2	/* Disable Automatic Acoustic Management */
#define SETFEATURES_EN_APM              0x05	/* Enable advanced power management */
#define SETFEATURES_DIS_APM             0x85	/* Disable advanced power management */
#define SMART_ENABLE                    0xD8
#define SMART_DISABLE                   0xD9
#define HDIO_DRIVE_TASK                 0x031e	/* execute task and special drive command */
#define HDIO_DRIVE_CMD                  0x031f	/* execute a special drive command */


typedef dword (*tTAP_Hdd_ReadSectorDMA)(dword SectorNr, dword NrSectors, void *Buffer);
typedef dword (*tTAP_Hdd_WriteSectorDMA)(dword SectorNr, dword NrSectors, void *Buffer);
typedef dword (*tTAP_Hdd_Move)(char *from_dir, char *to_dir, char *filename);

#define endian_swap_word(x)  *x = (*x <<  8) | (*x >>  8)

#define DIR_MAX_STACK   16
#define FATENTRYSIZE     3

typedef struct
{
  dword Cluster;
  dword Entry;
  dword DirLen;
} DirEntry;

//We've to use the 64-bit version of lstat() else it will fail with files >= 4GB
typedef struct
{
  __dev_t st_dev;
  long int st_pad1[2];
  __ino64_t st_ino;
  __mode_t st_mode;
  __nlink_t st_nlink;
  __uid_t st_uid;
  __gid_t st_gid;
  __dev_t st_rdev;
  long int st_pad2[2];
  __off64_t st_size;
  __time_t st_atime;
  long int __reserved0;
  __time_t st_mtime;
  long int __reserved1;
  __time_t st_ctime;
  long int __reserved2;
  __blksize_t st_blksize;
  long int st_pad4;
  __blkcnt64_t st_blocks;
  long int st_pad5[14];
} tstat64;

extern int lstat64(__const char *__restrict __file, tstat64 *__restrict __buf) __THROW;
extern int stat64(__const char *__restrict __file, tstat64 *__restrict __buf) __THROW;

extern volatile word *HDD_pData;
extern volatile byte *HDD_pError;
extern volatile byte *HDD_pFeature;
extern volatile byte *HDD_pSecCount;
extern volatile byte *HDD_pLBALow;
extern volatile byte *HDD_pLBAMid;
extern volatile byte *HDD_pLBAHigh;
extern volatile byte *HDD_pDevice;
extern volatile byte *HDD_pStatus;
extern volatile byte *HDD_pCommand;
extern volatile byte *HDD_pAltStatus;
//extern volatile byte *HDD_pDevControl; /* = (byte*) 0xb0012d5b;   // device control register */
extern tTAP_Hdd_ReadSectorDMA TAP_Hdd_ReadSectorDMA;
extern tTAP_Hdd_WriteSectorDMA TAP_Hdd_WriteSectorDMA;

extern int _appl_version;
extern bool LibInitialized;
extern void* (*TAP_GetSystemProc)(int);

void  busyWait(void);
void  Delay(dword);
int   GetClusterPointer(int);

int   SendHDDCommand(dword, byte*, int);

void  SwapWords(word *);
void  SwapDWords(dword *);
int   ReceiveSector(word *);
bool  ChangeDirRoot(void);
dword CalcAbsSectorFromFAT(TYPE_File *, dword);
bool  PushDirEntry (dword Cluster, dword Entry, dword DirLen);
bool  PopDirEntry (dword *Cluster, dword *Entry, dword *DirLen);
bool  GetFileDir(char *, dword, char *);
inline dword getNextCluster(dword c);

//The latest version of the SmartFiler Recycle Bin

#define RECYCLEPATH       "/DataFiles/RecycleBin-/"
#define INFBLOCKMAGIC     "SFIB"
#define INFBLOCKVERSION   1

typedef struct
{
  char                Magic[4];                     //0
  byte                Version;                      //4
  byte                Filler1;                      //5
  word                Duration;                     //6
  dword               LastBlock;                    //8
  bool                Seen;                         //12
  dword               RecycleDate;                  //16
  char                RecoverPath[FBLIB_DIR_SIZE];  //20
  byte                Filler2[1516];                //532
                                                    //2048
}tinfBlock;

typedef struct __STDIO_FILE_STRUCT FILE;

extern FILE *fopen64 (__const char *__restrict __filename, __const char *__restrict __modes);
extern int fseeko64(FILE *__stream, __off64_t  __off, int __whence);

bool HDD_InfBlockGet(char *RecPath, tinfBlock *infBlock);
bool HDD_InfBlockSet(char *RecPath, tinfBlock *infBlock);

#endif
