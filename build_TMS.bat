@echo off
cd /d %~dp0%
set Project=libFireBird
set TFROOT=C:\sw\prgm\Topfield
set PATH=%TFROOT%\TMS\crosstool\bin;C:\sw\OS\cygwin\bin

copy %Project%.h %TFROOT%\TMS\include

if exist Compile_TMSEMU goto Compile_TMSEMU

echo Building MIPS FBLib
bash -i -c "make -j 8"
goto Compile_Done

:Compile_TMSEMU
echo Building Intel FBLib
bash -i -c "make -j 8 --file=Makefile_tmsemu"

:Compile_Done

copy %Project%.a "%TFROOT%\TMS\crosstool\lib\%Project%.a"
