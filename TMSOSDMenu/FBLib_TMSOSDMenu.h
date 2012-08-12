#ifndef FBLIB_TMSOSDMENU_H
#define FBLIB_TMSOSDMENU_H

#include                "../libFireBird.h"

#define ITEMNAMESIZE    128
#define ITEMVALUESIZE   128
#define STDSTRINGSIZE   256
#define NRMENULEVELS     5
#define MAXMBBUTTONS     5
#define FONTYOFFSET     -3

typedef struct
{
  char                  Name[ITEMNAMESIZE];
  char                  Value[ITEMVALUESIZE];
  TYPE_GrData          *pNameIconGd;
  TYPE_GrData          *pValueIconGd;
  dword                 ColorPatch;
  dword                 TextColor;
  bool                  Selectable;
  bool                  ValueArrows;
  dword                 ID;
}tItem;

typedef struct
{
  dword                 X;
  dword                 Y;
  TYPE_GrData          *pButtonGd;
  dword                 Color;
  char                  Text[STDSTRINGSIZE];
}tButtons;

typedef enum
{
  OMDM_Standard,
  OMDM_Memo
} tOSDMenuDisplayMode;

typedef struct
{
  tItem                *Item;
  int                   NrItems;
  int                   MaxItems;
  int                   CurrentSelection;
  int                   CurrentTopIndex;
  bool                  AllowScrollingOfLongText;
  bool                  HasValueColumn;
  dword                 ValueXPos;
  bool                  ScrollLoop;
  bool                  NumberedItems;
  bool                  hasValueArrows;
  tButtons              Buttons[20];
  dword                 NrButtons;
  dword                 ButtonXStart[4];
  char                  TitleLeft[STDSTRINGSIZE];
  char                  TitleRight[STDSTRINGSIZE];
  dword                 LogoX;
  dword                 LogoY;
  TYPE_GrData          *pLogoGd;
  tOSDMenuDisplayMode  OSDMenuDisplayMode;
  tFontData            *FontLeftTitle;
  tFontData            *FontRightTitle;
  tFontData            *FontListLineNumber;
  tFontData            *FontListNameColumn;
  tFontData            *FontListValueColumn;
  tFontData            *FontButtons;
  tFontData            *FontMemo;
}tMenu;

typedef struct
{
  dword                 NrButtons;
  dword                 CurrentButton;
  char                  Button[MAXMBBUTTONS][STDSTRINGSIZE];
  char                  Title[STDSTRINGSIZE];
  char                  Text[STDSTRINGSIZE];
//  tFontData            *FontColorPickerTitle;
//  tFontData            *FontColorPickerCursor;
}tMessageBox;

typedef enum
{
  CCS_Red,
  CCS_Green,
  CCS_Blue
}tCurrentColorSelected;

extern tFontData        Calibri_10_FontData;
extern tFontData        Calibri_12_FontData;
extern tFontData        Calibri_14_FontData;
extern tFontData        Calibri_16_FontData;
extern tFontData        Calibri_18_FontData;
extern tFontData        Calibri_20_FontData;
extern tFontData        Calibri_20B_FontData;

extern TYPE_GrData      _Button_0_Gd;
extern TYPE_GrData      _Button_1_Gd;
extern TYPE_GrData      _Button_2_Gd;
extern TYPE_GrData      _Button_3_Gd;
extern TYPE_GrData      _Button_4_Gd;
extern TYPE_GrData      _Button_5_Gd;
extern TYPE_GrData      _Button_6_Gd;
extern TYPE_GrData      _Button_7_Gd;
extern TYPE_GrData      _Button_8_Gd;
extern TYPE_GrData      _Button_9_Gd;
extern TYPE_GrData      _Button_ar_Gd;
extern TYPE_GrData      _Button_audio_Gd;
extern TYPE_GrData      _Button_aux_Gd;
extern TYPE_GrData      _Button_blue_Gd;
extern TYPE_GrData      _Button_cut_Gd;
extern TYPE_GrData      _Button_down_Gd;
extern TYPE_GrData      _Button_exit_Gd;
extern TYPE_GrData      _Button_fav_Gd;
extern TYPE_GrData      _Button_ffwd_Gd;
extern TYPE_GrData      _Button_filelist_Gd;
extern TYPE_GrData      _Button_green_Gd;
extern TYPE_GrData      _Button_guide_Gd;
extern TYPE_GrData      _Button_info_Gd;
extern TYPE_GrData      _Button_jumpend_Gd;
extern TYPE_GrData      _Button_jumpstart_Gd;
extern TYPE_GrData      _Button_left_Gd;
extern TYPE_GrData      _Button_list_Gd;
extern TYPE_GrData      _Button_m_Gd;
extern TYPE_GrData      _Button_menu_Gd;
extern TYPE_GrData      _Button_mute_Gd;
extern TYPE_GrData      _Button_nouse_Gd;
extern TYPE_GrData      _Button_ok_Gd;
extern TYPE_GrData      _Button_option_Gd;
extern TYPE_GrData      _Button_pause_Gd;
extern TYPE_GrData      _Button_play_Gd;
extern TYPE_GrData      _Button_progminus_Gd;
extern TYPE_GrData      _Button_progplus_Gd;
extern TYPE_GrData      _Button_recall_Gd;
extern TYPE_GrData      _Button_record_Gd;
extern TYPE_GrData      _Button_red_Gd;
extern TYPE_GrData      _Button_right_Gd;
extern TYPE_GrData      _Button_rwd_Gd;
extern TYPE_GrData      _Button_sat_Gd;
extern TYPE_GrData      _Button_select_Gd;
extern TYPE_GrData      _Button_sleep_Gd;
extern TYPE_GrData      _Button_step_Gd;
extern TYPE_GrData      _Button_stop_Gd;
extern TYPE_GrData      _Button_subtitle_Gd;
extern TYPE_GrData      _Button_ttx_Gd;
extern TYPE_GrData      _Button_tv_radio_Gd;
extern TYPE_GrData      _Button_up_Gd;
extern TYPE_GrData      _Button_vf_Gd;
extern TYPE_GrData      _Button_volminus_Gd;
extern TYPE_GrData      _Button_volplus_Gd;
extern TYPE_GrData      _Button_white_Gd;
extern TYPE_GrData      _Button_yellow_Gd;

extern TYPE_GrData      _InfoBox_Gd;
extern TYPE_GrData      _Messagebox_Gd;
extern TYPE_GrData      _MessageBoxSelectedButtonBackground_Gd;
extern TYPE_GrData      _ScrollBarInvisible_Gd;
extern TYPE_GrData      _ScrollBarKnob_Gd;
extern TYPE_GrData      _ScrollBarVisible_Gd;
extern TYPE_GrData      _Selection_Bar_Gd;

extern TYPE_GrData      _ColorPicker_Gd;
extern TYPE_GrData      _ColorPicker_CursorNone_Gd;
extern TYPE_GrData      _ColorPicker_CursorDeselected_Gd;
extern TYPE_GrData      _ColorPicker_ValueBackroundSelected_Gd;

extern word             OSDRgn;
extern word             MyOSDRgn; //Used by OSDMenuSaveMyRegion()
extern bool             OSDDirty, TitleDirty, ListDirty, ButtonsDirty, LogoDirty;
extern tMenu            Menu[NRMENULEVELS];
extern dword            CurrentMenuLevel;
extern dword            ButtonColor;
extern tCursorType      MenuCursorType;

extern word             InfoBoxOSDRgn;
extern dword            InfoBoxTimeOut;
extern byte            *InfoBoxSaveArea;
extern dword            InfoBoxSaveAreaX, InfoBoxSaveAreaY;

extern word             MessageBoxOSDRgn;
extern tMessageBox      MessageBox;
extern bool             MessageBoxNoNormalMode;

extern word             ProgressBarOSDRgn;
extern word             ProgressBarFullRgn;
extern dword            ProgressBarLastValue;

extern word             ColorPickerOSDRgn;
extern dword            ColorPickerColor;
extern dword            ColorPickerDefaultColor;
extern tCurrentColorSelected  CurrentColorSelected;
extern int              ColorPickerLastCursorRed, ColorPickerLastCursorGreen, ColorPickerLastCursorBlue;

int  OSDMenuGetW(const char * str, byte fntSize);
TYPE_GrData *OSDMenuGetIconPointer(tButtonIcon ButtonIcon, TYPE_GrData *UserDefinedButton);
int  OSDMenuFindNextSelectableEntry(int CurrentSelection);
int  OSDMenuFindPreviousSelectableEntry(int CurrentSelection);
void OSDMenuPutS(word rgn, dword x, dword y, dword maxX, const char * str, dword fcolor, dword bcolor, byte fntSize, byte bDot, byte align);
void OSDDrawBackground(void);
void OSDMenuDrawCursor(dword x, dword y, dword w);
void OSDDrawTitle(void);
void OSDDrawLogo(void);
void OSDDrawButtons(void);
void OSDCalcIndices(void);
void OSDDrawScrollBar(void);
void OSDDrawList(void);
void OSDDrawMemo(void);
void OSDMenuColorPickerDrawCursor(tCurrentColorSelected CursorColor, bool Selected);

extern void (*CallbackProcedure)(tOSDCB OSDCBType, word OSDRgn);


#endif
