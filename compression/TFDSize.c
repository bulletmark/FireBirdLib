#include                "libFireBird.h"
#include                "FBLib_compression.h"

dword TFDSize(byte *pTFD)
{
  TRACEENTER();

  word                  NrBlocks = 0;
  dword                 i;
  byte                  *p = pTFD;

  if(!pTFD)
  {
    TRACEEXIT();
    return 0;
  }

  if(LOAD_WORD(p) != 8)
  {
    //Invalid header
    TRACEEXIT();
    return 0;
  }

  if(CRC16 (0, p + 4, 6) != LOAD_WORD(p + 2))
  {
    //Invalid header CRC
    TRACEEXIT();
    return 0;
  }

  if(LOAD_WORD(p + 6) != 1)
  {
    //Invalid file version
    TRACEEXIT();
    return 0;
  }

  NrBlocks = LOAD_WORD(p + 8);
  p += 10;
  for(i = 0; i < NrBlocks; i++)
    p += LOAD_WORD(p) + 2;

  TRACEEXIT();
  return p - pTFD;
}
