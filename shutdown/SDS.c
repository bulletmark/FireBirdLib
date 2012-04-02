#include                <string.h>
#include                "FBLib_shutdown.h"
#include                "../libFireBird.h"

#define ROOTDIR         "/ProgramFiles/Settings/SDS"
#define LOGFILE         "SDS.log"

typedef enum
{
  HHS_Init,
  HHS_Idle,
  HHS_EF00Received,
  HHS_PowerOffCancel,
  HHS_ShutdownTimerDiags,
  HHS_Shutdown,
  HHS_Exit
} tHookHandlerState;

typedef struct
{
  byte                  Type;
  byte                  unused[3];
  dword                 EventID;
  dword                 Queue;
} tEventQueue;

typedef struct
{
  byte                  Priority;
  byte                  State;
  byte                  unused[2];
  dword                 Handler;
} tEventQueueDetails;

void  (*__DevFront_PowerOffReply)(void) = NULL;
void  (*__DevFront_PowerOffCancel)(void) = NULL;

bool                    ShutdownHooked = FALSE;
int                     LastStatus = 0;
char                    Log[512];
tHookHandlerState       HookHandlerState = HHS_Init;

void (*OrigHandler)(word, dword);

void CreateRootDir(void)
{
  //Check & Create Folders
  HDD_TAP_PushDir();
  HDD_ChangeDir("/ProgramFiles");
  if(!TAP_Hdd_Exist("Settings")) TAP_Hdd_Create("Settings", ATTR_FOLDER);
  HDD_ChangeDir("Settings");
  if(!TAP_Hdd_Exist("SDS")) TAP_Hdd_Create("SDS", ATTR_FOLDER);
  HDD_TAP_PopDir();
}

void WriteLog(char *s)
{
  HDD_TAP_PushDir();
  TAP_Hdd_ChangeDir(ROOTDIR);
  LogEntry(LOGFILE, "SDS", TRUE, TIMESTAMP_YMDHMS, s);
  HDD_TAP_PopDir();
}

void Hooked_ApplEvent_CallHandler(unsigned int a1, unsigned int a2)
{
  (void)a1;
  (void)a2;

  ShutdownHooked = TRUE;
}

bool SetHandler(dword EventID, void *Handler, void **OrigHandler)
{
  static dword         *__topEvent = NULL;
  tEventQueue          *EventQueue;
  tEventQueueDetails   *EventQueueDetails;
  int                   i;

  if(!Handler && !(dword*)Handler) return FALSE;

  if(!__topEvent)
  {
    __topEvent = (dword*)FIS_vTopEvent();
    if(!__topEvent)
    {
      if(LastStatus != -10) WriteLog("Failed to resolve _topEvent");
      LastStatus = -10;
      return FALSE;
    }
  }

  EventQueue = (tEventQueue*)*__topEvent;
  for(i = 0; i < 512; i++)
  {
    if(EventQueue->Queue)
    {
      if(EventQueue->EventID == EventID)
      {
        EventQueueDetails = (tEventQueueDetails*)EventQueue->Queue;

        if(((dword)Handler > 0x01400000) && (EventQueueDetails->Handler > 0x01400000))
        {
          if(LastStatus != -11)
          {
            TAP_SPrint(Log, "Found 0x%x handler @ index %d. Already redirected to 0x%8.8x", EventID, i, EventQueueDetails->Handler);
            WriteLog(Log);
            LastStatus = -11;
          }
          return FALSE;
        }

        if(LastStatus != -12)
        {
          TAP_SPrint(Log, "Found 0x%x handler @ index %d. Redirecting from 0x%8.8x to 0x%8.8x", EventID, i, EventQueueDetails->Handler, (dword)Handler);
          WriteLog(Log);
          LastStatus = -12;
        }
        if(OrigHandler) *OrigHandler = (void*)EventQueueDetails->Handler;
        EventQueueDetails->Handler = (dword)Handler;
        return TRUE;
      }
    }
    EventQueue++;
  }

  if(LastStatus != -13)
  {
    TAP_SPrint(Log, "EventID %4.4x not yet declared", EventID);
    WriteLog(Log);
    LastStatus = -13;
  }

  return FALSE;
}

bool SDS(void)
{
  static dword              Timeout = 0;
  static tHookHandlerState  LastHHS = HHS_Exit;
  static dword              EF00FilterTimeout = 0;

  if(LastHHS != HookHandlerState)
  {
    switch(HookHandlerState)
    {
      case HHS_Init:                WriteLog("HHS_Init"); break;
      case HHS_Idle:                WriteLog("HHS_Idle"); break;
      case HHS_EF00Received:        WriteLog("HHS_EF00Received"); break;
      case HHS_PowerOffCancel:      WriteLog("HHS_PowerOffCancel"); break;
      case HHS_ShutdownTimerDiags:  WriteLog("HHS_ShutdownTimerDiags"); break;
      case HHS_Shutdown:            WriteLog("HHS_Shutdown"); break;
      case HHS_Exit:                WriteLog("HHS_Exit"); break;
    }
    LastHHS = HookHandlerState;
  }

  switch(HookHandlerState)
  {
    case HHS_Init:
    {
      dword            *curTapTask;
      int               Slot;
      char             *TAPFileName;
      tTAPInfo          TAPInfo;

      CreateRootDir();

      //Init some firmware routines
      if(!__DevFront_PowerOffReply)
      {
        __DevFront_PowerOffReply = (void*)FIS_fwDevFront_PowerOffReply();
        if(!__DevFront_PowerOffReply)
        {
          if(LastStatus != -1) WriteLog("Failed to resolve DevFront_PowerOffReply()");
          LastStatus = -1;
          HookHandlerState = HHS_Exit;
          return FALSE;
        }
      }

      if(!__DevFront_PowerOffCancel)
      {
        __DevFront_PowerOffCancel = (void*)FIS_fwDevFront_PowerOffCancel();
        if(!__DevFront_PowerOffCancel)
        {
          if(LastStatus != -2) WriteLog("Failed to resolve DevFront_PowerOffCancel()");
          LastStatus = -2;
          HookHandlerState = HHS_Exit;
          return FALSE;
        }
      }

      //Modify the handler pointer of the ef00 event queue
      if(!SetHandler(0xef00, Hooked_ApplEvent_CallHandler, (void*)&OrigHandler)) return FALSE;

      curTapTask = (dword*)FIS_vCurTapTask();
      Slot = *curTapTask;
      if(HDD_TAP_GetFileNameByIndex(Slot, &TAPFileName))
      {
        if(!HDD_TAP_GetInfoByAbsPath(TAPFileName, &TAPInfo)) strcpy(TAPInfo.TAPName, "???");
      }
      else
        strcpy(TAPInfo.TAPName, "???");
      TAP_SPrint(Log, "SDS has been activated by '%s'", TAPInfo.TAPName);
      WriteLog(Log);

      HookHandlerState = HHS_Idle;
      break;
    }

    case HHS_Idle:
    {
      if(EF00FilterTimeout && TAP_GetTick() > EF00FilterTimeout) EF00FilterTimeout = 0;

      if(ShutdownHooked)
      {
        HookHandlerState = HHS_EF00Received;
        ShutdownHooked = FALSE;
      }
      break;
    }

    case HHS_EF00Received:
    {
      __DevFront_PowerOffReply();

      if(EF00FilterTimeout)
      {
        Timeout = TAP_GetTick() + 50;
        HookHandlerState = HHS_PowerOffCancel;
      }
      else
      {
        dword ret = HDD_TAP_SendEvent(0, TRUE, EVT_STOP, 2, 0);
        if(ret == 0)
        {
          if(LastStatus != -4) WriteLog("A TAP has intercepted the shutdown notfication");
          LastStatus = -4;
          Timeout = TAP_GetTick() + 50;
          HookHandlerState = HHS_PowerOffCancel;
        }
        else
        {
          HookHandlerState = HHS_ShutdownTimerDiags;
        }
      }

      break;
    }

    case HHS_PowerOffCancel:
    {
      if(TAP_GetTick() > Timeout)
      {
        if(LastStatus != -5) WriteLog("The shutdown has been canceled");
        LastStatus = -5;
        __DevFront_PowerOffCancel();
        EF00FilterTimeout = TAP_GetTick() + 200;
        HookHandlerState = HHS_Idle;
      }
      break;
    }

    case HHS_ShutdownTimerDiags:
    {
      if(LastStatus != -6) WriteLog("Notifiying TimerDiags about the shutdown");
      LastStatus = -6;
      HDD_TAP_SendEvent(0x8E0A4224, FALSE, EVT_STOP, 0, 0);
      Timeout = TAP_GetTick() + 200;
      HookHandlerState = HHS_Shutdown;
      break;
    }

    case HHS_Shutdown:
    {
      if(TAP_GetTick() > Timeout)
      {
        if(OrigHandler)
        {
          SetHandler(0xef00, OrigHandler, NULL);
          OrigHandler = NULL;
        }
        if(LastStatus != -7) WriteLog("Notifiying all TAPs about the shutdown");
        LastStatus = -7;
        HDD_TAP_SendEvent(0, FALSE, EVT_STOP, 0, 0);
        //TAP_Exit();
        if(LastStatus != -8) WriteLog("Enqueuing the shutdown event");
        LastStatus = -8;
        Shutdown(TaskPower);
        HookHandlerState = HHS_Exit;
      }
      break;
    }

    case HHS_Exit:
    {
      if(OrigHandler)
      {
        SetHandler(0xef00, OrigHandler, NULL);
        OrigHandler = NULL;
        if(LastStatus != -9) WriteLog("SDS has been deactivated");
        LastStatus = -9;
      }
      return FALSE;
    }
  }

  return TRUE;
}

void SDSTerminate(void)
{
  if(LastStatus != -3) WriteLog("SDS termination request received");
  LastStatus = -3;

  if(OrigHandler)
  {
    SetHandler(0xef00, OrigHandler, NULL);
    OrigHandler = NULL;
    if(LastStatus != -9) WriteLog("SDS has been deactivated");
    LastStatus = -9;
  }
  HookHandlerState = HHS_Exit;
}
