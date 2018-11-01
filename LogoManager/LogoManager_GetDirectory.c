#include                <string.h>
#include                <stdlib.h>
#include                "libFireBird.h"
#include                "FBLib_LogoManager.h"

char *LogoManager_GetDirectory(tLogoStyle LogoStyle, tLogoAspect LogoAR, char *LogoPath)
{
  TRACEENTER();

  if(LogoPath)
  {
    strcpy(LogoPath, LOGOROOT);
    switch(LogoStyle)
    {
      case LGST_3pgstyle:     strcat(LogoPath, "/3pg/"); break;
      case LGST_QtstyleBlue:  strcat(LogoPath, "/qtblue/"); break;
      case LGST_QtstyleGrey:  strcat(LogoPath, "/qtgrey/"); break;
      case LGST_QtstyleTMS:   strcat(LogoPath, "/qttms/"); break;
      case LGST_TransBlack:   strcat(LogoPath, "/trans-black/"); break;
      case LGST_TransIBBlue:  strcat(LogoPath, "/trans-ibblue/"); break;
      case LGST_TransIBGrey:  strcat(LogoPath, "/trans-ibgrey/"); break;
      case LGST_TransQTBlue:  strcat(LogoPath, "/trans-qtblue/"); break;
      case LGST_TransQTGrey:  strcat(LogoPath, "/trans-qtgrey/"); break;
      default:
        break;
    }

    switch(LogoAR)
    {
      case LGAR_43:  strcat(LogoPath, "43"); break;
      case LGAR_169: strcat(LogoPath, "169"); break;
      default:
        break;
    }
  }

  TRACEEXIT();
  return LogoPath;
}
