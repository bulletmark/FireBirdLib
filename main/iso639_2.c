#include "../libFireBird.h"

char *iso639_2 (int OSDLan)
{
  switch (OSDLan)
  {
    case LAN_English:
      return "eng";

    case LAN_French:
      return "fre";

    case LAN_German:
      return "ger";

    case LAN_Italy:
      return "ita";

    case LAN_Spain:
      return "spa";

    case LAN_Arab:
      return "ara";

    case LAN_Greek:
      return "gre";

    case LAN_Turk:
      return "tur";

    case LAN_Danish:
      return "dan";

    case LAN_Swedish:
      return "swe";

    case LAN_Norwegian:
      return "nor";

    case LAN_Dutch:
      return "dut";

    case LAN_Russian:
      return "rus";

    case LAN_Polish:
      return "pol";

    case LAN_Persian:
      return "per";

    case LAN_Suomi:
      return "fin";

    case LAN_Slovak:
      return "slo";

    case LAN_Thai:
      return "tha";

    case LAN_Czech:
      return "cze";

    case LAN_Bulgarian:
      return "bul";

    default:
      return NULL;
  }
}
