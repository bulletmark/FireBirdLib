#include <stdio.h>
#include <tap.h>
#include "FBLib_rec.h"

extern FILE            *infDatainfFileAbs;

bool infData_DeleteAbs(char *infFileName, char *NameTag)
{
  bool                  ret;
  dword                 SourcePos, DestPos, Len;
  tTFRPlusHdr           TFRPlusHdr;
  char                  NameTagHdr[512], s[256];
  byte                  *Data;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("infData_DeleteAbs");
  #endif

  ret = FALSE;

  if(NameTag && *NameTag && infData_OpenFileAbs(infFileName) && infData_LocateSigAbs(NameTag, NULL))
  {
    ret = TRUE;

    //Now the file pointer is located at the beginning of the data block
    //which should be deleted.
    DestPos = ftell(infDatainfFileAbs);
    fread(&TFRPlusHdr, sizeof(tTFRPlusHdr), 1, infDatainfFileAbs);
    Len = sizeof(tTFRPlusHdr) + TFRPlusHdr.NameTagLen + TFRPlusHdr.PayloadSize;
    SourcePos = DestPos + Len;
    fseek(infDatainfFileAbs, SourcePos, SEEK_SET);

    while(SourcePos < infData_FlenAbs())
    {
      //Stop if we're unable to read the whole header
      if(fread(&TFRPlusHdr, sizeof(tTFRPlusHdr), 1, infDatainfFileAbs) == 0) break;

      //Stop parsing if the magic is invalid
      if(memcmp(TFRPlusHdr.Magic, INFDATMAGIC, 4) != 0) break;

      Len = sizeof(tTFRPlusHdr) + TFRPlusHdr.NameTagLen + TFRPlusHdr.PayloadSize;

      fread(NameTagHdr, TFRPlusHdr.NameTagLen, 1, infDatainfFileAbs);

      if(TFRPlusHdr.PayloadSize)
      {
        Data = TAP_MemAlloc(TFRPlusHdr.PayloadSize);
        if(Data)
        {
          fread(Data, TFRPlusHdr.PayloadSize, 1, infDatainfFileAbs);
        }
        else
        {
          TAP_SPrint(s, "failed to reserve %d bytes for deletion of %s:%s\n", TFRPlusHdr.PayloadSize, infFileName, NameTagHdr);
          LogEntryFBLibPrintf(TRUE, "infData: %s", s);
          TFRPlusHdr.PayloadSize = 0;
        }
      }
      else
        Data = NULL;

      fseek(infDatainfFileAbs, DestPos, SEEK_SET);
      fwrite(&TFRPlusHdr, sizeof(tTFRPlusHdr), 1, infDatainfFileAbs);
      fwrite(NameTagHdr, TFRPlusHdr.NameTagLen, 1, infDatainfFileAbs);

      if(Data)
      {
        fwrite(Data, TFRPlusHdr.PayloadSize, 1, infDatainfFileAbs);
        TAP_MemFree(Data);
      }

      DestPos += Len;
      SourcePos += Len;

      fseek(infDatainfFileAbs, SourcePos, SEEK_SET);
    }
    infData_TruncateAbs(infFileName, DestPos);
  }

  infData_CloseFileAbs();

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
