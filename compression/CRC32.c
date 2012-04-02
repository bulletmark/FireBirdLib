#include "../libFireBird.h"

dword                   CRC32Table[256];
bool                    CRCTableOK = FALSE;

void make_crc_table(void);

void make_crc_table(void)
{
  dword                dwCRC;
  dword                CRCPOLY = 0;
  dword                i, j;
  bool                 topbit;
  byte                 poly[15] = { 0, 1, 2, 4, 5, 7, 8, 10, 11, 12, 16, 22, 23, 26 };

#ifdef DEBUG_FIREBIRDLIB
  CallTraceEnter("make_crc_table");
#endif

  for(i = 0; i < 15; ++i)
    CRCPOLY |= (1 << poly [i]);

  for(i = 0; i < 256; i++)
  {
    dwCRC = i << 24;
    for(j = 0; j < 8; ++j)
    {
      topbit = (dwCRC >> 31);
      dwCRC <<= 1;
      if (topbit) dwCRC ^= CRCPOLY;
    }
    CRC32Table[i] = dwCRC;
  }
  CRCTableOK = TRUE;

#ifdef DEBUG_FIREBIRDLIB
  CallTraceExit(NULL);
#endif
}


dword CRC32(dword StartValue, void *StartAddress, dword Length)
{
  volatile byte         *pData;
  dword                 crc = StartValue;   //Normaly 0xffffffff

#ifdef DEBUG_FIREBIRDLIB
  CallTraceEnter("CRC32");
#endif

  if (!CRCTableOK) make_crc_table();

  for (pData = StartAddress; pData < (byte *) StartAddress + Length; pData++)
    crc = (crc << 8) ^ CRC32Table[((crc >> 24) ^ *pData) & 0xff];

#ifdef DEBUG_FIREBIRDLIB
  CallTraceExit(NULL);
#endif

  return crc;
}
