@echo off
set Project=libFireBird
set TFROOT=C:\sw\prgm\Topfield
set PATH=%TFROOT%\gccForTMS\crosstool\bin;C:\sw\OS\cygwin\bin

copy %Project%.h %TFROOT%\API\TMS\include

if exist Compile_TMSEMU goto Compile_TMSEMU

echo Building MIPS FBLib
bash -i -c "make -j 8"
goto Compile_Done

:Compile_TMSEMU
echo Building Intel FBLib
bash -i -c "make -j 8 --file=Makefile_tmsemu"

:Compile_Done
copy %Project%.a "%TFROOT%\gccForTMS\crosstool\lib\%Project%.a"
copy %Project%_tmsemu.a "%TFROOT%\gccForTMS\crosstool\lib\%Project%_tmsemu.a"
