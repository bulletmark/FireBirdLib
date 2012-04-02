@echo off
rem cls
set Project=Test
set API=C:\sw\prgm\Topfield\API\TF5000

echo ---%Project%
call gcc.bat %Project%.c

echo ---Linker
mips-ld --cref -o %Project%.elf -T %API%\TAP.LD %Project%.o -l FireBird -l c -l tap -l gcc -l FireBird -Map %Project%.map
mips-objcopy -O binary %Project%.elf %Project%.tap
erase %Project%.o %Project%.elf %Project%.map

echo ------
