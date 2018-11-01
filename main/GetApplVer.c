#include                <string.h>
#include                "libFireBird.h"

char *GetApplVer(void)
{
  TRACEENTER();

  void (*Appl_SetApplVer)(char *);

  char                 *osdOutBuf;
  static char           FWVersion[20];
  dword                 roStart, roEnd;
  byte                 *p;
  dword                 SectionIndex;

  if(FWVersion[0])
  {
    TRACEEXIT();
    return FWVersion;
  }

  osdOutBuf = (void*)FIS_vOsdOutBuf();
  Appl_SetApplVer = (void*)FIS_fwAppl_SetApplVer();

  if(!osdOutBuf || !Appl_SetApplVer)
  {
    TRACEEXIT();
    return NULL;
  }

  //According to the disass listing, the char* parameter is not used.
  //The output is buffered into the 0x1000 bytes buffer _osdOutBuf.
  osdOutBuf[0] = '\0';
  Appl_SetApplVer(NULL);
  strcpy(FWVersion, osdOutBuf);

  if(ELFOpenFile("/root/pvr") && ELFReadELFHeader() && ELFReadSectionHeaders() && ELFReadShstrtabSection())
  {
    SectionIndex = ELFGetSectionIndex(".rodata");
    if(SectionIndex)
    {
      ELFGetSectionAddress(SectionIndex, &roStart, &roEnd);
      roEnd += roStart;
      p = (byte*)roStart;
      while(p < (byte*)roEnd)
      {
        //a typical date: Dec 19 2013
        //the first digit of the day is a space instead of a 0
        if((p[3] == ' ') && (p[6] == ' ') && (p[7] == '2') && (p[8] == '0') && (((p[9] == '0')) || ((p[9] == '1'))))
        {
          strcat(FWVersion, " (");
          strcat(FWVersion, p);
          strcat(FWVersion, ")");
          break;
        }
        p +=4;
      }
    }
  }
  ELFCleanup();

  TRACEEXIT();
  return FWVersion;
}
