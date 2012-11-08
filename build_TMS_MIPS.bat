@echo off

if not exist Compile_TMSEMU goto AlreadyMIPS
erase Compile_TMSEMU
c:\sw\OS\cygwin\bin\find . -name "*.o" -delete
c:\sw\OS\cygwin\bin\find . -name "*.d" -delete

:AlreadyMIPS

call build_TMS.bat
pause
