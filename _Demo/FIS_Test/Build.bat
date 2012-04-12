@echo off
rem cls
set Project=FIS_Test

echo ---%Project%
call gcc.bat %Project%.c

echo ---Linker
mips-ld --cref -o %Project%.elf -T C:\sw\prgm\Topfield\API\TF5000\TAP.LD %Project%.o -l FireBird -l c -l tap -l gcc -l FireBird -Map %Project%.map
mips-objcopy -O binary %Project%.elf %Project%.tap
erase %Project%.o %Project%.elf %Project%.map

echo ------
tapcheck /f
