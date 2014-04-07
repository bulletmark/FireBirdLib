#include                "FBLib_TMSOSDMenu.h"

tButtonIcon OSDMenuGetButtonIcon(dword key)
{
  TRACEENTER();

  tButtonIcon ret = BI_None;

  switch(key)
  {
    case 0:             ret = BI_None; break;
    case RKEY_0:        ret = BI_0; break;
    case RKEY_1:        ret = BI_1; break;
    case RKEY_2:        ret = BI_2; break;
    case RKEY_3:        ret = BI_3; break;
    case RKEY_4:        ret = BI_4; break;
    case RKEY_5:        ret = BI_5; break;
    case RKEY_6:        ret = BI_6; break;
    case RKEY_7:        ret = BI_7; break;
    case RKEY_8:        ret = BI_8; break;
    case RKEY_9:        ret = BI_9; break;
    case RKEY_Uhf:      ret = BI_AR; break;
    case RKEY_AudioTrk: ret = BI_Audio; break;
    //case RKEY_:       ret = BI_Aux; break;
    case RKEY_Blue:     ret = BI_Blue; break;
    case RKEY_Ab:       ret = BI_Cut; break;
    case RKEY_Down:     ret = BI_Down; break;
    case RKEY_Exit:     ret = BI_Exit; break;
    case RKEY_Fav:      ret = BI_Fav; break;
    case RKEY_Forward:  ret = BI_Ffwd; break;
    case RKEY_PlayList: ret = BI_FileList; break;
    case RKEY_Green:    ret = BI_Green; break;
    case RKEY_Guide:    ret = BI_Guide; break;
    case RKEY_Info:     ret = BI_Info; break;
    case RKEY_Next:     ret = BI_JumpEnd; break;
    case RKEY_Prev:     ret = BI_JumpStart; break;
    case RKEY_Left:     ret = BI_Left; break;
    //case RKEY_:       ret = BI_List; break;
    case RKEY_TvSat:    ret = BI_M; break;
    case RKEY_Menu:     ret = BI_Menu; break;
    case RKEY_Mute:     ret = BI_Mute; break;
    case RKEY_Ok:       ret = BI_Ok; break;
    //case RKEY_:       ret = BI_Option; break;
    case RKEY_Pause:    ret = BI_Pause; break;
    case RKEY_Play:     ret = BI_Play; break;
    case RKEY_ChDown:   ret = BI_ProgMinus; break;
    case RKEY_ChUp:     ret = BI_ProgPlus; break;
    case RKEY_Recall:   ret = BI_Recall; break;
    case RKEY_Record:   ret = BI_Record; break;
    case RKEY_Red:      ret = BI_Red; break;
    case RKEY_Right:    ret = BI_Right; break;
    case RKEY_Rewind:   ret = BI_Rwd; break;
    case RKEY_Sat:      ret = BI_Sat; break;
    //case RKEY_:       ret = BI_Select; break;
    case RKEY_Sleep:    ret = BI_Sleep; break;
    case RKEY_Slow:     ret = BI_Step; break;
    case RKEY_Stop:     ret = BI_Stop; break;
    case RKEY_Subt:     ret = BI_Subtitle; break;
    case RKEY_Teletext: ret = BI_TTX; break;
    case RKEY_TvRadio:  ret = BI_TV_Radio; break;
    case RKEY_Up:       ret = BI_Up; break;
    case RKEY_VFormat:  ret = BI_VF; break;
    case RKEY_VolDown:  ret = BI_VolMinus; break;
    case RKEY_VolUp:    ret = BI_VolPlus; break;
    case RKEY_White:    ret = BI_White; break;
    case RKEY_Yellow:   ret = BI_Yellow; break;
  }

  TRACEEXIT();
  return ret;
}
