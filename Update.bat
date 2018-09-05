@echo off
set Project=libFireBird
set TFROOT=C:\sw\prgm\Topfield

copy %Project%.h %TFROOT%\TMS\include
copy %Project%.a "%TFROOT%\TMS\crosstool\lib\%Project%.a"

pause