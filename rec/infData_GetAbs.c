#include <stdio.h>
#include <tap.h>
#include "FBLib_rec.h"

extern FILE            *infDatainfFileAbs;

bool infData_GetAbs(char *infFileName, char *NameTag, dword *PayloadSize, byte **Payload)
{
  byte                 *DataBlock;
  bool                  ret;
  tTFRPlusHdr           TFRPlusHdr;
  char                  NameTagHdr[256], s[256];

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("infData_GetAbs");
  #endif

  ret = FALSE;
  if(PayloadSize) *PayloadSize = 0;
  if(Payload) *Payload = NULL;

  if(NameTag && *NameTag && Payload && infData_OpenFileAbs(infFileName) && infData_LocateSigAbs(NameTag, NULL))
  {
    ret = TRUE;
    DataBlock = NULL;

    fread(&TFRPlusHdr, sizeof(tTFRPlusHdr), 1, infDatainfFileAbs);
    fread(NameTagHdr, TFRPlusHdr.NameTagLen, 1, infDatainfFileAbs);
    if(PayloadSize) *PayloadSize = TFRPlusHdr.PayloadSize;

    if(TFRPlusHdr.PayloadSize > 0)
    {
      DataBlock = TAP_MemAlloc(TFRPlusHdr.PayloadSize);
      if(DataBlock)
        fread(DataBlock, TFRPlusHdr.PayloadSize, 1, infDatainfFileAbs);
      else
      {
        TAP_SPrint(s, "failed to reserve %d bytes for %s:%s", TFRPlusHdr.PayloadSize, infFileName, NameTag);
        LogEntryFBLibPrintf(TRUE, "infData: %s", s);
      }
    }
    *Payload = DataBlock;
  }

  infData_CloseFileAbs();

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
