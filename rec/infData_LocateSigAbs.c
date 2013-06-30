#include <stdio.h>
#include <string.h>
#include <tap.h>
#include "FBLib_rec.h"

extern FILE            *infDatainfFileAbs;

bool infData_LocateSigAbs(char *NameTag, dword *PayloadSize)
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

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("infData_LocateSigAbs");
  #endif

  ret = FALSE;
  if(PayloadSize) *PayloadSize = 0;

  if(NameTag && *NameTag && infDatainfFileAbs && (infData_FlenAbs() > INFDATASTART))
  {
    fseek(infDatainfFileAbs, INFDATASTART, SEEK_SET);

    while((CurrentPos = ftell(infDatainfFileAbs)) < infData_FlenAbs())
    {
      fread(&TFRPlusHdr, sizeof(tTFRPlusHdr), 1, infDatainfFileAbs);

      //Stop parsing if the magic is invalid
      if(memcmp(TFRPlusHdr.Magic, INFDATMAGIC, 4) != 0) break;

      fread(NameTagHdr, TFRPlusHdr.NameTagLen, 1, infDatainfFileAbs);

      if(strcmp(NameTag, NameTagHdr) == 0)
      {
        ret = TRUE;
        if(PayloadSize) *PayloadSize = TFRPlusHdr.PayloadSize;
        fseek(infDatainfFileAbs, CurrentPos, SEEK_SET);
        break;
      }
      fseek(infDatainfFileAbs, TFRPlusHdr.PayloadSize, SEEK_CUR);
    }
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
