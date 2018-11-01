#include                <string.h>
#include                <stdlib.h>
#include                "FBLib_TMSOSDKeyboard.h"
#include                "TMSOSDMenu/graphic/TextCursor14.gd"

bool                    OSDMenuKeyboard_GUIInitialized = FALSE;

char                   *OSDMenuKeyboard_Title = NULL;
char                   *OSDMenuKeyboard_StringVar = NULL;
char                   *OSDMenuKeyboard_StringVarOrig = NULL;
dword                   OSDMenuKeyboard_StringMaxLen = 0;
int                     OSDMenuKeyboard_CursorPosition = 0;
int                     OSDMenuKeyboard_TextStartPosition = 0;
int                     OSDMenuKeyboard_ButtonsX[3];
tOSDMenuKeyboard_Buttons OSDMenuKeyboard_Buttons[20];
int                     OSDMenuKeyboard_NrButtons = 0;

char                    Keypad[KPM_NrModes][26][4] = {{"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"},
                                                      {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"},
                                                      {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "\u00e4", "\u00c4", "\u00f6", "\u00d6", "\u00fc", "\u00dc", "\u00df", ",", ";", ".", ":", "-", "_", "=", "?", "+"},
                                                     //                                                   ä         Ä         ö         Ö         ü         Ü         ß
                                                      {"!", "\"","§", "$", "%", "&", "/", "(", ")", "[", "]", "{", "}", "<", ">", "@", "*", "#", "|", "^", "~", "°", "'", " ", " ", " "},
                                                      {"\u00c0", "\u00e0", "\u00c1", "\u00e1", "\u00c2", "\u00e2", "\u00c3", "\u00e3", "\u00c5", "\u00e5", "\u00c6", "\u00e6", "\u00c7", "\u00e7", "\u00c8", "\u00e8", "\u00c9", "\u00e9", "\u00ca", "\u00ea", "\u00cb", "\u00eb", "\u00d0", "\u00f0", " ", " "},
                                                     // À         à         Á         á         Â         â         Ã         ã         Å         å          Æ        æ         Ç         ç         È         è         É         é         Ê         ê         Ë         ë         Ð         ð
                                                      {"\u00cc", "\u00ec", "\u00cd", "\u00ed", "\u00ce", "\u00ee", "\u00cf", "\u00ef", "\u00d1", "\u00f1", "\u00d2", "\u00f2", "\u00d3", "\u00f3", "\u00d4", "\u00f4", "\u00d5", "\u00f5", "\u00d8", "\u00f8", "\u00d9", "\u00f9", "\u00da", "\u00fa", "\u00db", "\u00fb"},
                                                     // Ì         ì         Í         í         Î         î         Ï         ï         Ñ         ñ         Ò         ò         Ó         ó         Ô         ô         Õ         õ         Ø         ø         Ù         ù         Ú         ú         Û         û
                                                      {"\u00dd", "\u00fd", "\u00de", "\u00fe", "\u00b5", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "}};
                                                     // Ý         ý         Þ         þ         µ


tKeyPadMode             KeyPadMode = KPM_Standard;
int                     KeyPadPosition = 0;
word                    OSDMenuKeyboard_rgn = 0;
bool                    OSDMenuKeyboard_ReturnToNormal;
tFontDataUC             KeyboardFont_12, KeyboardFont_14;

void OSDMenuKeyboard_Setup(char *Title, char *Variable, dword MaxLength)
{
  TRACEENTER();

  OSDMenuKeyboard_Title = TAP_MemAlloc(strlen(Title) + 1);
  strcpy(OSDMenuKeyboard_Title, Title);
  OSDMenuKeyboard_StringVar = TAP_MemAlloc(MaxLength + 4);
  memset(OSDMenuKeyboard_StringVar, 0, MaxLength + 4);

  strncpy(OSDMenuKeyboard_StringVar, Variable, MaxLength);
  StrMkUTF8(OSDMenuKeyboard_StringVar, 9);

  OSDMenuKeyboard_TextStartPosition = 0;
  OSDMenuKeyboard_NrButtons = 0;
  OSDMenuKeyboard_ButtonsX[0] = 10;
  OSDMenuKeyboard_ButtonsX[1] = 10;
  OSDMenuKeyboard_ButtonsX[2] = 10;

  OSDMenuKeyboard_StringVarOrig = Variable;

  OSDMenuKeyboard_StringMaxLen = MaxLength;

  FMUC_LoadFontFile("Calibri_12.ufnt", &KeyboardFont_12);
  FMUC_LoadFontFile("Calibri_14.ufnt", &KeyboardFont_14);

  TRACEEXIT();
}
