#ifndef CALLEETAPCOM_H
#define CALLEETAPCOM_H

// TAP id and name
#define CALLEE_ID       2
#define CALLEE_Name     "Callee"
#define CALLEE_TAPName  CALLEE_Name ".tap"

//Launch parameter
typedef struct
{
  dword  StructVersion;
  char   AnyText[20];
  dword  AnyData;
} Callee_Parameters;

// version
#define Callee_Param_Version 1


#endif
