@echo off
rem Makes a exe zip file.
rem Copyright (C) 2007-2013 kaoru
rem $Id$

if not exist bin\Release.%1 exit /b 1
pushd bin\Release.%1

del /q ..\bobura.%1.zip
zip -9 ..\bobura.%1.zip * -x *.bsc *.lib

popd
