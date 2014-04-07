#include                <string.h>
#include                <stdlib.h>
#include                "../libFireBird.h"
#include                "FBLib_LogoManager.h"

void LogoManager_LogoCacheRebuild(void)
{
  TRACEENTER();

  char                  ID[4];
  dword                 Version;
  TYPE_File            *f, *fLogo;
  int                   i, j, k, NrFiles;
  TYPE_FolderEntry      FolderEntry;
  dword                 LogoIndex;
  byte                 *PixelData, *TempBuffer;
  dword                 BufferSize, CompressedSize;
  TYPE_GrData          *grData;
  int                   LogosConverted;

  if(LogoManager_CB) LogoManager_CB(2, -1);

  //Step 1: Kill the current cache
  HDD_TAP_PushDir();
  HDD_ChangeDir(LOGOROOT);
  TAP_Hdd_Delete(LOGOCACHE);

  //Step 2: iterate through all directories and count the number of logos
  LogoManager_NrLogos = 0;
  for(i = LGST_3pgstyle; i < LGST_NRITEMS; i++)
  {
    for(j = LGAR_43; j < LGAR_NRITEMS; j++)
    {
      if(HDD_ChangeDir(LogoManager_GetDirectory(i, j)))
      {
        NrFiles = TAP_Hdd_FindFirst(&FolderEntry, "qtl|qsl|ibl");
        for(k = 0; k < NrFiles; k++)
        {
          if(FolderEntry.attr == ATTR_NORMAL)
          {
            FixInvalidFileName(FolderEntry.name);
            LogoManager_NrLogos++;
          }
          TAP_Hdd_FindNext(&FolderEntry);
        }
      }
    }
  }
  if(LogoManager_CB) LogoManager_CB(3, LogoManager_NrLogos);


  //Step 3: build the basic cache file
  LogosConverted = 0;
  if(LogoManager_LogoData) TAP_MemFree(LogoManager_LogoData);
  LogoManager_LogoData = TAP_MemAlloc(LogoManager_NrLogos * sizeof(tLogoData));
  if(LogoManager_LogoData)
  {
    memset(LogoManager_LogoData, 0, LogoManager_NrLogos * sizeof(tLogoData));
    HDD_ChangeDir(LOGOROOT);
    if(!TAP_Hdd_Exist(LOGOCACHE)) TAP_Hdd_Create(LOGOCACHE, ATTR_NORMAL);
    f = TAP_Hdd_Fopen(LOGOCACHE);
    if(f)
    {
      strcpy(ID, LOGOCACHEID);
      Version = LOGOCACHEVERSION;

      TAP_Hdd_Fwrite(ID, 4, 1, f);
      TAP_Hdd_Fwrite(&Version, sizeof(dword), 1, f);
      TAP_Hdd_Fwrite(&LogoManager_NrLogos, sizeof(dword), 1, f);
      TAP_Hdd_Fwrite(LogoManager_LogoData, sizeof(tLogoData), LogoManager_NrLogos, f);

      //Step 4: iterate through all directories again, compress the data and save it to the cache
      LogoIndex = 0;
      for(i = LGST_3pgstyle; i < LGST_NRITEMS; i++)
      {
        for(j = LGAR_43; j < LGAR_NRITEMS; j++)
        {
          if(HDD_ChangeDir(LogoManager_GetDirectory(i, j)))
          {
            NrFiles = TAP_Hdd_FindFirst(&FolderEntry, "qtl|qsl|ibl");
            for(k = 0; k < NrFiles; k++)
            {
              if(LogoManager_CB) LogoManager_CB(2, LogosConverted * 100 / LogoManager_NrLogos);

              if(FolderEntry.attr == ATTR_NORMAL)
              {
                LogoManager_LogoData[LogoIndex].ChannelID = 0;
                strncpy(LogoManager_LogoData[LogoIndex].LogoName, FolderEntry.name, MAXLOGONAME);
                LogoManager_LogoData[LogoIndex].LogoName[MAXLOGONAME] = '\0';
                LogoManager_LogoData[LogoIndex].LogoName[strlen(LogoManager_LogoData[LogoIndex].LogoName) - 4] = '\0';
                LogoManager_LogoData[LogoIndex].Style  = i;

                if(StringEndsWith(FolderEntry.name, ".qtl")) LogoManager_LogoData[LogoIndex].Size = LGSZ_qtl;
                if(StringEndsWith(FolderEntry.name, ".qsl")) LogoManager_LogoData[LogoIndex].Size = LGSZ_qsl;
                if(StringEndsWith(FolderEntry.name, ".ibl")) LogoManager_LogoData[LogoIndex].Size = LGSZ_ibl;

                LogoManager_LogoData[LogoIndex].Aspect = j;
                LogoManager_LogoData[LogoIndex].grData = NULL;

                fLogo = TAP_Hdd_Fopen(FolderEntry.name);
                if(fLogo)
                {
                  BufferSize = TAP_Hdd_Flen(fLogo) - 8;
                  PixelData = TAP_MemAlloc(BufferSize + 8);
                  TempBuffer = TAP_MemAlloc(sizeof(TYPE_GrData) + BufferSize);
                  if(PixelData && TempBuffer)
                  {
                    TAP_Hdd_Fread(PixelData, BufferSize + 8, 1, fLogo);
                    CompressedSize = CompressTFD(&PixelData[8], BufferSize, &TempBuffer[sizeof(TYPE_GrData)], 0x0001, 0xffff, NULL);
                    TAP_Put16bit(&TempBuffer[sizeof(TYPE_GrData) + 0x0e], 0xffff);

                    grData = (TYPE_GrData*)TempBuffer;
                    grData->version        = 1;
                    grData->reserved       = 0;
                    grData->dataFormat     = OSD_1555;
                    grData->compessMethod  = COMPRESS_Tfp;
                    grData->data           = NULL;
                    grData->dataSize       = BufferSize;
                    grData->width          = TAP_Get32bit(&PixelData[0]);
                    grData->height         = TAP_Get32bit(&PixelData[4]);

                    LogoManager_LogoData[LogoIndex].CachePosition = TAP_Hdd_Ftell(f);
                    LogoManager_LogoData[LogoIndex].grDataSize    = sizeof(TYPE_GrData) + CompressedSize;
                    TAP_Hdd_Fwrite(grData, LogoManager_LogoData[LogoIndex].grDataSize, 1, f);
                    LogoIndex++;
                  }
                  if(PixelData) TAP_MemFree(PixelData);
                  if(TempBuffer) TAP_MemFree(TempBuffer);
                  TAP_Hdd_Fclose(fLogo);
                }
                else
                {
                  if(LogoManager_CB) LogoManager_CB(-1, 2);
                }
                LogosConverted++;
              }
              TAP_Hdd_FindNext(&FolderEntry);
            }
          }
        }
      }

      //Step 5: if the LIL exists, read and update the ChannelID of all Logos

      //Step 6: rewrite the cache structure to update all pointers
      TAP_Hdd_Fseek(f, sizeof(ID) + sizeof(dword) + sizeof(dword), SEEK_SET);
      TAP_Hdd_Fwrite(LogoManager_LogoData, sizeof(tLogoData), LogoManager_NrLogos, f);
      TAP_Hdd_Fclose(f);
    }
  }
  HDD_TAP_PopDir();
  if(LogoManager_CB) LogoManager_CB(4, 0);

  TRACEEXIT();
}
