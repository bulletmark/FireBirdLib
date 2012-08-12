#include                "FBLib_TMSOSDMenu.h"

tButtonIcon OSDMenuGetButtonIcon(dword key)
{
  switch(key)
  {
    case 0:             return BI_None;
    case RKEY_0:        return BI_0;
    case RKEY_1:        return BI_1;
    case RKEY_2:        return BI_2;
    case RKEY_3:        return BI_3;
    case RKEY_4:        return BI_4;
    case RKEY_5:        return BI_5;
    case RKEY_6:        return BI_6;
    case RKEY_7:        return BI_7;
    case RKEY_8:        return BI_8;
    case RKEY_9:        return BI_9;
    case RKEY_Uhf:      return BI_AR;
    case RKEY_AudioTrk: return BI_Audio;
    //case RKEY_:       return BI_Aux;
    case RKEY_Blue:     return BI_Blue;
    case RKEY_Ab:       return BI_Cut;
    case RKEY_Down:     return BI_Down;
    case RKEY_Exit:     return BI_Exit;
    case RKEY_Fav:      return BI_Fav;
    case RKEY_Forward:  return BI_Ffwd;
    case RKEY_PlayList: return BI_FileList;
    case RKEY_Green:    return BI_Green;
    case RKEY_Guide:    return BI_Guide;
    case RKEY_Info:     return BI_Info;
    case RKEY_Next:     return BI_JumpEnd;
    case RKEY_Prev:     return BI_JumpStart;
    case RKEY_Left:     return BI_Left;
    //case RKEY_:       return BI_List;
    case RKEY_TvSat:    return BI_M;
    case RKEY_Menu:     return BI_Menu;
    case RKEY_Mute:     return BI_Mute;
    case RKEY_Ok:       return BI_Ok;
    //case RKEY_:       return BI_Option;
    case RKEY_Pause:    return BI_Pause;
    case RKEY_Play:     return BI_Play;
    case RKEY_ChDown:   return BI_ProgMinus;
    case RKEY_ChUp:     return BI_ProgPlus;
    case RKEY_Recall:   return BI_Recall;
    case RKEY_Record:   return BI_Record;
    case RKEY_Red:      return BI_Red;
    case RKEY_Right:    return BI_Right;
    case RKEY_Rewind:   return BI_Rwd;
    case RKEY_Sat:      return BI_Sat;
    //case RKEY_:       return BI_Select;
    case RKEY_Sleep:    return BI_Sleep;
    case RKEY_Slow:     return BI_Step;
    case RKEY_Stop:     return BI_Stop;
    case RKEY_Subt:     return BI_Subtitle;
    case RKEY_Teletext: return BI_TTX;
    case RKEY_TvRadio:  return BI_TV_Radio;
    case RKEY_Up:       return BI_Up;
    case RKEY_VFormat:  return BI_VF;
    case RKEY_VolDown:  return BI_VolMinus;
    case RKEY_VolUp:    return BI_VolPlus;
    case RKEY_White:    return BI_White;
    case RKEY_Yellow:   return BI_Yellow;
  }

  return BI_None;
}
