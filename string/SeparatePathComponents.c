#include                <string.h>
#include                "../libFireBird.h"

void SeparatePathComponents(char *FullName, char *Path, char *FileName, char *FileExt)
{
  TRACEENTER();

  int                   Index;
  bool                  isDel;

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
