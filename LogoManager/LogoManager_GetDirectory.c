#include                <string.h>
#include                <stdlib.h>
#include                "../libFireBird.h"
#include                "FBLib_LogoManager.h"

char *LogoManager_GetDirectory(tLogoStyle LogoStyle, tLogoAspect LogoAR)
{
  static char           Path[512];

  strcpy(Path, LOGOROOT);
  switch(LogoStyle)
  {
    case LGST_3pgstyle:     strcat(Path, "/3pg/"); break;
    case LGST_QtstyleBlue:  strcat(Path, "/qtblue/"); break;
    case LGST_QtstyleGrey:  strcat(Path, "/qtgrey/"); break;
    case LGST_QtstyleTMS:   strcat(Path, "/qttms/"); break;
    case LGST_TransBlack:   strcat(Path, "/trans-black/"); break;
    case LGST_TransIBBlue:  strcat(Path, "/trans-ibblue/"); break;
    case LGST_TransIBGrey:  strcat(Path, "/trans-ibgrey/"); break;
    case LGST_TransQTBlue:  strcat(Path, "/trans-qtblue/"); break;
    case LGST_TransQTGrey:  strcat(Path, "/trans-qtgrey/"); break;
    default:
      break;
  }

  switch(LogoAR)
  {
    case LGAR_43:  strcat(Path, "43"); break;
    case LGAR_169: strcat(Path, "169"); break;
    default:
      break;
  }

  return Path;
}
