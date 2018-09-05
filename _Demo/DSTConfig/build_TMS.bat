@echo off
cd /d %~dp0%
set TFROOT=C:\sw\prgm\Topfield
set PATH=%TFROOT%\TMS\crosstool\bin;C:\sw\OS\cygwin\bin
bash -i -c make
