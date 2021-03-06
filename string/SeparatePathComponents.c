#include                <string.h>
#include                "libFireBird.h"

void SeparatePathComponents(const char *FullName, char *Path, char *FileName, char *FileExt)
{
  TRACEENTER();

  int                   Index;
  bool                  isDel;

  if(Path) Path[0] = '\0';
  if(FileName) FileName[0] = '\0';
  if(FileExt) FileExt[0] = '\0';

  if(!FullName || !*FullName)
  {
    TRACEEXIT();
    return;
  }

  SeparateFileNameComponents(FullName, Path, FileName, FileExt, &Index, NULL, &isDel);

  if(Index && FileName) TAP_SPrint(&FileName[strlen(FileName)], "-%d", Index);
  if(isDel && FileExt) strcat(FileExt, ".del");

  TRACEEXIT();
}
