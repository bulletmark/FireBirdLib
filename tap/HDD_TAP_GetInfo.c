#include                <stdlib.h>
#include                <string.h>
#include                "libFireBird.h"

bool HDD_TAP_GetInfo(const char *FileName, tTAPInfo *pTAPInfo)
{
  TRACEENTER();

  dword                 Index;
  char                  s[128];

  if(!pTAPInfo)
  {
    TRACEEXIT();
    return FALSE;
  }

  if(!ELFOpenFile(FileName))
  {
    ELFCleanup();

    TRACEEXIT();
    return FALSE;
  }

  if(!ELFReadELFHeader())
  {
    ELFCleanup();

    TRACEEXIT();
    return FALSE;
  }

  if(!ELFReadSectionHeaders())
  {
    ELFCleanup();

    TRACEEXIT();
    return FALSE;
  }

  if(!ELFReadShstrtabSection())
  {
    ELFCleanup();

    TRACEEXIT();
    return FALSE;
  }

  Index = ELFGetSectionIndex("._tap_id");
  if((Index == 0) || !ELFReadDWORD(Index, &pTAPInfo->TAPID))
  {
    ELFCleanup();

    TRACEEXIT();
    return FALSE;
  }

  pTAPInfo->Date = 0;
  Index = ELFGetSectionIndex("._tap_etcinfo");
  if((Index != 0) && ELFReadData(Index, s))
  {
    word                y, m, d;
    int                 i;
    char                Mon[13][4] = {"", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    //"Dec  9 2009"
    y = atoi(&s[7]);
    s[6] = '\0';

    d = atoi(&s[4]);

    s[3] = '\0';
    m = 0;
    for(i = 1; i <= 12; i++)
      if(!strcmp(s, Mon[i]))
      {
        m = i;
        break;
      }

    pTAPInfo->Date = TAP_MakeMjd(y, m, d);
  }

  pTAPInfo->TAPName[0] = '\0';
  Index = ELFGetSectionIndex("._tap_program_name");
  if(Index) ELFReadData(Index, pTAPInfo->TAPName);

  pTAPInfo->Author[0] = '\0';
  Index = ELFGetSectionIndex("._tap_author_name");
  if(Index) ELFReadData(Index, pTAPInfo->Author);

  pTAPInfo->Description[0] = '\0';
  Index = ELFGetSectionIndex("._tap_description");
  if(Index) ELFReadData(Index, pTAPInfo->Description);

  #ifdef MAX_PROGRAM_VERSION
    pTAPInfo->TAPVersion[0] = '\0';
    Index = ELFGetSectionIndex("._tap_program_version");
    if(Index) ELFReadData(Index, pTAPInfo->TAPVersion);
  #endif

  ELFCleanup();

  TRACEEXIT();
  return TRUE;
}
