#include "FBLib_ini.h"
#include "../libFireBird.h"

void INISetInt (char *Key, long int Value)
{
  char                  s [12];

  sprintf(s, "%d", Value);
  INISetString (Key, s);
}
