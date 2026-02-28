@echo off
set CFLAGS=^
-Wall -Wextra ^
-Og -ggdb3

set linking=

@echo on
gcc %CFLAGS% -o main.exe main.c %linking% && .\main.exe
@echo off
rem gcc %CFLAGS% -o main.exe main.c %linking% && .\main.exe && del .\main.exe
