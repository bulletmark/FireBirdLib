#include                <stdlib.h>
#include                "FBLib_EPG.h"

dword EPGInfo_CalculateStructSize(void)
{
  TRACEENTER();

  tTreeEntry           *Entry, *ListStart;
  dword                 MinStructSize, d;

  if(EPGInfoStructSize == 0)
  {
    ListStart = (tTreeEntry*)*(dword*)Appl_GetEvtListHeadInUsePool();

    //If the list points to itself, no data is available
    if(ListStart != (tTreeEntry*)ListStart->Next)
    {

      //Loop until we're back at the beginning of the pool
      MinStructSize = 0xffffffff;
      Entry = ListStart;
      do
      {
        d = abs((dword)Entry - *Entry->Next);
        if((d != 0) && (d < MinStructSize)) MinStructSize = d;

        Entry = (tTreeEntry*)Entry->Next;
      } while(Entry && (Entry->Next != ListStart->Prev));

      if((MinStructSize != 0xffffffff) & (MinStructSize != 0))
      {
        EPGInfoStructSize = MinStructSize;
      }
    }
  }

  TRACEEXIT();
  return EPGInfoStructSize;
}
