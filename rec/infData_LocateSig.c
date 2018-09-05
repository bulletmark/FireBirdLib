#include <stdio.h>
#include <string.h>
#include "FBLib_rec.h"

extern FILE            *infDatainfFile;

bool infData_LocateSig(char *NameTag, dword *PayloadSize)
{
  bool                  ret;
  tTFRPlusHdr           TFRPlusHdr;
  char                  NameTagHdr[256];
  dword                 CurrentPos;

  //Format
  //  char Magic[4]             //TFr+
  //  dword PayloadSize
  //  word NameTagLength        //includes the NULL character
  //  char NameTag[SigLength]
  //  byte Payload[PayloadSize]

  TRACEENTER;

  ret = FALSE;
  if(PayloadSize) *PayloadSize = 0;

  if(NameTag && *NameTag && infDatainfFile && (infData_Flen() > INFDATASTART))
  {
    fseek(infDatainfFile, INFDATASTART, SEEK_SET);

    while((CurrentPos = ftell(infDatainfFile)) < infData_Flen())
    {
      fread(&TFRPlusHdr, sizeof(tTFRPlusHdr), 1, infDatainfFile);

      //Stop parsing if the magic is invalid
      if(memcmp(TFRPlusHdr.Magic, INFDATMAGIC, 4) != 0) break;

      fread(NameTagHdr, TFRPlusHdr.NameTagLen, 1, infDatainfFile);

      if(strcmp(NameTag, NameTagHdr) == 0)
      {
        ret = TRUE;
        if(PayloadSize) *PayloadSize = TFRPlusHdr.PayloadSize;
        fseek(infDatainfFile, CurrentPos, SEEK_SET);
        break;
      }
      fseek(infDatainfFile, TFRPlusHdr.PayloadSize, SEEK_CUR);
    }
  }

  TRACEEXIT;
  return ret;
}
