/*
    TAP to edit DST.INI for use with EPGInfo functions in libFireBird.
    Built on a skeleton of FireBird's TMSOSDMenuDemo

    TAP History.
    ============

    Ver     Date        Author              Description
    ===     ====        ======              ===========
    v0.01   2013-04-09  DeltaMikeCharlie    Initial version.
    v0.02   2013-04-12  FireBird            Refine German translation and add tLangStrings logic.
    v0.03   2013-04-23  DeltaMikeCharlie    Add ability to save with F2(Green) or Rec.
                                            Add KeyTranslate for 7000 series RCUs.
*/

#include                "stdio.h"
#include                "stdlib.h"
#include                "string.h"

#include                "tap.h"
#include                "libFireBird.h"

#define PROGRAM_NAME    "DSTConfig"
#define VERSION         "v0.03"

TAP_ID                  (0x444D430D);           //DMC13
TAP_PROGRAM_NAME        (PROGRAM_NAME" "VERSION);
TAP_AUTHOR_NAME         ("DeltaMikeCharlie");
TAP_DESCRIPTION         ("Configure DST.INI");
TAP_ETCINFO             (__DATE__);

#define LNGFILENAME     PROGRAM_NAME ".lng"
#define MANUALDSTINI    "DST.ini"


typedef enum
{
  ST_Init,
  ST_Idle,
  ST_YesNoDialogue,
  ST_YesNoDialogueSave,
  ST_Exit
} tState;

typedef enum
{
  lng_Header,             //00

  lng_Firmware,
  lng_Europe,
  lng_Manual,

  lng_First,
  lng_Second,
  lng_Third,
  lng_Fourth,
  lng_Fifth,

  lng_Mon,
  lng_Tue,                //10
  lng_Wed,
  lng_Thu,
  lng_Fri,
  lng_Sat,
  lng_Sun,

  lng_Jan,
  lng_Feb,
  lng_Mar,
  lng_Apr,
  lng_May,                //20
  lng_Jun,
  lng_Jul,
  lng_Aug,
  lng_Sep,
  lng_Oct,
  lng_Nov,
  lng_Dec,

  lng_DSTRule,
  lng_NextDSTStart,
  lng_NextDSTEnd,         //30
  lng_FirmwareTimeZone,

  lng_BtnExit,
  lng_BtnSave,
  lng_BtnReload,

  lng_Yes,
  lng_No,

  lng_Exit,
  lng_Save,

  lng_OFF,
  lng_ON,                 //40
  lng_Unknown,

  lng_Ordinal,
  lng_Weekday,
  lng_Month,
  lng_Hour,
  lng_Minute,

  lng_NRLNGITEMS
} tLangStrings;

    tState                  State = ST_Init;

    char                    fwDSTZone[32];

    char                    dstStartString[64];
    char                    dstStartHourString[8];
    char                    dstStartMinString[8];

    char                    dstEndString[64];
    char                    dstEndHourString[8];
    char                    dstEndMinString[8];


    char                    setMode[3][32];
    char                    setOrdinal[6][32];
    char                    setDay[7][32];
    char                    setMonth[13][32];

    byte                    currentMode = 0;
    byte                    currentStartOrd = 1;
    byte                    currentStartDay = 0;
    byte                    currentStartMonth = 1;
    byte                    currentStartHour = 0;
    byte                    currentStartMin = 0;
    byte                    currentEndOrd = 1;
    byte                    currentEndDay = 0;
    byte                    currentEndMonth = 1;
    byte                    currentEndHour = 0;
    byte                    currentEndMin = 0;


void loadLanguageStrings()
{

	if (!LangLoadStrings(LNGFILENAME, lng_NRLNGITEMS, LAN_English, PROGRAM_NAME))
	{
		//TAP_Print("Language file not found - default to English");
	}

    strcpy(setMode[0], LangGetStringDefault(lng_Firmware, "Firmware"));
    strcpy(setMode[1], LangGetStringDefault(lng_Europe, "Europe"));
    strcpy(setMode[2], LangGetStringDefault(lng_Manual, "Manual"));

    //First entry is index 1 to align with INI settings.
    strcpy(setOrdinal[1], LangGetStringDefault(lng_First, "First"));
    strcpy(setOrdinal[2], LangGetStringDefault(lng_Second, "Second"));
    strcpy(setOrdinal[3], LangGetStringDefault(lng_Third, "Third"));
    strcpy(setOrdinal[4], LangGetStringDefault(lng_Fourth, "Fourth"));
    strcpy(setOrdinal[5], LangGetStringDefault(lng_Fifth, "Fifth/Last"));

    strcpy(setDay[0], LangGetStringDefault(lng_Mon, "Mon"));
    strcpy(setDay[1], LangGetStringDefault(lng_Tue, "Tue"));
    strcpy(setDay[2], LangGetStringDefault(lng_Wed, "Wed"));
    strcpy(setDay[3], LangGetStringDefault(lng_Thu, "Thu"));
    strcpy(setDay[4], LangGetStringDefault(lng_Fri, "Fri"));
    strcpy(setDay[5], LangGetStringDefault(lng_Sat, "Sat"));
    strcpy(setDay[6], LangGetStringDefault(lng_Sun, "Sun"));

    //First entry is index 1 to align with INI settings.
    strcpy(setMonth[1], LangGetStringDefault(lng_Jan, "Jan"));
    strcpy(setMonth[2], LangGetStringDefault(lng_Feb, "Feb"));
    strcpy(setMonth[3], LangGetStringDefault(lng_Mar, "Mar"));
    strcpy(setMonth[4], LangGetStringDefault(lng_Apr, "Apr"));
    strcpy(setMonth[5], LangGetStringDefault(lng_May, "May"));
    strcpy(setMonth[6], LangGetStringDefault(lng_Jun, "Jun"));
    strcpy(setMonth[7], LangGetStringDefault(lng_Jul, "Jul"));
    strcpy(setMonth[8], LangGetStringDefault(lng_Aug, "Aug"));
    strcpy(setMonth[9], LangGetStringDefault(lng_Sep, "Sep"));
    strcpy(setMonth[10], LangGetStringDefault(lng_Oct, "Oct"));
    strcpy(setMonth[11], LangGetStringDefault(lng_Nov, "Nov"));
    strcpy(setMonth[12], LangGetStringDefault(lng_Dec, "Dec"));
}

void saveINISettings()
{
    char        ruleString[64];

    HDD_TAP_PushDir();
    HDD_ChangeDir("/ProgramFiles/Settings");
    INIOpenFile (MANUALDSTINI, PROGRAM_NAME);

    switch(currentMode)
    {
        case 1:
            strcpy(ruleString, "Europe");
            break;
        case 2:
            strcpy(ruleString, "Manual");
            break;
        default:
            strcpy(ruleString, "Firmware");
            break;
    }

    INISetString("DefaultRule", ruleString);
    //TAP_Print("'%s'\r\n", ruleString);

    TAP_SPrint(ruleString, "%d,%d,%d,%02d:%02d", currentStartOrd, currentStartDay, currentStartMonth, currentStartHour, currentStartMin);
    INISetString("DSTStartRule", ruleString);
    //TAP_Print("'%s'\r\n", ruleString);

    TAP_SPrint(ruleString, "%d,%d,%d,%02d:%02d", currentEndOrd, currentEndDay, currentEndMonth, currentEndHour, currentEndMin);
    INISetString("DSTEndRule", ruleString);
    //TAP_Print("'%s'\r\n", ruleString);

    INISaveFile (MANUALDSTINI, INILOCATION_AtCurrentDir, NULL);

    INICloseFile();
    HDD_TAP_PopDir();

    //TAP_Print("INI Settings Saved.\r\n")

}



void loadINISettings()
{

    char        ruleString[64];

    currentStartOrd = 1;
    currentStartDay = 6;
    currentStartMonth = 10;
    currentStartHour = 2;
    currentStartMin = 0;

    currentEndOrd = 1;
    currentEndDay = 6;
    currentEndMonth = 4;
    currentEndHour = 3;
    currentEndMin = 0;

    currentMode = 0;

    HDD_TAP_PushDir();
    HDD_ChangeDir("/ProgramFiles/Settings");
    if(INIOpenFile(MANUALDSTINI, "") > INILOCATION_NewFile)
    {
        INIGetString("DSTStartRule", ruleString, "1,6,10,02:00", sizeof(ruleString) - 1);
        sscanf(ruleString, "%hhu,%hhu,%hhu,%02hhu:%02hhu", &currentStartOrd, &currentStartDay, &currentStartMonth, &currentStartHour, &currentStartMin);

        INIGetString("DSTEndRule", ruleString, "1,6,4,03:00", sizeof(ruleString) - 1);
        sscanf(ruleString, "%hhu,%hhu,%hhu,%02hhu:%02hhu", &currentEndOrd, &currentEndDay, &currentEndMonth, &currentEndHour, &currentEndMin);

        INIGetString("DefaultRule", ruleString, "Firmware", sizeof(ruleString) - 1);

        LowerCase(ruleString);

        if(strcmp(ruleString, "europe") == 0)
        {
            currentMode = 1;
        }
        if(strcmp(ruleString, "manual") == 0)
        {
            currentMode = 2;
        }
    }

    INICloseFile();
    HDD_TAP_PopDir();

    //A small attempt at some crash prevention from manually malformed INI files
    if(currentStartOrd > 5) currentStartOrd = 5;
    if(currentStartDay > 6) currentStartDay = 6;
    if(currentStartMonth > 12) currentStartMonth = 12;
    if(currentStartHour > 23) currentStartHour = 23;
    if(currentStartMin > 59) currentStartMin = 59;

    if(currentEndOrd > 5) currentEndOrd = 5;
    if(currentEndDay > 6) currentEndDay = 6;
    if(currentEndMonth > 12) currentEndMonth = 12;
    if(currentEndHour > 23) currentEndHour = 23;
    if(currentEndMin > 59) currentEndMin = 59;

    if(currentMode > 2) currentMode = 2;

}//END loadINISettings


void getFirmwareDST()
{

    tFlashTimeInfo          TimeInfo;

    strcpy(fwDSTZone, LangGetStringDefault(lng_Unknown, "Unknown"));

    if(FlashTimeGetInfo(&TimeInfo))
        {
            short tempInfo = TimeInfo.UTCOffset;
            //tempInfo = -150;   //Test for negative offset

            if(tempInfo < 0)
            {
                TAP_SPrint(fwDSTZone, "UTC - %02d:%02d", abs(tempInfo)/60, abs(tempInfo)%60);
            }
            else
            {
                TAP_SPrint(fwDSTZone, "UTC + %02d:%02d", abs(tempInfo)/60, abs(tempInfo)%60);
            }

            if(TimeInfo.DST == 3)
            {
                strcat(fwDSTZone, ", DST=");
                strcat(fwDSTZone, LangGetStringDefault(lng_ON, "ON"));
            }
            else
            {
                strcat(fwDSTZone, ", DST=");
                strcat(fwDSTZone, LangGetStringDefault(lng_OFF, "OFF"));
            }
        }
}

void updateTransitionStrings()
{
    dword   transition = 0;

    word    year;
    byte    month, day, hour, min, weekDay;

    transition =  DST_CalcTransition(currentStartOrd, currentStartDay, currentStartMonth, currentStartHour, currentStartMin);

	hour = (transition & 0xff00) >>8;
	min = (transition &0xff);
	TAP_ExtractMjd(transition>>16, &year, &month, &day, &weekDay);

	TAP_SPrint(dstStartString, "%d %s %d %02d:%02d", day, setMonth[month], year, hour, min);
	TAP_SPrint(dstStartHourString, "%02d", hour);
    TAP_SPrint(dstStartMinString, "%02d", min);

    transition =  DST_CalcTransition(currentEndOrd, currentEndDay, currentEndMonth, currentEndHour, currentEndMin);

	hour = (transition & 0xff00) >>8;
	min = (transition &0xff);
	TAP_ExtractMjd(transition>>16, &year, &month, &day, &weekDay);

	TAP_SPrint(dstEndString, "%d %s %d %02d:%02d", day, setMonth[month], year, hour, min);
	TAP_SPrint(dstEndHourString, "%02d", hour);
    TAP_SPrint(dstEndMinString, "%02d", min);

}



dword TAP_EventHandler(word event, dword param1, dword param2)
{
  (void) param2;

  OSDMenuEvent(&event, &param1, &param2);

  switch(State)
  {
    case ST_Init:
    {
      OSDMenuInitialize(FALSE, TRUE, TRUE, TRUE, PROGRAM_NAME, LangGetStringDefault(lng_Header, "Configure DST.INI"));

      OSDMenuItemAdd(LangGetStringDefault(lng_DSTRule, "DST Rule"), setMode[currentMode], NULL, NULL, TRUE, TRUE, currentMode);
      OSDMenuItemAdd(LangGetStringDefault(lng_FirmwareTimeZone, "Current Time Zone"), fwDSTZone, NULL, NULL, FALSE, FALSE, 0);

      OSDMenuItemAdd(LangGetStringDefault(lng_NextDSTStart, "Next DST Start"), dstStartString, NULL, NULL, FALSE, FALSE, 0);
      OSDMenuItemAdd(LangGetStringDefault(lng_Ordinal, "Ordinal"), setOrdinal[currentStartOrd], NULL, NULL, TRUE, TRUE, currentStartOrd);
      OSDMenuItemAdd(LangGetStringDefault(lng_Weekday, "Weekday"), setDay[currentStartDay], NULL, NULL, TRUE, TRUE, currentStartDay);
      OSDMenuItemAdd(LangGetStringDefault(lng_Month, "Month"), setMonth[currentStartMonth], NULL, NULL, TRUE, TRUE, currentStartMonth);
      OSDMenuItemAdd(LangGetStringDefault(lng_Hour, "Hour"), dstStartHourString, NULL, NULL, TRUE, TRUE, currentStartHour);
      OSDMenuItemAdd(LangGetStringDefault(lng_Minute, "Minute"), dstStartMinString, NULL, NULL, TRUE, TRUE, currentStartMin);

      OSDMenuItemAdd(LangGetStringDefault(lng_NextDSTEnd, "Next DST End"), dstEndString, NULL, NULL, FALSE, FALSE, 0);
      OSDMenuItemAdd(LangGetStringDefault(lng_Ordinal, "Ordinal"), setOrdinal[currentEndOrd], NULL, NULL, TRUE, TRUE, currentEndOrd);
      OSDMenuItemAdd(LangGetStringDefault(lng_Weekday, "Weekday"), setDay[currentEndDay], NULL, NULL, TRUE, TRUE, currentEndDay);
      OSDMenuItemAdd(LangGetStringDefault(lng_Month, "Month"), setMonth[currentEndMonth], NULL, NULL, TRUE, TRUE, currentEndMonth);
      OSDMenuItemAdd(LangGetStringDefault(lng_Hour, "Hour"), dstEndHourString, NULL, NULL, TRUE, TRUE, currentEndHour);
      OSDMenuItemAdd(LangGetStringDefault(lng_Minute, "Minute"), dstEndMinString, NULL, NULL, TRUE, TRUE, currentEndMin);

      OSDMenuButtonAdd(2, BI_Exit,    NULL, LangGetStringDefault(lng_BtnExit, "Exit"));
      OSDMenuButtonAdd(2, BI_Green,  NULL, " /");
      OSDMenuButtonAdd(2, BI_Record,  NULL, LangGetStringDefault(lng_BtnSave, "Save"));
      OSDMenuButtonAdd(2, BI_Recall,  NULL, LangGetStringDefault(lng_BtnReload, "Reload"));

      OSDMenuUpdate(FALSE);

      State = ST_Idle;

      break;
    }

    case ST_Idle:
    {
      if(event == EVT_KEY)
      {
        if(param1 == RKEY_Exit)
        {
          OSDMenuMessageBoxInitialize(PROGRAM_NAME, LangGetStringDefault(lng_Exit, "Exit DSTConfig?"));
          OSDMenuMessageBoxButtonAdd(LangGetStringDefault(lng_Yes, "Yes"));
          OSDMenuMessageBoxButtonAdd(LangGetStringDefault(lng_No, "No"));

          OSDMenuMessageBoxButtonSelect(0);
          OSDMenuMessageBoxShow();
          State = ST_YesNoDialogue;
        }

        if(param1 == RKEY_Record || param1 == RKEY_F2)
        {
            OSDMenuMessageBoxInitialize(PROGRAM_NAME, LangGetStringDefault(lng_Save, "Save DST Configuration?"));
            OSDMenuMessageBoxButtonAdd(LangGetStringDefault(lng_Yes, "Yes"));
            OSDMenuMessageBoxButtonAdd(LangGetStringDefault(lng_No, "No"));

            OSDMenuMessageBoxButtonSelect(0);
            OSDMenuMessageBoxShow();

            State = ST_YesNoDialogueSave;
        }

        if(param1 == RKEY_Recall)
        {
            loadINISettings();
            updateTransitionStrings();
            OSDMenuDestroy();
            State = ST_Init;
        }



        if(param1 == RKEY_Right || param1 == RKEY_Left)
        {

            int     direction = 1;
            if(param1 == RKEY_Left) direction = -1;


            int thisItem = OSDMenuGetCurrentItem();
            int thisID = OSDMenuItemGetID(thisItem);

            //TAP_Print("This item = %d, ID = %d.\r\n", thisItem, thisID);

            thisID = thisID + direction;

            switch(thisItem)
            {
                case    0:      //DST Mode Firmware/Europe/Manual
                    //TAP_Print("Updating item = %d to ID = %d '%s'.\r\n", thisItem, thisID, setMode[thisID]);
                    if(thisID < 0) thisID = 2;
                    if(thisID > 2) thisID = 0;
                    OSDMenuItemModifyValue(thisItem, setMode[thisID]);
                    currentMode = thisID;
                    break;

                case    3:      //Start Ordinal
                    //TAP_Print("Updating item = %d to ID = %d '%s'.\r\n", thisItem, thisID, setOrdinal[thisID]);
                    if(thisID < 1) thisID = 5;
                    if(thisID > 5) thisID = 1;
                    OSDMenuItemModifyValue(thisItem, setOrdinal[thisID]);
                    currentStartOrd = thisID;
                    break;
                case    4:      //Start day
                    //TAP_Print("Updating item = %d to ID = %d '%s'.\r\n", thisItem, thisID, setDay[thisID]);
                    if(thisID < 0) thisID = 6;
                    if(thisID > 6) thisID = 0;
                    OSDMenuItemModifyValue(thisItem, setDay[thisID]);
                    currentStartDay = thisID;
                    break;
                case    5:      //Start month
                    //TAP_Print("Updating item = %d to ID = %d '%s'.\r\n", thisItem, thisID, setMonth[thisID]);
                    if(thisID < 1) thisID = 12;
                    if(thisID > 12) thisID = 1;
                    OSDMenuItemModifyValue(thisItem, setMonth[thisID]);
                    currentStartMonth = thisID;
                    break;
                case    6:      //Start hour
                    //TAP_Print("Updating item = %d to ID = %d '%s'.\r\n", thisItem, thisID, setMonth[thisID]);
                    if(thisID < 0) thisID = 23;
                    if(thisID > 23) thisID = 0;
                    TAP_SPrint(dstStartHourString, "%02d", thisID);
                    OSDMenuItemModifyValue(thisItem, dstStartHourString);
                    currentStartHour = thisID;
                    break;
                case    7:      //Start Min
                    //TAP_Print("Updating item = %d to ID = %d '%s'.\r\n", thisItem, thisID, setMonth[thisID]);
                    if(thisID < 0) thisID = 59;
                    if(thisID > 59) thisID = 0;
                    TAP_SPrint(dstStartMinString, "%02d", thisID);
                    OSDMenuItemModifyValue(thisItem, dstStartMinString);
                    currentStartMin = thisID;
                    break;


                case    9:      //End Ordinal
                    //TAP_Print("Updating item = %d to ID = %d '%s'.\r\n", thisItem, thisID, setOrdinal[thisID]);
                    if(thisID < 1) thisID = 5;
                    if(thisID > 5) thisID = 1;
                    OSDMenuItemModifyValue(thisItem, setOrdinal[thisID]);
                    currentEndOrd = thisID;
                    break;
                case    10:      //End day
                    //TAP_Print("Updating item = %d to ID = %d '%s'.\r\n", thisItem, thisID, setDay[thisID]);
                    if(thisID < 0) thisID = 6;
                    if(thisID > 6) thisID = 0;
                    OSDMenuItemModifyValue(thisItem, setDay[thisID]);
                    currentEndDay = thisID;
                    break;
                case    11:      //End month
                    //TAP_Print("Updating item = %d to ID = %d '%s'.\r\n", thisItem, thisID, setMonth[thisID]);
                    if(thisID < 1) thisID = 12;
                    if(thisID > 12) thisID = 1;
                    OSDMenuItemModifyValue(thisItem, setMonth[thisID]);
                    currentEndMonth = thisID;
                    break;
                case    12:      //end hour
                    //TAP_Print("Updating item = %d to ID = %d '%s'.\r\n", thisItem, thisID, setMonth[thisID]);
                    if(thisID < 0) thisID = 23;
                    if(thisID > 23) thisID = 0;
                    TAP_SPrint(dstEndHourString, "%02d", thisID);
                    OSDMenuItemModifyValue(thisItem, dstEndHourString);
                    currentEndHour = thisID;
                    break;
                case    13:      //end Min
                    //TAP_Print("Updating item = %d to ID = %d '%s'.\r\n", thisItem, thisID, setMonth[thisID]);
                    if(thisID < 0) thisID = 59;
                    if(thisID > 59) thisID = 0;
                    TAP_SPrint(dstEndMinString, "%02d", thisID);
                    OSDMenuItemModifyValue(thisItem, dstEndMinString);
                    currentEndMin = thisID;
                    break;
            }

            updateTransitionStrings();
            OSDMenuItemModifyValue(2, dstStartString);
            OSDMenuItemModifyValue(8, dstEndString);

            OSDMenuItemModifyID(thisItem, thisID);
            OSDMenuUpdate(FALSE);


        }//END got left/right keys



        param1 = 0;
      }//END got a key

      break;
    }//END ST_Idle

    case ST_YesNoDialogue:
    case ST_YesNoDialogueSave:
    {
      if(!OSDMenuMessageBoxIsVisible())
      {
        if(OSDMenuMessageBoxLastButton() == 0)
        {
          OSDMenuDestroy();

          if(State == ST_YesNoDialogueSave)
          {
              saveINISettings();
          }

          State = ST_Exit;

        }
        else
        {
          State = ST_Idle;
        }
      }
      break;
    }//END YNDialogue

    case ST_Exit:
    {
      TAP_Exit();
      break;
    }//END State Exit

  }//END Switch on State

  return param1;
}

int TAP_Main(void)
{

  getFirmwareDST();
  loadLanguageStrings();
  loadINISettings();
  updateTransitionStrings();
  KeyTranslate(TRUE, &TAP_EventHandler);

  return 1;
}
