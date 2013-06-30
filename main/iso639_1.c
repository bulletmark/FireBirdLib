#include "../libFireBird.h"

char *iso639_1(int OSDLan)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("iso639_1");
  #endif

  char *lang;

  switch(OSDLan)
  {
    case LAN_English:
      lang = "en";
      break;

    case LAN_French:
      lang = "fr";
      break;

    case LAN_German:
      lang = "de";
      break;

    case LAN_Italy:
      lang = "it";
      break;

    case LAN_Spain:
      lang = "es";
      break;

    case LAN_Arab:
      lang = "ar";
      break;

    case LAN_Greek:
      lang = "el";
      break;

    case LAN_Turk:
      lang = "tr";
      break;

    case LAN_Danish:
      lang = "da";
      break;

    case LAN_Swedish:
      lang = "sv";
      break;

    case LAN_Norwegian:
      lang = "no";
      break;

    case LAN_Dutch:
      lang = "nl";
      break;

    case LAN_Russian:
      lang = "ru";
      break;

    case LAN_Polish:
      lang = "pl";
      break;

    case LAN_Persian:
      lang = "fa";
      break;

    case LAN_Suomi:
      lang = "fi";
      break;

    case LAN_Slovak:
      lang = "sk";
      break;

    case LAN_Thai:
      lang = "th";
      break;

    case LAN_Czech:
      lang = "cs";
      break;

    case LAN_Bulgarian:
      lang = "bg";
      break;

    default:
      lang = NULL;
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return lang;
}
