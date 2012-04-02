#include                "stdlib.h"
#include                "tap.h"
#include                "libFireBird.h"
#include                "Setup_busybox.h"

#include                "busybox_Bin2C.c"

#define BUSYBOX         "busybox"

void InstallBusybox(void)
{
  TYPE_File            *f;

  HDD_ChangeDir("/ProgramFiles");
  if(!TAP_Hdd_Exist(BUSYBOX))
  {
    TAP_Hdd_Delete(BUSYBOX);
    TAP_Hdd_Create(BUSYBOX, ATTR_NORMAL);
    f = TAP_Hdd_Fopen(BUSYBOX);
    if(f)
    {
      TAP_Hdd_Fwrite(_busybox_Bitmap, _busybox_Size, 1, f);
      TAP_Hdd_Fclose(f);
    }
  }
  system("chmod 555 /mnt/hd/ProgramFiles/"BUSYBOX);
}
