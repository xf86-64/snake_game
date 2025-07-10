
@echo off
title ./snake
echo Compiling program...

if exist %CD% (
  rmdir /s /q bin
  mkdir bin 
) else (
  mkdir bin
)
gcc src/atoi.c src/snake.c src/main.c -lncurses -o bin/snake
if not %errorlevel% == 0 (
 cls
 echo Program terminated with an error 
 pause 
)

