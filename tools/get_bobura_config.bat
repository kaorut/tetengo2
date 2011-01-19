@echo off
rem bobra_config.h Value Getter
rem Copyright (C) 2007-2011 kaoru
rem $Id$

for /f "tokens=*" %%x in ('cscript /nologo %~dp0get_bobura_config.js %1 %2') do set BOBURA_CONFIG=%%x
