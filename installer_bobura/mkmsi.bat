@echo off
rem Launches the NMAKE Script.
rem Copyright (C) 2007-2013 kaoru
rem $Id$

if not "%MKMSI_PLATFORM%"=="x64" (
    nmake PLATFORM=Win32 ARCH=x86 /f Makefile.nmake "%1" "%2" "%3" "%4" "%5" "%6" "%7" "%8" "%9"
)
if not "%MKMSI_PLATFORM%"=="Win32" (
    nmake PLATFORM=x64 ARCH=x64 /f Makefile.nmake "%1" "%2" "%3" "%4" "%5" "%6" "%7" "%8" "%9"
)
