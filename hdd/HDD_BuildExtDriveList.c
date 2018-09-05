#include <sys/statvfs.h>
#include "libFireBird.h"

bool HDD_BuildExtDriveList(textPartitionInfo *ExtPartitionList, dword *NrListItems)
{
  static dword              *__nExtPartition = NULL;
  static textPartitionInfo  *__extPartitionInfo = NULL;
  dword                      i;

  if(NrListItems) *NrListItems = 0;

  //Resolve all firmware functions and variables
  if(!__nExtPartition)
  {
    __nExtPartition = (dword*)FIS_vnExtPartition();
    if(!__nExtPartition) return FALSE;
  }

  if(!__extPartitionInfo)
  {
    __extPartitionInfo = (textPartitionInfo*)FIS_vExtPartitionInfo();
    if(!__extPartitionInfo) return FALSE;
  }

  //Check if an external disk has been mounted
  if(*__nExtPartition == 0) return FALSE;

  i = *__nExtPartition;
  if(i > 10) i = 10;

  if(ExtPartitionList) memcpy(ExtPartitionList, __extPartitionInfo, i * sizeof(textPartitionInfo));

  if(NrListItems) *NrListItems = i;

  return TRUE;
}
