@echo off
rem Code-signs a file.
rem Copyright (C) 2007-2018 kaoru
rem $Id$

if not exist "%~dp0zzz_codesign.bat" exit /b

call "%~dp0zzz_codesign.bat" "%1" "%2" "%3" "%4" "%5" "%6" "%7" "%8" "%9"
