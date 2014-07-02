@echo off
set Project=libFireBird
set TFROOT=C:\sw\prgm\Topfield

copy %Project%.h %TFROOT%\API\TMS\include
copy %Project%.a "%TFROOT%\gccForTMS\crosstool\lib\%Project%.a"
