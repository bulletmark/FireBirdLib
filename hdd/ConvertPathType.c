#include                <string.h>
#include                "libFireBird.h"

void ConvertPathType(char *Source, char *Dest, tPathFormat DestFormat)
{
  TRACEENTER;

  tPathFormat           SourceFormat;

  if(!Source || !Dest)
  {
    TRACEEXIT;
    return;
  }

  SourceFormat = GetPathType(Source);

  //A shortcut if source and destination formats are the same
  if(SourceFormat == DestFormat)
  {
    strcpy(Dest, Source);

    if((DestFormat == PF_TAPPathOnly) || (DestFormat == PF_LinuxPathOnly))
    {
      if(Dest[strlen(Dest) - 1] != '/') strcat(Dest, "/");
    }

    TRACEEXIT;
    return;
  }

  switch(SourceFormat)
  {
    case PF_FileNameOnly:
    {
      switch(DestFormat)
      {
        case PF_FileNameOnly: break;

        case PF_TAPPathOnly:
        {
          //Simply return the current TAP directory
          HDD_TAP_GetCurrentDir(Dest);
          if(!StringEndsWith(Dest, "/")) strcat(Dest, "/");
          break;
        }

        case PF_LinuxPathOnly:
        {
          //Return the Linux path to the TAP's current directory
          strcpy(Dest, "/mnt/hd");
          HDD_TAP_GetCurrentDir(&Dest[7]);
          if(!StringEndsWith(Dest, "/")) strcat(Dest, "/");
          break;
        }

        case PF_FullTAPPath:
        {
          //Return the current TAP directory including the file name from Source
          HDD_TAP_GetCurrentDir(Dest);
          if(!StringEndsWith(Dest, "/")) strcat(Dest, "/");
          strcat(Dest, Source);
          break;
        }

        case PF_FullLinuxPath:
        {
          //Return the Linux path to the TAP's current directory plus the file name passed in Source
          strcpy(Dest, "/mnt/hd");
          HDD_TAP_GetCurrentDir(&Dest[7]);
          if(!StringEndsWith(Dest, "/")) strcat(Dest, "/");
          strcat(Dest, Source);
          break;
        }
      }
      break;
    }

    case PF_TAPPathOnly:
    {
      switch(DestFormat)
      {
        case PF_FileNameOnly:
        {
          //If Source contains only a path, there is no file name to extract
          Dest[0] = '\0';
          break;
        }

        case PF_TAPPathOnly: break;

        case PF_LinuxPathOnly:
        {
          //Check if Source contains an absolute or relative path
          if(Source[0] == '/')
          {
            //Insert the mount point at the beginning
            TAP_SPrint(Dest, "/mnt/hd%s", Source);
          }
          else
          {
            //As the path is relative, we need to get the current path to make it absolute
            char        CurrentPath[FBLIB_DIR_SIZE];

            HDD_TAP_GetCurrentDir(CurrentPath);
            if(!StringEndsWith(CurrentPath, "/")) strcat(CurrentPath, "/");
            strcat(CurrentPath, Source);
            if(!StringEndsWith(CurrentPath, "/")) strcat(CurrentPath, "/");
            TAP_SPrint(Dest, "/mnt/hd%s", CurrentPath);
          }
          if(!StringEndsWith(Dest, "/")) strcat(Dest, "/");
          break;
        }

        case PF_FullTAPPath:
        {
          //Not possible, there is no file name in source
          Dest[0] = '\0';
          break;
        }

        case PF_FullLinuxPath:
        {
          //Not possible, there is no file name in source
          Dest[0] = '\0';
          break;
        }
      }
      break;
    }

    case PF_LinuxPathOnly:
    {
      switch(DestFormat)
      {
        case PF_FileNameOnly:
        {
          //Not possible, there is no file name in source
          Dest[0] = '\0';
          break;
        }

        case PF_TAPPathOnly:
        {
          //Cut away the mount point
          if(strncmp(Source, TAPFSROOT, strlen(TAPFSROOT)) == 0)
          {
            strcpy(Dest, &Source[7]);
            if(!StringEndsWith(Dest, "/")) strcat(Dest, "/");
          }
          else
            Dest[0] = '\0';

          break;
        }

        case PF_LinuxPathOnly: break;

        case PF_FullTAPPath:
        {
          //Not possible, there is no file name in source
          Dest[0] = '\0';
          break;
        }

        case PF_FullLinuxPath:
        {
          //Not possible, there is no file name in source
          //But it is possible that only a path is needed
          strcpy(Dest, Source);
          break;
        }
      }
      break;
    }

    case PF_FullTAPPath:
    {
      switch(DestFormat)
      {
        case PF_FileNameOnly:
        {
          char         *LastSlash;

          //Just copy the file name, which starts after the last /
          LastSlash = strrchr(Source, '/');
          strcpy(Dest, LastSlash + 1);
          break;
        }

        case PF_TAPPathOnly:
        {
          char         *LastSlash;
          dword         i;

          //Copy from the beginning up to the last slash
          LastSlash = strrchr(Source, '/');
          i = (dword)LastSlash - (dword)Source;
          strncpy(Dest, Source, i);
          Dest[i] = '\0';
          if(!StringEndsWith(Dest, "/")) strcat(Dest, "/");
          break;
        }

        case PF_LinuxPathOnly:
        {
          char         *LastSlash;
          dword         i;

          //To calculate the Linux path, we need to determine if this is a relative or absolute path
          if(Source[0] == '/')
          {
            //Just insert the mount point, then copy everything up to the last slash
            strcpy(Dest, "/mnt/hd");
            LastSlash = strrchr(Source, '/');
            i = (dword)LastSlash - (dword)Source;
            strncpy(&Dest[7], Source, i);
            Dest[i+7] = '\0';
          }
          else
          {
            //As the path is relative, we need to get the current path to make it absolute
            char        CurrentPath[FBLIB_DIR_SIZE];

            HDD_TAP_GetCurrentDir(CurrentPath);
            if(!StringEndsWith(CurrentPath, "/")) strcat(CurrentPath, "/");
            strcat(CurrentPath, Source);

            strcpy(Dest, "/mnt/hd");
            LastSlash = strrchr(CurrentPath, '/');
            i = (dword)LastSlash - (dword)CurrentPath;
            strncpy(&Dest[7], CurrentPath, i);
            Dest[i+7] = '\0';
          }
          if(!StringEndsWith(Dest, "/")) strcat(Dest, "/");

          break;
        }

        case PF_FullTAPPath: break;

        case PF_FullLinuxPath:
        {
          //To calculate the Linux path, we need to determine if this is a relative or absolute path
          if(Source[0] == '/')
          {
            //Simply insert the mount point
            TAP_SPrint(Dest, "/mnt/hd%s", Source);
          }
          else
          {
            //As the path is relative, we need to get the current path to make it absolute
            char        CurrentPath[FBLIB_DIR_SIZE];

            HDD_TAP_GetCurrentDir(CurrentPath);
            if(!StringEndsWith(CurrentPath, "/")) strcat(CurrentPath, "/");
            strcat(CurrentPath, Source);

            TAP_SPrint(Dest, "/mnt/hd%s", CurrentPath);
          }
          break;
        }
      }
      break;
    }

    case PF_FullLinuxPath:
    {
      switch(DestFormat)
      {
        case PF_FileNameOnly:
        {
          char         *LastSlash;

          //Just copy the file name, which starts after the last /
          LastSlash = strrchr(Source, '/');
          strcpy(Dest, LastSlash + 1);
          break;
        }

        case PF_TAPPathOnly:
        {
          char         *LastSlash;
          dword         i;

          //Copy from the beginning up to the last slash, but skip the mount point
          if(strncmp(Source, TAPFSROOT, strlen(TAPFSROOT)) == 0)
          {
            LastSlash = strrchr(Source, '/');
            i = (dword)LastSlash - (dword)&Source[7];
            strncpy(Dest, &Source[7], i);
            Dest[i] = '\0';
            if(!StringEndsWith(Dest, "/")) strcat(Dest, "/");
          }
          else
            Dest[0] = '\0';

          break;
        }

        case PF_LinuxPathOnly:
        {
          char         *LastSlash;
          dword         i;

          //Copy from the beginning up to the last slash
          LastSlash = strrchr(Source, '/');
          i = (dword)LastSlash - (dword)Source;
          strncpy(Dest, Source, i);
          Dest[i] = '\0';
          if(!StringEndsWith(Dest, "/")) strcat(Dest, "/");

          break;
        }

        case PF_FullTAPPath:
        {
          //Copy everything except the mount point
          if(strncmp(Source, TAPFSROOT, strlen(TAPFSROOT)) == 0)
            strcpy(Dest, &Source[7]);
          else
            Dest[0] = '\0';
          break;
        }

        case PF_FullLinuxPath: break;
      }
      break;
    }
  }

  TRACEEXIT;
}
