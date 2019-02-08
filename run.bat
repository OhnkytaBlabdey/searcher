@echo off
:lb1
cbuf -head |maze tree.txt 2>log.txt|ans 2>nul|cbuf -rear 
chk 0<log.txt

if %errorlevel% leq 0 (
echo fail
goto lb1
)
if %errorlevel% leq 1(
echo successed
goto lb2
)
echo not found
:lb2