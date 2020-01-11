#include <stdio.h>
#include <string.h>
#include "FBLib_rec.h"

extern FILE            *infDatainfFile;

bool infData_GetNameByIndex(const char *infFileName, dword NameIndex, char *NameTag)
{
  bool                  ret;
  tTFRPlusHdr           TFRPlusHdr;
  char                  NameTagHdr[256];
  dword                 CurrentIndex;

  TRACEENTER();

  ret = FALSE;

  if(NameTag && infData_OpenFile(infFileName))
  {
    CurrentIndex = 0;
    fseek(infDatainfFile, INFDATASTART, SEEK_SET);

    while(ftell(infDatainfFile) < (int)infData_Flen())
    {
      fread(&TFRPlusHdr, sizeof(tTFRPlusHdr), 1, infDatainfFile);

      //Stop parsing if the magic is invalid
      if(memcmp(TFRPlusHdr.Magic, INFDATMAGIC, 4) != 0) break;

      fread(NameTagHdr, TFRPlusHdr.NameTagLen, 1, infDatainfFile);

      if(NameIndex == CurrentIndex)
      {
        ret = TRUE;
        strcpy(NameTag, NameTagHdr);
        break;
      }

      CurrentIndex++;
      fseek(infDatainfFile, TFRPlusHdr.PayloadSize, SEEK_CUR);
    }
  }

  infData_CloseFile();

  TRACEEXIT();
  return ret;
}
