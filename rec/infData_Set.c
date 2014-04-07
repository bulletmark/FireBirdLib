#include <stdio.h>
#include <string.h>
#include <tap.h>
#include "FBLib_rec.h"

extern FILE            *infDatainfFile;

bool infData_Set(char *infFileName, char *NameTag, dword PayloadSize, byte *Payload)
{
  bool                  ret;
  tTFRPlusHdr           TFRPlusHdr;

  TRACEENTER();

  ret = FALSE;

  infData_Delete(infFileName, NameTag);
  if(NameTag && *NameTag && infData_OpenFile(infFileName))
  {
    ret = TRUE;

    //Ensure the minimum size of INFDATASTART bytes
    if(infData_Flen() < INFDATASTART)
    {
      infData_CloseFile();
      infData_Truncate(infFileName, INFDATASTART);
      infData_OpenFile(infFileName);
    }

    //Add the data block
    fseek(infDatainfFile, 0, SEEK_END);

    memcpy(TFRPlusHdr.Magic, INFDATMAGIC, 4);
    TFRPlusHdr.NameTagLen = strlen(NameTag) + 1;
    TFRPlusHdr.PayloadSize = PayloadSize;

    if(PayloadSize && (Payload == NULL))
    {
      LogEntryFBLibPrintf(TRUE, "infData: PayloadSize of %s:%s is not 0, but data pointer is NULL!", infFileName, NameTag);
      TFRPlusHdr.PayloadSize = 0;
      ret = FALSE;
    }

    fwrite(&TFRPlusHdr, sizeof(tTFRPlusHdr), 1, infDatainfFile);
    fwrite(NameTag, TFRPlusHdr.NameTagLen, 1, infDatainfFile);

    if(Payload)
      fwrite(Payload, TFRPlusHdr.PayloadSize, 1, infDatainfFile);
  }
  infData_CloseFile();

  TRACEEXIT();
  return ret;
}
