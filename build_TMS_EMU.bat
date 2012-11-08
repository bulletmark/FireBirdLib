@echo off

if exist Compile_TMSEMU goto AlreadyEMU
touch Compile_TMSEMU
c:\sw\OS\cygwin\bin\find . -name "*.o" -delete
c:\sw\OS\cygwin\bin\find . -name "*.d" -delete

:AlreadyEMU

call build_TMS.bat
pause
