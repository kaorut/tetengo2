rem @echo off
rem Solution Config Value Getter
rem Copyright (C) 2007-2016 kaoru
rem $Id$

for /f "tokens=*" %%x in ('cscript /nologo %~dp0zzz_get_solution_config.js %1 %2 %3') do set SOLUTION_CONFIG=%%x
