#include <fcntl.h>
#include <unistd.h>
#include "FBLib_av.h"
#include "libFireBird.h"

bool SaveBitmap(char *FileName, int width, int height, byte* pBuffer)
{
  TRACEENTER();

  dword									rowlength;
  char                  AbsFilename[FBLIB_DIR_SIZE];
  int                   FileHandle;

  if(!pBuffer ||!FileName || !*FileName)
  {
    TRACEEXIT();
    return FALSE;
  }

  ConvertPathType(FileName, AbsFilename, PF_FullLinuxPath);

  FileHandle = open(AbsFilename, O_WRONLY | O_CREAT | O_TRUNC);
  if(FileHandle == -1)
  {
    TRACEEXIT();
    return FALSE;
  }

  // Write Header
  BMP_WriteHeader(FileHandle, width, height);

  // write bitmap data
	// according to spec.: the rowlength must be a multiple of 4 bytes, if necessary fill up with zero-bytes
	rowlength = (width*3%4==0) ? width*3 : ((width*3/4)+1)*4;
	write(FileHandle, pBuffer, rowlength * height);
	close(FileHandle);

  TRACEEXIT();
  return TRUE;
}
