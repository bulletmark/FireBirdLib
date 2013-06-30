#include <stdio.h>
#include <string.h>
#include <tap.h>
#include "FBLib_rec.h"

extern FILE            *infDatainfFileAbs;

bool infData_GetNameByIndexAbs(char *infFileName, dword NameIndex, char *NameTag)
{
  bool                  ret;
  tTFRPlusHdr           TFRPlusHdr;
  char                  NameTagHdr[256];
  dword                 CurrentIndex;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("infData_GetNameByIndexAbs");
  #endif

  ret = FALSE;

  if(NameTag && infData_OpenFileAbs(infFileName))
  {
    CurrentIndex = 0;
    fseek(infDatainfFileAbs, INFDATASTART, SEEK_SET);

    while(ftell(infDatainfFileAbs) < (int)infData_FlenAbs())
    {
      fread(&TFRPlusHdr, sizeof(tTFRPlusHdr), 1, infDatainfFileAbs);

      //Stop parsing if the magic is invalid
      if(memcmp(TFRPlusHdr.Magic, INFDATMAGIC, 4) != 0) break;

      fread(NameTagHdr, TFRPlusHdr.NameTagLen, 1, infDatainfFileAbs);

      if(NameIndex == CurrentIndex)
      {
        ret = TRUE;
        strcpy(NameTag, NameTagHdr);
        break;
      }

      CurrentIndex++;
      fseek(infDatainfFileAbs, TFRPlusHdr.PayloadSize, SEEK_CUR);
    }
  }

  infData_CloseFileAbs();

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
