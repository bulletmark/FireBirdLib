#include                "FBLib_EPG.h"

dword EPGInfo_CountEvents(dword *TreePointer)
{
  TRACEENTER;

  dword                 i;
  tTreeEntry           *ListStart, *Entry;

  i = 0;

  if(TreePointer)
  {
    ListStart = (tTreeEntry*)*TreePointer;

    //If the list points to itself, no data is available
    if(ListStart == (tTreeEntry*)ListStart->Next)
    {
      TRACEEXIT;

      return 0;
    }

    //Loop until we're back at the beginning of the pool
    Entry = ListStart;
    do
    {
      i++;
      Entry = (tTreeEntry*)Entry->Next;
    } while(Entry && (Entry->Next != ListStart->Prev));
  }

  TRACEEXIT;
  return i;
}
