#include "../libFireBird.h"

char *iso639_2(int OSDLan)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("iso639_2");
  #endif

  char *lang;

  switch(OSDLan)
  {
    case LAN_English:
      lang = "eng";
      break;

    case LAN_French:
      lang = "fre";
      break;

    case LAN_German:
      lang = "ger";
      break;

    case LAN_Italy:
      lang = "ita";
      break;

    case LAN_Spain:
      lang = "spa";
      break;

    case LAN_Arab:
      lang = "ara";
      break;

    case LAN_Greek:
      lang = "gre";
      break;

    case LAN_Turk:
      lang = "tur";
      break;

    case LAN_Danish:
      lang = "dan";
      break;

    case LAN_Swedish:
      lang = "swe";
      break;

    case LAN_Norwegian:
      lang = "nor";
      break;

    case LAN_Dutch:
      lang = "dut";
      break;

    case LAN_Russian:
      lang = "rus";
      break;

    case LAN_Polish:
      lang = "pol";
      break;

    case LAN_Persian:
      lang = "per";
      break;

    case LAN_Suomi:
      lang = "fin";
      break;

    case LAN_Slovak:
      lang = "slo";
      break;

    case LAN_Thai:
      lang = "tha";
      break;

    case LAN_Czech:
      lang = "cze";
      break;

    case LAN_Bulgarian:
      lang = "bul";
      break;

    default:
      lang = NULL;
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return lang;
}
