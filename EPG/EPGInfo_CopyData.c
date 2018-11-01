#include                <string.h>
#include                "FBLib_EPG.h"

void EPGInfo_CopyData(TYPE_EvtInfo *EvtInfo, TYPE_EPGInfo *EPGInfo, dword EventStartTime, dword EventEndTime, short Offset)
{
  TRACEENTER();

  if(EvtInfo && EPGInfo)
  {
    EPGInfo->EventID         = EvtInfo->EventID;
    EPGInfo->DataStatus      = EvtInfo->DataStatus;
    EPGInfo->RunningStatus   = EvtInfo->RunningStatus;

    EPGInfo->StartTime       = EventStartTime;
    EPGInfo->EndTime         = EventEndTime;
    EPGInfo->TimeZone        = Offset;
    EPGInfo->duration        = EvtInfo->durationHour * 60 + EvtInfo->durationMin;

    EPGInfo->SatIndex        = EvtInfo->SatIndex;
    EPGInfo->NetworkID       = EvtInfo->NetworkID;
    EPGInfo->TSID            = EvtInfo->TSID;
    EPGInfo->ServiceID       = EvtInfo->ServiceID;

    FlashServiceFindNum(EvtInfo->SatIndex, EvtInfo->NetworkID, EvtInfo->TSID, EvtInfo->ServiceID, &EPGInfo->ServiceType, &EPGInfo->ServiceNum);

    strncpy(EPGInfo->lang, EvtInfo->lang, 3);
    EPGInfo->lang[4] = '\0';

    EPGInfo->ParentalRate    = EvtInfo->ParentalRate;

    //Convert all non-ASCII characters to Unicode
    //Event Name
    memset(EPGInfo->EventName, 0, sizeof(EPGInfo->EventName));
    strncpyUC(EPGInfo->EventName, EvtInfo->ShortEventText, EvtInfo->NameLength);
    StrMkUTF8(EPGInfo->EventName, 9);
    EPGInfo->NameLength = strlen(EPGInfo->EventName);

    //Short event text
    memset(EPGInfo->ShortEventText, 0, sizeof(EPGInfo->ShortEventText));
    strcpyUC(EPGInfo->ShortEventText, &EvtInfo->ShortEventText[EvtInfo->NameLength]);
    StrMkUTF8(EPGInfo->ShortEventText, 9);
    EPGInfo->ShortEventTextLength = strlen(EPGInfo->ShortEventText);

    //Long event text
    //As an ext description may contain multiple NULL characters, replace them with 0x0a, convert to UTF-8 and then replace back to 0x00
    memset(EPGInfo->ExtEventText, 0, sizeof(EPGInfo->ExtEventText));
    memcpy(EPGInfo->ExtEventText, EvtInfo->ExtEventText, EvtInfo->ExtEventTextLength);

    char *p = EPGInfo->ExtEventText;
    int i;

    for(i = 0; i < EvtInfo->ExtEventTextLength; i++)
    {
      if(*p == '\x00') *p = '\x01';
      p++;
    }
    StrMkUTF8(EPGInfo->EventName, 9);
    EPGInfo->ExtEventTextLength = strlen(EPGInfo->ExtEventText);
    p = EPGInfo->ExtEventText;
    while(*p)
    {
      if(*p == '\x01') *p = '\x00';
      p++;
    }

    EPGInfo->citID           = EvtInfo->citID;

    //Copy, depending on the struct size
    if(EPGInfo_CalculateStructSize() > 68)
    {
      EPGInfo->ContentIdentifier = EvtInfo->ContentIdentifier;
      EPGInfo->sourceFlag        = EvtInfo->sourceFlag;
      EPGInfo->unknown14         = EvtInfo->unknown14;
      EPGInfo->iceChannel        = EvtInfo->iceChannel;

      if(EPGInfo_CalculateStructSize() > 72)
      {
        memcpy(EPGInfo->unknown15, EvtInfo->unknown15, sizeof(EvtInfo->unknown15));
      }
      else
      {
        memset(EPGInfo->unknown15, 0, sizeof(EPGInfo->unknown15));
      }
    }
    else
    {
      EPGInfo->ContentIdentifier = 0;
      EPGInfo->sourceFlag        = 0;
      EPGInfo->unknown14         = 0;
      EPGInfo->iceChannel        = 0;
      memset(EPGInfo->unknown15, 0, sizeof(EPGInfo->unknown15));
    }
  }

  TRACEEXIT();
}
