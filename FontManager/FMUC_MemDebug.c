#include <stdlib.h>
#include "FBLib_FontManager.h"

tFMUC_MemDebug          FMUC_Memory[10000];

void FMUC_MemoryDump(dword *NrReservations, dword *NrTotalSize)
{
  int                   i;
  dword                 Nr, Total;
  tFMUC_MemDebug       *Mem;

  Nr = 0;
  Total = 0;
  Mem = &FMUC_Memory[0];

  for(i = 0; i < 10000; i++)
  {
    if(Mem->Alloc != NULL)
    {
       Nr++;
       Total = Total + Mem->Size;
    }
    Mem++;
  }

  if(NrReservations) *NrReservations = Nr;
  if(NrTotalSize) *NrTotalSize = Total;
}

tFMUC_MemDebug *FMUC_MemoryFindFree(void)
{
  int                   i;
  tFMUC_MemDebug       *Mem;

  Mem = &FMUC_Memory[0];
  for(i = 0; i < 10000; i++)
  {
    if(Mem->Alloc == NULL) return Mem;
    Mem++;
  }

  return NULL;
}

tFMUC_MemDebug *FMUC_MemoryFindPointer(void *Pointer)
{
  int                   i;
  tFMUC_MemDebug       *Mem;

  Mem = &FMUC_Memory[0];
  for(i = 0; i < 10000; i++)
  {
    if(Mem->Alloc == Pointer) return Mem;
    Mem++;
  }

  return NULL;
}

void *FMUC_ReserveMemory(char *Requester, dword size)
{
  tFMUC_MemDebug       *Mem;
  void                 *ret;
  dword                 NrReservations, NrTotalSize;

  ret = TAP_MemAlloc(size);
  return ret;

  Mem = FMUC_MemoryFindFree();
  if(Mem == NULL)
  {
    LogEntryFBLibPrintf(TRUE, "FMUC_ReserveMemory: no space in lookup table");
    return ret;
  }

  Mem->Requester = Requester;
  Mem->Size = size;
  Mem->Alloc = ret;


  FMUC_MemoryDump(&NrReservations, &NrTotalSize);
  LogEntryFBLibPrintf(TRUE, "FMUC: %s has requested %lu bytes. Currently %lu, %lu bytes", Requester, size, NrReservations, NrTotalSize);

  return ret;
}

void FMUC_FreeMemory(char *Requester, void *Pointer)
{
  tFMUC_MemDebug       *Mem;
  dword                 NrReservations, NrTotalSize;

  TAP_MemFree(Pointer);
  return;

  Mem = FMUC_MemoryFindPointer(Pointer);
  if(Mem == NULL)
  {
    LogEntryFBLibPrintf(TRUE, "FMUC_FreeMemory: entry not found in lookup table");
    return;
  }

  Mem->Alloc = NULL;
  FMUC_MemoryDump(&NrReservations, &NrTotalSize);

  LogEntryFBLibPrintf(TRUE, "FMUC: '%s' has released %lu bytes from '%s'. Currently %lu, %lu bytes", Requester, Mem->Size, Mem->Requester, NrReservations, NrTotalSize);

  Mem->Size = 0;
  Mem->Requester = NULL;
}
