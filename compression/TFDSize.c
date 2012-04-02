#include                "../libFireBird.h"
#include                "FBLib_compression.h"

dword TFDSize(byte *pTFD)
{
  word                  NrBlocks = 0;
  dword                 i;
  byte                  *p = pTFD;

#ifdef DEBUG_FIREBIRDLIB
  CallTraceEnter("TFDSize");
#endif

  if (LOAD_WORD(p) != 8)                            //Invalid header?
  {

#ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
#endif

    return 0;
  }

  if (CRC16 (0, p + 4, 6) != LOAD_WORD(p + 2))      //Invalid header CRC?
  {

#ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
#endif

    return 0;
  }

  if (LOAD_WORD(p + 6) != 1)                        //Invalid file version?
  {

#ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
#endif

    return 0;
  }

  NrBlocks = LOAD_WORD(p + 8);
  p += 10;
  for (i = 0; i < NrBlocks; i++)
    p += LOAD_WORD(p) + 2;

#ifdef DEBUG_FIREBIRDLIB
  CallTraceExit(NULL);
#endif

  return p - pTFD;
}
