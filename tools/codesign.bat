@echo off
rem Code-signs a file.
rem Copyright (C) 2007-2014 kaoru
rem $Id$

if not exist "%1tools\zzz_codesign.bat" exit /b

"%1tools\zzz_codesign.bat" "%2" "%3" "%4" "%5" "%6" "%7" "%8" "%9"
