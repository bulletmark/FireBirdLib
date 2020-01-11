#include <string.h>
#include "libFireBird.h"

#define MAX_DIRDEPTH 16

static char dirstack[MAX_DIRDEPTH][MAX_FILE_NAME_SIZE + 1];
static int dirdepth = -1;

static bool push_dir (const char *dir)
{
  if (dirdepth + 1 < MAX_DIRDEPTH && strlen(dir) <= MAX_FILE_NAME_SIZE)
  {
    strcpy(dirstack[++dirdepth], dir);
    return TRUE;
  }
  else return FALSE;
}

static bool pop_dir (char *dir)
{
  if (dirdepth >= 0)
  {
    strcpy(dir, dirstack[dirdepth--]);
    return TRUE;
  }
  else return FALSE;
}

static bool GetFileDir (const char *FileName, const char *Dir, const char *ext)
{
  dword files;
  TYPE_FolderEntry entry;

  TAP_Hdd_ChangeDir(Dir);

  files = TAP_Hdd_FindFirst(&entry, ext);

  while (files--)
  {
    if (entry.attr == ATTR_FOLDER) push_dir(entry.name);
    else if (strcmp(entry.name, FileName) == 0) return TRUE;

    TAP_Hdd_FindNext(&entry);
  }

  return FALSE;
}

bool HDD_GetFileDir (const char *FileName, eRootDirs Root, char *Dir)
{
  const char *ext = NULL;
  char dirname[MAX_FILE_NAME_SIZE + 1];
  bool result;

  TRACEENTER();

  if (!FileName || !Dir || ((int) Root < DIR_ROOT || Root > DIR_TMP))
  {
    TRACEEXIT();
    return FALSE;
  }

  if (strlen(FileName) > 4) ext = strrchr(FileName, '.');

  switch (Root)
  {
    case DIR_ROOT:
      strcpy(Dir, "/");
      break;

    case DIR_DATA_FILES:
      strcpy(Dir, "/DataFiles");
      break;

    case DIR_PROGRAM_FILES:
      strcpy(Dir, "/ProgramFiles");
      break;

    case DIR_MP3_FILES:
      strcpy(Dir, "/MP3Files");
      break;

    case DIR_INCOMING:
      strcpy(Dir, "/Incoming");
      break;

    case DIR_MEDIA_FILES:
      strcpy(Dir, "/MediaFiles");
      break;

    case DIR_PHOTO_FILES:
      strcpy(Dir, "/PhotoFiles");
      break;

    case DIR_SYSTEM_FILES:
      strcpy(Dir, "/SystemFiles");
      break;

    case DIR_TMP:
      strcpy(Dir, "/tmp");
      break;
  }

  HDD_TAP_PushDir();

  result = GetFileDir(FileName, Dir, ext);

  while (!result && pop_dir(dirname))
  {
    if (*dirname == '/')
    {
      strcpy(Dir, dirname);
      continue;
    }

    if (strlen(Dir) + strlen(dirname) + 1 < FBLIB_DIR_SIZE)
    {
      if (!push_dir(Dir)) break;

      if (strcmp(Dir, "/") != 0) strcat(Dir, "/");

      strcat(Dir, dirname);

      result = GetFileDir(FileName, Dir, ext);
    }
  }

  if (!result) *Dir = 0;

  HDD_TAP_PopDir();

  TRACEEXIT();

  return result;
}
