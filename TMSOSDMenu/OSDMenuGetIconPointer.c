#include                "FBLib_TMSOSDMenu.h"

TYPE_GrData *OSDMenuGetIconPointer(tButtonIcon ButtonIcon, TYPE_GrData *UserDefinedButton)
{
  TRACEENTER;

  TYPE_GrData *ret = NULL;
  switch(ButtonIcon)
  {
    case BI_None        : ret = NULL; break;
    case BI_0           : ret = &_Button_0_Gd; break;
    case BI_1           : ret = &_Button_1_Gd; break;
    case BI_2           : ret = &_Button_2_Gd; break;
    case BI_3           : ret = &_Button_3_Gd; break;
    case BI_4           : ret = &_Button_4_Gd; break;
    case BI_5           : ret = &_Button_5_Gd; break;
    case BI_6           : ret = &_Button_6_Gd; break;
    case BI_7           : ret = &_Button_7_Gd; break;
    case BI_8           : ret = &_Button_8_Gd; break;
    case BI_9           : ret = &_Button_9_Gd; break;
    case BI_AR          : ret = &_Button_ar_Gd; break;
    case BI_Audio       : ret = &_Button_audio_Gd; break;
    case BI_Aux         : ret = &_Button_aux_Gd; break;
    case BI_Blue        : ret = &_Button_blue_Gd; break;
    case BI_Cut         : ret = &_Button_cut_Gd; break;
    case BI_Down        : ret = &_Button_down_Gd; break;
    case BI_Exit        : ret = &_Button_exit_Gd; break;
    case BI_Fav         : ret = &_Button_fav_Gd; break;
    case BI_Ffwd        : ret = &_Button_ffwd_Gd; break;
    case BI_FileList    : ret = &_Button_filelist_Gd; break;
    case BI_Green       : ret = &_Button_green_Gd; break;
    case BI_Guide       : ret = &_Button_guide_Gd; break;
    case BI_Info        : ret = &_Button_info_Gd; break;
    case BI_JumpEnd     : ret = &_Button_jumpend_Gd; break;
    case BI_JumpStart   : ret = &_Button_jumpstart_Gd; break;
    case BI_Left        : ret = &_Button_left_Gd; break;
    case BI_List        : ret = &_Button_list_Gd; break;
    case BI_M           : ret = &_Button_m_Gd; break;
    case BI_Menu        : ret = &_Button_menu_Gd; break;
    case BI_Mute        : ret = &_Button_mute_Gd; break;
    case BI_Ok          : ret = &_Button_ok_Gd; break;
    case BI_Option      : ret = &_Button_option_Gd; break;
    case BI_Pause       : ret = &_Button_pause_Gd; break;
    case BI_Play        : ret = &_Button_play_Gd; break;
    case BI_ProgMinus   : ret = &_Button_progminus_Gd; break;
    case BI_ProgPlus    : ret = &_Button_progplus_Gd; break;
    case BI_Recall      : ret = &_Button_recall_Gd; break;
    case BI_Record      : ret = &_Button_record_Gd; break;
    case BI_Red         : ret = &_Button_red_Gd; break;
    case BI_Right       : ret = &_Button_right_Gd; break;
    case BI_Rwd         : ret = &_Button_rwd_Gd; break;
    case BI_Sat         : ret = &_Button_sat_Gd; break;
    case BI_Select      : ret = &_Button_select_Gd; break;
    case BI_Sleep       : ret = &_Button_sleep_Gd; break;
    case BI_Step        : ret = &_Button_step_Gd; break;
    case BI_Stop        : ret = &_Button_stop_Gd; break;
    case BI_Subtitle    : ret = &_Button_subtitle_Gd; break;
    case BI_TTX         : ret = &_Button_ttx_Gd; break;
    case BI_TV_Radio    : ret = &_Button_tv_radio_Gd; break;
    case BI_Up          : ret = &_Button_up_Gd; break;
    case BI_VF          : ret = &_Button_vf_Gd; break;
    case BI_VolMinus    : ret = &_Button_volminus_Gd; break;
    case BI_VolPlus     : ret = &_Button_volplus_Gd; break;
    case BI_White       : ret = &_Button_white_Gd; break;
    case BI_Yellow      : ret = &_Button_yellow_Gd; break;
    case BI_NoUse       : ret = &_Button_nouse_Gd; break;
    case BI_UserDefined : ret = UserDefinedButton; break;
  }

  TRACEEXIT;
  return ret;
}
