#include                "libFireBird.h"
#include                "FBLib_LogoManager.h"

bool LogoManager_GetServiceNumByChannelID(ulong64 ChannelID, int *SvcType, int *SvcNum)
{
  TRACEENTER();

  int                   i, NrTVChannels, NrRadioChannels;

  TAP_Channel_GetTotalNum(&NrTVChannels, &NrRadioChannels);

  for(i = 0; i < NrTVChannels; i++)
    if(LogoManager_GetChannelID(SVC_TYPE_Tv, i) == ChannelID)
    {
      if(SvcType) *SvcType = SVC_TYPE_Tv;
      if(SvcNum) *SvcNum = i;

      TRACEEXIT();
      return TRUE;
    }

  for(i = 0; i < NrRadioChannels; i++)
    if(LogoManager_GetChannelID(SVC_TYPE_Radio, i) == ChannelID)
    {
      if(SvcType) *SvcType = SVC_TYPE_Radio;
      if(SvcNum) *SvcNum = i;

      TRACEEXIT();
      return TRUE;
    }


  TRACEEXIT();
  return FALSE;
}
