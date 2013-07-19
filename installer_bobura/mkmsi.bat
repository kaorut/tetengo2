@echo off
rem Launches the NMAKE Script.
rem Copyright (C) 2007-2013 kaoru
rem $Id$

if        "%PLATFORM%"=="Win32" (
    set ARCH=x86
) else if "%PLATFORM%"=="x64" (
    set ARCH=x64
)

nmake /f Makefile.nmake "%1" "%2" "%3" "%4" "%5" "%6" "%7" "%8" "%9"

set ARCH=
