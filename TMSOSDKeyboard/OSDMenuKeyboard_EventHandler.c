#include                <string.h>
#include                "FBLib_TMSOSDKeyboard.h"

bool OSDMenuKeyboard_EventHandler(word *event, dword *param1, dword *param2)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuKeyboard_EventHandler");
  #endif

  (void) param2;

  if(OSDMenuKeyboard_StringVarOrig == NULL)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  if(!OSDMenuKeyboard_GUIInitialized)
  {
    OSDMenuKeyboard_CursorPosition = strlenUC(OSDMenuKeyboard_StringVar);
    OSDMenuKeyboard_TextStartPosition = 0;
    KeyPadPosition = 0;

    OSDMenuKeyboard_Draw();
    OSDMenuKeyboard_TMSRemoteDirectMode(TRUE);
    OSDMenuKeyboard_GUIInitialized = TRUE;
  }

  switch(*event)
  {
    case EVT_KEY:
    {
      switch(*param1)
      {
        case RKEY_Right:      //Zeichenauswahl rechts
        case RKEY_VolUp:
        {
          KeyPadPosition++;
          switch(KeyPadPosition)
          {
            case  8: KeyPadPosition =  0; break;
            case 16: KeyPadPosition =  8; break;
            case 24: KeyPadPosition = 16; break;
            case 29: KeyPadPosition = 24; break;
          }
          OSDMenuKeyboard_Draw();
          break;
        }

        case RKEY_Left:       //Zeichenauswahl links
        case RKEY_VolDown:
        {
          KeyPadPosition--;

          switch(KeyPadPosition)
          {
            case -1: KeyPadPosition =  7; break;
            case  7: KeyPadPosition = 15; break;
            case 15: KeyPadPosition = 23; break;
            case 23: KeyPadPosition = 28; break;
          }
          OSDMenuKeyboard_Draw();
          break;
        }

        case RKEY_Down:       //Zeichenauswahl hinunter
        case RKEY_ChUp:
        {
          //Spezialbehandlung durch die 2 grossen Tasten
          switch(KeyPadPosition)
          {
            case 18:
            case 19: KeyPadPosition = 26; break;
            case 20:
            case 21: KeyPadPosition = 27; break;
            case 22:
            case 23: KeyPadPosition = 28; break;
            case 24: KeyPadPosition =  0; break;
            case 25: KeyPadPosition =  1; break;
            case 26: KeyPadPosition =  2; break;
            case 27: KeyPadPosition =  4; break;
            case 28: KeyPadPosition =  6; break;

            default: KeyPadPosition += 8;
          }
          OSDMenuKeyboard_Draw();
          break;
        }

        case RKEY_Up:         //Zeichenauswahl hoch
        case RKEY_ChDown:
        {
          //Spezialbehandlung durch die 2 grossen Tasten
          switch(KeyPadPosition)
          {
            case  0: KeyPadPosition = 24; break;
            case  1: KeyPadPosition = 25; break;
            case  2:
            case  3: KeyPadPosition = 26; break;
            case  4:
            case  5: KeyPadPosition = 27; break;
            case  6:
            case  7: KeyPadPosition = 28; break;
            case 27: KeyPadPosition = 20; break;
            case 28: KeyPadPosition = 22; break;
            default: KeyPadPosition -= 8;
          }
          OSDMenuKeyboard_Draw();
          break;
        }

        case RKEY_Next:       //Cursor rechts
        {
          OSDMenuKeyboard_CursorRight();
          break;
        }

        case RKEY_Prev:       //Cursor links
        {
          OSDMenuKeyboard_CursorLeft();
          break;
        }

        case RKEY_Slow:       //Cursor ans Ende
        {
          OSDMenuKeyboard_CursorEnd();
          break;
        }

        case RKEY_Ok:         //Zeichen übernehmen
        {
          switch(KeyPadPosition)
          {
            case 26:
            {
              if(strlen(OSDMenuKeyboard_StringVar) < OSDMenuKeyboard_StringMaxLen)
              {
                InsertAt(OSDMenuKeyboard_StringVar, OSDMenuKeyboard_CursorPosition, " ");
                OSDMenuKeyboard_CursorPosition++;
                OSDMenuKeyboard_Draw();
              }
              break;
            }

            case 27:
            {
              OSDMenuKeyboard_DeleteLeft();
              break;
            }

            case 28:
            {
              OSDMenuKeyboard_SaveAndFinish();

              #ifdef DEBUG_FIREBIRDLIB
                CallTraceExit(NULL);
              #endif

              return TRUE;
            }

            default:
            {
              if(strlen(OSDMenuKeyboard_StringVar) < OSDMenuKeyboard_StringMaxLen)
              {
                InsertAt(OSDMenuKeyboard_StringVar, OSDMenuKeyboard_CursorPosition, Keypad[KeyPadMode][KeyPadPosition]);
                OSDMenuKeyboard_CursorPosition++;
                OSDMenuKeyboard_Draw();
              }
            }
          }
          break;
        }

        case RKEY_Info:       //Zeichensatz ändern
        case RKEY_Play:
        {
          KeyPadMode++;
          if(KeyPadMode >= KPM_NrModes) KeyPadMode = 0;
          OSDMenuKeyboard_Draw();
          break;
        }

        case RKEY_Pause:      //Zwischen normalen und CAPS Zeichen wechseln
        {
          if(KeyPadMode == KPM_Standard)
            KeyPadMode = KPM_CAPS;
          else
            KeyPadMode = KPM_Standard;
          OSDMenuKeyboard_Draw();
          break;
        }

        case RKEY_Forward:    //Zeichen rechts löschen
        {
          OSDMenuKeyboard_DeleteRight();
          break;
        }

        case RKEY_Rewind:     //Zeichen links löschen
        {
          OSDMenuKeyboard_DeleteLeft();
          break;
        }

        case RKEY_Recall:     //Original wiederherstellen
        {
          memset(OSDMenuKeyboard_StringVar, 0, OSDMenuKeyboard_StringMaxLen + 4);
          strncpy(OSDMenuKeyboard_StringVar, OSDMenuKeyboard_StringVarOrig, OSDMenuKeyboard_StringMaxLen);
          StrMkUTF8(OSDMenuKeyboard_StringVar, 9);
          OSDMenuKeyboard_CursorPosition = strlenUC(OSDMenuKeyboard_StringVar);
          OSDMenuKeyboard_Draw();
          break;
        }

        case RKEY_Blue:       //Gesamten Text löschen
        {
          memset(OSDMenuKeyboard_StringVar, 0, OSDMenuKeyboard_StringMaxLen + 4);
          OSDMenuKeyboard_CursorPosition = 0;
          OSDMenuKeyboard_Draw();
          break;
        }

        case RKEY_Yellow:     //Add *text*
        {
          if((strlen(OSDMenuKeyboard_StringVar) < OSDMenuKeyboard_StringMaxLen) && (OSDMenuKeyboard_StringVar[0] != '*')) InsertAt(OSDMenuKeyboard_StringVar, 0, "*");
          if((strlen(OSDMenuKeyboard_StringVar) < OSDMenuKeyboard_StringMaxLen) && (OSDMenuKeyboard_StringVar[strlen(OSDMenuKeyboard_StringVar) - 1] != '*')) strcat(OSDMenuKeyboard_StringVar, "*");
          OSDMenuKeyboard_Draw();
          break;
        }

        case RKEY_Exit:       //Speichern und beenden
        {
          OSDMenuKeyboard_SaveAndFinish();

          #ifdef DEBUG_FIREBIRDLIB
            CallTraceExit(NULL);
          #endif

          return TRUE;
        }
      }
      *param1 = 0;
      break;
    }

    case EVT_TMSREMOTEASCII:
    {
      switch(*param1)
      {
        case 0x08:    //BS
        {
          OSDMenuKeyboard_DeleteLeft();
          break;
        }

        case 0x0D:    //CR
        {
          OSDMenuKeyboard_SaveAndFinish();

          #ifdef DEBUG_FIREBIRDLIB
            CallTraceExit(NULL);
          #endif

          return TRUE;
        }

        case 0x1B:    //ESC
        {
          OSDMenuKeyboard_SaveAndFinish();

          #ifdef DEBUG_FIREBIRDLIB
            CallTraceExit(NULL);
          #endif

          return TRUE;
        }

        case 0x7f:    //Del
        {
          OSDMenuKeyboard_DeleteRight();
          break;
        }

        case 0x0124:  //Pos1
        {
          OSDMenuKeyboard_CursorPosition = 0;
          OSDMenuKeyboard_Draw();
          break;
        }

        case 0x0123:  //End
        {
          OSDMenuKeyboard_CursorPosition = strlen(OSDMenuKeyboard_StringVar);
          OSDMenuKeyboard_Draw();
          break;
        }

        case 0x0125:  //Left
        {
          OSDMenuKeyboard_CursorLeft();
          break;
        }

        case 0x0127:  //Right
        {
          OSDMenuKeyboard_CursorRight();
          break;
        }

        case 0x0170:   //F1 = RED
        {
          OSDMenuKeyboard_Finish();

          #ifdef DEBUG_FIREBIRDLIB
            CallTraceExit(NULL);
          #endif

          return TRUE;
        }

        case 0x0171:   //F2 = GREEN
        {
          OSDMenuKeyboard_SaveAndFinish();

          #ifdef DEBUG_FIREBIRDLIB
            CallTraceExit(NULL);
          #endif

          return TRUE;
        }

        case 0x0173:   //F4 = BLUE
        {
          memset(OSDMenuKeyboard_StringVar, 0, OSDMenuKeyboard_StringMaxLen + 4);
          OSDMenuKeyboard_CursorPosition = 0;
          OSDMenuKeyboard_Draw();
          break;
        }

        default:
        {
          //ASCII Codes
          if((*param1 < 0x100) && (((*param1 >= 0x20) && (*param1 < 0x7f)) || (*param1 >= 0xa0)))
          {
            if(strlen(OSDMenuKeyboard_StringVar) < OSDMenuKeyboard_StringMaxLen)
            {
              char          ToBeInserted[8];

              ToBeInserted[0] = *param1;
              ToBeInserted[1] = '\0';
              StrMkUTF8(ToBeInserted, 9);
              InsertAt(OSDMenuKeyboard_StringVar, OSDMenuKeyboard_CursorPosition, ToBeInserted);
              OSDMenuKeyboard_CursorPosition++;
              OSDMenuKeyboard_Draw();
            }
          }
        }
      }
      break;
    }
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return FALSE;
}
