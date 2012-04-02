#include                "FBLib_TMSOSDMenu.h"

TYPE_GrData *OSDMenuGetIconPointer(tButtonIcon ButtonIcon, TYPE_GrData *UserDefinedButton)
{
  switch(ButtonIcon)
  {
    case BI_None        : return NULL;
    case BI_0           : return &_Button_0_Gd;
    case BI_1           : return &_Button_1_Gd;
    case BI_2           : return &_Button_2_Gd;
    case BI_3           : return &_Button_3_Gd;
    case BI_4           : return &_Button_4_Gd;
    case BI_5           : return &_Button_5_Gd;
    case BI_6           : return &_Button_6_Gd;
    case BI_7           : return &_Button_7_Gd;
    case BI_8           : return &_Button_8_Gd;
    case BI_9           : return &_Button_9_Gd;
    case BI_AR          : return &_Button_ar_Gd;
    case BI_Audio       : return &_Button_audio_Gd;
    case BI_Aux         : return &_Button_aux_Gd;
    case BI_Blue        : return &_Button_blue_Gd;
    case BI_Cut         : return &_Button_cut_Gd;
    case BI_Down        : return &_Button_down_Gd;
    case BI_Exit        : return &_Button_exit_Gd;
    case BI_Fav         : return &_Button_fav_Gd;
    case BI_Ffwd        : return &_Button_ffwd_Gd;
    case BI_FileList    : return &_Button_filelist_Gd;
    case BI_Green       : return &_Button_green_Gd;
    case BI_Guide       : return &_Button_guide_Gd;
    case BI_Info        : return &_Button_info_Gd;
    case BI_JumpEnd     : return &_Button_jumpend_Gd;
    case BI_JumpStart   : return &_Button_jumpstart_Gd;
    case BI_Left        : return &_Button_left_Gd;
    case BI_List        : return &_Button_list_Gd;
    case BI_M           : return &_Button_m_Gd;
    case BI_Menu        : return &_Button_menu_Gd;
    case BI_Mute        : return &_Button_mute_Gd;
    case BI_Ok          : return &_Button_ok_Gd;
    case BI_Option      : return &_Button_option_Gd;
    case BI_Pause       : return &_Button_pause_Gd;
    case BI_Play        : return &_Button_play_Gd;
    case BI_ProgMinus   : return &_Button_progminus_Gd;
    case BI_ProgPlus    : return &_Button_progplus_Gd;
    case BI_Recall      : return &_Button_recall_Gd;
    case BI_Record      : return &_Button_record_Gd;
    case BI_Red         : return &_Button_red_Gd;
    case BI_Right       : return &_Button_right_Gd;
    case BI_Rwd         : return &_Button_rwd_Gd;
    case BI_Sat         : return &_Button_sat_Gd;
    case BI_Select      : return &_Button_select_Gd;
    case BI_Sleep       : return &_Button_sleep_Gd;
    case BI_Step        : return &_Button_step_Gd;
    case BI_Stop        : return &_Button_stop_Gd;
    case BI_Subtitle    : return &_Button_subtitle_Gd;
    case BI_TTX         : return &_Button_ttx_Gd;
    case BI_TV_Radio    : return &_Button_tv_radio_Gd;
    case BI_Up          : return &_Button_up_Gd;
    case BI_VF          : return &_Button_vf_Gd;
    case BI_VolMinus    : return &_Button_volminus_Gd;
    case BI_VolPlus     : return &_Button_volplus_Gd;
    case BI_White       : return &_Button_white_Gd;
    case BI_Yellow      : return &_Button_yellow_Gd;
    case BI_NoUse       : return &_Button_nouse_Gd;
    case BI_UserDefined : return UserDefinedButton;
  }

  return NULL;
}
