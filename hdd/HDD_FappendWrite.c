#include <stdio.h>
#include <string.h>
#include "libFireBird.h"

bool HDD_FappendWrite(TYPE_File *file, const char *data)
{
  TRACEENTER();

  char      buffer[256 + 512];
  dword     len, pos, extra, blks;
  bool      ret;

  len = strlen(data);

  if(file == NULL || len > 256)
  {
    TRACEEXIT();
    return FALSE;
  }

  strcpy(buffer, data);
  memset(buffer + len, 0, sizeof(buffer) - len);

  pos = TAP_Hdd_Ftell(file);
  extra = 512 - ((pos + len) % 512);

  if(extra == 512) extra = 0;

  if((blks = TAP_Hdd_Fwrite(buffer, len + extra, 1, file)) != 1)
  {
    TRACEEXIT();
    return FALSE;
  }

  pos += len;
  ret = (TAP_Hdd_Fseek(file, pos, SEEK_SET) == pos);

  TRACEEXIT();
  return ret;
}
