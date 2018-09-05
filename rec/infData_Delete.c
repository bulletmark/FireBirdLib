#include <stdio.h>
#include "FBLib_rec.h"

extern FILE            *infDatainfFile;

bool infData_Delete(char *infFileName, char *NameTag)
{
  bool                  ret;
  dword                 SourcePos, DestPos, Len;
  tTFRPlusHdr           TFRPlusHdr;
  char                  NameTagHdr[512];
  byte                  *Data;

  TRACEENTER;

  ret = FALSE;

  if(NameTag && *NameTag && infData_OpenFile(infFileName) && infData_LocateSig(NameTag, NULL))
  {
    ret = TRUE;

    //Now the file pointer is located at the beginning of the data block
    //which should be deleted.
    DestPos = ftell(infDatainfFile);
    fread(&TFRPlusHdr, sizeof(tTFRPlusHdr), 1, infDatainfFile);
    Len = sizeof(tTFRPlusHdr) + TFRPlusHdr.NameTagLen + TFRPlusHdr.PayloadSize;
    SourcePos = DestPos + Len;
    fseek(infDatainfFile, SourcePos, SEEK_SET);

    while(SourcePos < infData_Flen())
    {
      //Stop if we're unable to read the whole header
      if(fread(&TFRPlusHdr, sizeof(tTFRPlusHdr), 1, infDatainfFile) == 0) break;

      //Stop parsing if the magic is invalid
      if(memcmp(TFRPlusHdr.Magic, INFDATMAGIC, 4) != 0) break;

      Len = sizeof(tTFRPlusHdr) + TFRPlusHdr.NameTagLen + TFRPlusHdr.PayloadSize;

      fread(NameTagHdr, TFRPlusHdr.NameTagLen, 1, infDatainfFile);

      if(TFRPlusHdr.PayloadSize)
      {
        Data = TAP_MemAlloc(TFRPlusHdr.PayloadSize);
        if(Data)
        {
          fread(Data, TFRPlusHdr.PayloadSize, 1, infDatainfFile);
        }
        else
        {
          LogEntryFBLibPrintf(TRUE, "infData: failed to reserve %d bytes for deletion of %s:%s", TFRPlusHdr.PayloadSize, infFileName, NameTagHdr);
          TFRPlusHdr.PayloadSize = 0;
        }
      }
      else
        Data = NULL;

      fseek(infDatainfFile, DestPos, SEEK_SET);
      fwrite(&TFRPlusHdr, sizeof(tTFRPlusHdr), 1, infDatainfFile);
      fwrite(NameTagHdr, TFRPlusHdr.NameTagLen, 1, infDatainfFile);

      if(Data)
      {
        fwrite(Data, TFRPlusHdr.PayloadSize, 1, infDatainfFile);
        TAP_MemFree(Data);
      }

      DestPos += Len;
      SourcePos += Len;

      fseek(infDatainfFile, SourcePos, SEEK_SET);
    }
    infData_Truncate(infFileName, DestPos);
  }

  infData_CloseFile();

  TRACEEXIT;
  return ret;
}
