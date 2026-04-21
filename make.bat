@echo off

set "ACTION=%1"
set "MAINFILE=main.cpp"
set "EXECUTABLE_FILE=main.exe"
set "LIBRARIES=user32.lib Gdi32.lib"

if "%ACTION%" == ""  (
	echo USAGE: make build ^| run
	EXIT /B
)

if %ACTION% EQU build (
	echo building into .\build\...
	:: pushd .\build
	clang-cl /Zi .\code\%MAINFILE% -o .\build\%EXECUTABLE_FILE% %LIBRARIES% && echo done! || echo compilation failed, error code: %ERRORLEVEL%
	:: popd 
	EXIT /B
) 

if %ACTION% EQU run (
	.\build\%EXECUTABLE_FILE% %2
	EXIT /B
)

:: if %ACTION% EQU run (
:: 	pushd build
:: 		:: .\%EXECUTABLE_FILE% file.lox
:: 		.\%EXECUTABLE_FILE% %2
:: 	popd
::  	EXIT /B
:: )

if %ACTION% EQU clean (
	echo cleaning the build folder...
	del .\build\*
	echo done!
	EXIT /B
)

if %ACTION% EQU push (
	git push https://github.com/collins994/handmade_hero main
	EXIT /B
)

if %ACTION% EQU pull (
	git pull https://github.com/collins994/handmade_hero main
	EXIT /B
)

if %ACTION% EQU debug (
	echo starting windbg session...
	windbgx .\build\%EXECUTABLE_FILE%
	EXIT /B
)

echo invalid option "%ACTION%"
