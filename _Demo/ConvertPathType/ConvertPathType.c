#include                <string.h>
#include                "tap.h"
#include                "libFireBird.h"

#define PROGRAM_NAME    "ConvertPathType Test"
#define VERSION         "V0.1"

TAP_ID                  (0x8E0A42FE);
TAP_PROGRAM_NAME        (PROGRAM_NAME" "VERSION);
TAP_PROGRAM_VERSION     (VERSION);
TAP_AUTHOR_NAME         ("FireBird");
TAP_DESCRIPTION         ("Test for the ConvertPathType function");
TAP_ETCINFO             (__DATE__);

void DoTesting(char *Source)
{
  tPathFormat           SourceType;
  char                  Dest[FBLIB_DIR_SIZE];

  TAP_Print("Source       : '%s'\n", Source);

  TAP_Print("Detected     : ");
  SourceType = GetPathType(Source);
  switch(SourceType)
  {
    case PF_FileNameOnly:   TAP_Print("PF_FileNameOnly\n\n"); break;
    case PF_TAPPathOnly:    TAP_Print("PF_TAPPathOnly\n\n"); break;
    case PF_LinuxPathOnly:  TAP_Print("PF_LinuxPathOnly\n\n"); break;
    case PF_FullTAPPath:    TAP_Print("PF_FullTAPPath\n\n"); break;
    case PF_FullLinuxPath:  TAP_Print("PF_FullLinuxPath\n\n"); break;
  }

  ConvertPathType(Source, Dest, PF_FileNameOnly);
  TAP_Print("FileNameOnly : '%s'\n", Dest);

  ConvertPathType(Source, Dest, PF_TAPPathOnly);
  TAP_Print("TAPPathOnly  : '%s'\n", Dest);

  ConvertPathType(Source, Dest, PF_FullTAPPath);
  TAP_Print("FullTAPPath  : '%s'\n", Dest);

  ConvertPathType(Source, Dest, PF_LinuxPathOnly);
  TAP_Print("LinuxPathOnly: '%s'\n", Dest);

  ConvertPathType(Source, Dest, PF_FullLinuxPath);
  TAP_Print("FullLinuxPath: '%s'\n", Dest);

  TAP_Print("-------------------------------------------\n");
}

void TestSequence(void)
{
  DoTesting("xyz.tap");
  DoTesting("Settings/xyz.tap");
  DoTesting("/ProgramFiles/Settings/xyz.tap");
  DoTesting("/mnt/hd/ProgramFiles/Settings/xyz.tap");
  DoTesting("Settings");
  DoTesting("settings");
  DoTesting("Settings/");
  DoTesting("/ProgramFiles/Settings");
  DoTesting("/ProgramFiles/Settings/");
  DoTesting("/mnt/hd/ProgramFiles/Settings");
  DoTesting("/mnt/hd/ProgramFiles/Settings/");
  DoTesting("..");
  DoTesting("/root");
}

dword TAP_EventHandler(word event, dword param1, dword param2)
{
  (void) event;
  (void) param2;

  return param1;
}

int TAP_Main(void)
{
  TestSequence();

  return 0;
}
