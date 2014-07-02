#include                <unistd.h>
#include                <string.h>
#include                "../libFireBird.h"

int HDD_FindSymbolicLink(char *pathName, char *returnedPath, char *fullPathName)
{
  TRACEENTER();

  int         pathLen = strlen(pathName);
  int         i = 0;
  int         ret = 0;

  char        tempPath[513];
  char        linkpath[513];

  if(!pathName || !*pathName || (!returnedPath && !fullPathName))
  {
    TRACEEXIT();
    return 0;
  }

  memset(tempPath, 0, sizeof(tempPath));
  memset(linkpath, 0, sizeof(linkpath));

  for(i = 0; i < pathLen; i++)
  {
    tempPath[i] = pathName[i];

    if(pathName[i] == '/' || i == (pathLen - 1))
    {

      if(pathName[i] == '/') {tempPath[i] = 0;}  //Remove the trailing "/" if this is not the end of the path

      ret = readlink(tempPath, linkpath, sizeof(linkpath));
      if(ret != -1)
      {
        if(returnedPath) strcpy(returnedPath, linkpath);

        if(fullPathName)
        {
          strcpy(fullPathName, linkpath);
          if(pathName[i] == '/') strcat(fullPathName, &pathName[i]);
        }

        TRACEEXIT();
        return ret;
      }
    }

    tempPath[i] = pathName[i];
  }

  TRACEEXIT();
  return 0;

}
