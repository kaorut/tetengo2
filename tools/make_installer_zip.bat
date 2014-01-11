@echo off
rem Makes an installer zip file.
rem Copyright (C) 2007-2014 kaoru
rem $Id$

if not exist bin\installer.Release exit /b 1
pushd bin\installer.Release

del /q ..\bobura.zip
zip -9r ..\bobura.zip * -x *.bsc

popd
