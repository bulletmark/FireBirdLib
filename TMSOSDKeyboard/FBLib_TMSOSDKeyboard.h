#ifndef FBLIB_TMSOSDKEYBOARD_H
  #define FBLIB_TMSOSDKEYBOARD_H

  #include              "libFireBird.h"
  #include              "OSDMenuKeyboard_Colors.h"
  #include              "TMSRemote_TAPCOM.h"

  #define BUTTONTEXTSIZE  23
  #define NRKEYPADKEYS    29

  typedef struct
  {
    dword               Line;
    tButtonIcon         ButtonIcon;
    char                Text[BUTTONTEXTSIZE];
  } tOSDMenuKeyboard_Buttons;

  extern bool           OSDMenuKeyboard_GUIInitialized;

  extern char          *OSDMenuKeyboard_Title;
  extern char          *OSDMenuKeyboard_StringVar;
  extern char          *OSDMenuKeyboard_StringVarOrig;
  extern dword          OSDMenuKeyboard_StringMaxSize;
  extern int            OSDMenuKeyboard_CursorPosition;
  extern int            OSDMenuKeyboard_TextStartPosition;
  extern int            OSDMenuKeyboard_ButtonsX[3];
  extern tOSDMenuKeyboard_Buttons OSDMenuKeyboard_Buttons[20];
  extern int            OSDMenuKeyboard_NrButtons;
  extern char           Keypad[KPM_NrModes][26][4];
  extern tKeyboardCursor KeyboardCursorType;
  extern tKeyPadMode    KeyPadMode;
  extern int            KeyPadPosition;
  extern word           OSDMenuKeyboard_rgn;
  extern bool           OSDMenuKeyboard_ReturnToNormal;
  extern bool           AutomaticLowerCase;
  extern tFontDataUC    KeyboardFont_12, KeyboardFont_14;

  void OSDMenuKeyboard_Draw(void);
  void OSDMenuKeyboard_DrawLegendButton(dword Line, tButtonIcon ButtonIcon, const char *Text);
  void OSDMenuKeyboard_TMSRemoteDirectMode(bool DirectMode);
  void OSDMenuKeyboard_CursorRight(void);
  void OSDMenuKeyboard_CursorLeft(void);
  void OSDMenuKeyboard_CursorEnd(void);
  void OSDMenuKeyboard_DeleteRight(void);
  void OSDMenuKeyboard_DeleteLeft(void);
  void OSDMenuKeyboard_Finish(void);
  void OSDMenuKeyboard_SaveAndFinish(void);

#endif
