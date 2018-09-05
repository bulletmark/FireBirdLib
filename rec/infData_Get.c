#include <stdio.h>
#include "FBLib_rec.h"

extern FILE            *infDatainfFile;

bool infData_Get(char *infFileName, char *NameTag, dword *PayloadSize, byte **Payload)
{
  byte                 *DataBlock;
  bool                  ret;
  tTFRPlusHdr           TFRPlusHdr;
  char                  NameTagHdr[256], s[256];

  TRACEENTER;

  ret = FALSE;
  if(PayloadSize) *PayloadSize = 0;
  if(Payload) *Payload = NULL;

  if(NameTag && *NameTag && Payload && infData_OpenFile(infFileName) && infData_LocateSig(NameTag, NULL))
  {
    ret = TRUE;
    DataBlock = NULL;

    fread(&TFRPlusHdr, sizeof(tTFRPlusHdr), 1, infDatainfFile);
    fread(NameTagHdr, TFRPlusHdr.NameTagLen, 1, infDatainfFile);
    if(PayloadSize) *PayloadSize = TFRPlusHdr.PayloadSize;

    if(TFRPlusHdr.PayloadSize > 0)
    {
      DataBlock = TAP_MemAlloc(TFRPlusHdr.PayloadSize);
      if(DataBlock)
        fread(DataBlock, TFRPlusHdr.PayloadSize, 1, infDatainfFile);
      else
      {
        TAP_SPrint(s, "failed to reserve %d bytes for %s:%s", TFRPlusHdr.PayloadSize, infFileName, NameTag);
        LogEntryFBLibPrintf(TRUE, "infData: %s", s);
      }
    }
    *Payload = DataBlock;
  }

  infData_CloseFile();

  TRACEEXIT;
  return ret;
}
