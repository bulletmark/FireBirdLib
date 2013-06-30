#ifndef FBLIB_REC_H
#define FBLIB_REC_H

#include                "../libFireBird.h"

#define PCRSECTORS      900

typedef struct
{
  TYPE_File          *RecFile;
  TYPE_File          *InfFile;
  TYPE_File          *NavFile;
} tHddRecordFile;

#define INFDATASTART      0x7d000   //500kB
#define INFDATAMAXSIG     64
#define INFDATAMAXBLOCKS  100
#define INFDATMAGIC       "TFr+"

typedef struct
{
  char                  Magic[4];
  dword                 NameTagLen;
  dword                 PayloadSize;
} tTFRPlusHdr;

extern bool             LibInitialized;

word getWord(void *buffer, bool NeedsByteSwapping);
dword getDword(void *buffer, bool NeedsByteSwapping);
void setWord(void *buffer, word Data, bool BigEndian);
void setDword(void *buffer, dword Data, bool BigEndian);

void HDD_DecodeRECHeader_ST_S(byte *Buffer, tRECHeaderInfo *RECHeaderInfo);
void HDD_DecodeRECHeader_ST_T(byte *Buffer, tRECHeaderInfo *RECHeaderInfo);
void HDD_DecodeRECHeader_ST_C(byte *Buffer, tRECHeaderInfo *RECHeaderInfo);
void HDD_DecodeRECHeader_ST_T5700(byte *Buffer, tRECHeaderInfo *RECHeaderInfo);
void HDD_DecodeRECHeader_ST_T5800(byte *Buffer, tRECHeaderInfo *RECHeaderInfo);
void HDD_DecodeRECHeader_ST_TMSS(byte *Buffer, tRECHeaderInfo *RECHeaderInfo);
void HDD_DecodeRECHeader_ST_TMST(byte *Buffer, tRECHeaderInfo *RECHeaderInfo);
void HDD_DecodeRECHeader_ST_TMSC(byte *Buffer, tRECHeaderInfo *RECHeaderInfo);

void HDD_EncodeRECHeader_ST_S(byte *Buffer, tRECHeaderInfo *RECHeaderInfo);
void HDD_EncodeRECHeader_ST_T(byte *Buffer, tRECHeaderInfo *RECHeaderInfo);
void HDD_EncodeRECHeader_ST_C(byte *Buffer, tRECHeaderInfo *RECHeaderInfo);
void HDD_EncodeRECHeader_ST_T5700(byte *Buffer, tRECHeaderInfo *RECHeaderInfo);
void HDD_EncodeRECHeader_ST_T5800(byte *Buffer, tRECHeaderInfo *RECHeaderInfo);
void HDD_EncodeRECHeader_ST_TMSS(byte *Buffer, tRECHeaderInfo *RECHeaderInfo);
void HDD_EncodeRECHeader_ST_TMST(byte *Buffer, tRECHeaderInfo *RECHeaderInfo);
void HDD_EncodeRECHeader_ST_TMSC(byte *Buffer, tRECHeaderInfo *RECHeaderInfo);

bool   infData_OpenFileAbs(char *infFileName);
dword  infData_FlenAbs(void);
bool   infData_LocateSigAbs(char *NameTag, dword *PayloadSize);
void   infData_TruncateAbs(char *infFileName, dword Position);
void   infData_CloseFileAbs(void);
char  *infData_LocToAbs(char *LocalInfName);

#endif
