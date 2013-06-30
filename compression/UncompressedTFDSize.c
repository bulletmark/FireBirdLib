#include                "../libFireBird.h"
#include                "FBLib_compression.h"

dword UncompressedTFDSize(byte *pSrc)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("UncompressedTFDSize");
  #endif

  word                  compSize = 0, uncompSize = 0, NrBlocks = 0;
  dword                 outSize = 0, i;

  if(!pSrc)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return 0;
  }

  if(LOAD_WORD(pSrc) != 8)
  {
    //Invalid header
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return 0;
  }

  if(CRC16 (0, pSrc + 4, 6) != LOAD_WORD(pSrc + 2))
  {
    //Invalid header CRC
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return 0;
  }

  if(LOAD_WORD(pSrc + 6) != 1)
  {
    //Invalid file version
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return 0;
  }

  NrBlocks = LOAD_WORD(pSrc + 8);

  pSrc += 10;

  for(i = 0; i < NrBlocks; i++)
  {
    compSize   = LOAD_WORD(pSrc) - 6;
    uncompSize = LOAD_WORD(pSrc + 6);

    if(uncompSize > 0x7ffa)
    {
      //Uncompressed data block size too large
      #ifdef DEBUG_FIREBIRDLIB
        CallTraceExit(NULL);
      #endif

      return 0;
    }

    pSrc += compSize + 8;
    outSize += uncompSize;
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return outSize;
}
