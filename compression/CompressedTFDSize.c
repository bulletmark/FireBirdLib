#include                "../libFireBird.h"
#include                "FBLib_compression.h"

dword CompressedTFDSize(byte *pSrc, dword SourceBufferSize, void *pPercentFinishedCallback)
{
  dword                 ret;

#ifdef DEBUG_FIREBIRDLIB
  CallTraceEnter("CompressedTFDSize");
#endif

  ret = CompressTFD (pSrc, SourceBufferSize, NULL, 0, 0, pPercentFinishedCallback);

#ifdef DEBUG_FIREBIRDLIB
  CallTraceExit(NULL);
#endif

  return ret;
}
