#include                "tap.h"
#include                "libFireBird.h"

#define PROGRAM_NAME    "SDS Demo"
#define VERSION         "V0.1"

TAP_ID                  (0x8E0A424b);
TAP_PROGRAM_NAME        (PROGRAM_NAME" "VERSION);
TAP_AUTHOR_NAME         ("FireBird");
TAP_DESCRIPTION         ("SDS Demo");
TAP_ETCINFO             (__DATE__);

dword TAP_EventHandler(word event, dword param1, dword param2)
{
  static dword          Timeout = 0;                  //Zuständig für den "Job" nach dem abgefangenem Shutdown
  static bool           InterceptShutdown = FALSE;    //Soll der Shutdown abgefangen werden?
  static bool           DoOwnJob = FALSE;             //Der Shutdown wurde abgefangen, eigenen "Job" beginnen
  static int            SDSStatus = 2;                //Nur für's Debugging verwendet

  (void) param2;

  if(event == EVT_KEY)
  {
    switch(param1)
    {
      //Die Shutdown Interception kann mit der FAV-Taste ein- und ausgeschaltet werden. Die Statusanzeige erfolgt via Telnet.
      case RKEY_Fav:
      {
        InterceptShutdown = !InterceptShutdown;
        TAP_PrintNet("Interception = %s\n", InterceptShutdown ? "on" : "off");
        param1 = 0;
        break;
      }
    }
  }

  //Wenn gewünscht, den Shutdown request vom SDS abfangen. Zusätzlich ein Flag setzen, so dass die eigentlich Aufgabe durchgeführt wird.
  if((event == EVT_STOP) && (param1 == 2) && InterceptShutdown)
  {
    TAP_PrintNet("Shutdown has been intercepted, starting own job\n");
    DoOwnJob = TRUE;
    return 0;
  }

  //Dieses TAP wird vom User beendet. Sofort den SDS beenden, da sonst der Topf abstürzt.
  //Dies gilt auch, wenn sich das TAP irgendwo mit TAP_Exit() selbst beendet.
  if((event == EVT_STOP) && (param1 == 1))
  {
    TAP_PrintNet("User is killing me, stop SDS\n");
    SDSTerminate();
  }

  if(event == EVT_IDLE)
  {
    //Einfach den SDS-Handler aufrufen.
    //Dieser liefert TRUE, falls die Kontrolle über den Shutdown-Handler erfolgreich übernommen wurde.
    //Dieser Rückgabewert ist hier jedoch nicht wichtig und kann ignoriert werden.
    //FALSE wird geliefert, falls bereits ein anderes TAP den SDS initialisiert hat. In diesem Fall kann trotzdem
    //weiter der Handler aufgerufen werden. Beendet sich nämlich das andere TAP, übernimmt dieses automatisch
    //den Event-Handler.
    //Der Rückgabewert wird hier nur für's Debugging verwendet.
    bool ret = SDS();
    if(SDSStatus != (ret ? 1 : 0))
    {
      TAP_PrintNet("SDS reported to be %s\n", ret ? "active" : "inactive");
      SDSStatus = (ret ? 1 : 0);
    }

    if(DoOwnJob)
    {
      //Der eigentliche Job lautet: Topf nach 30 Sekunden abschalten
      //TAPs, die nur den EVT_STOP ohne param1 auswerten, haben sich unter Umständen
      //zu diesem Zeitpunkt bereits beendet (EVT_STOP/2). Man darf also nicht davon ausgehen,
      //dass noch alle TAPs laufen.
      if(Timeout == 0) Timeout = TAP_GetTick() + 3000;

      if(TAP_GetTick() > Timeout)
      {
        //Abfang-Flag zurücksetzen, sonst endet man in einer Endlosschleife
        TAP_PrintNet("Own job is done, shutting Toppy down\n");
        InterceptShutdown = FALSE;
        DoOwnJob = FALSE;
        Timeout = 0;

        //Shutdown einleiten
        //Dies erzeugt wieder einen Shutdown-Request (EVT_STOP/2) vom SDS.
        //Dieses TAP darf natürlich nicht mehr darauf reagieren, deshalb auch das InterceptShutdown = FALSE oben.
        Shutdown(TaskPower);
      }
    }
  }

  return param1;
}


int TAP_Main(void)
{
  return 1;
}
