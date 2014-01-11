@echo off
rem Copies Bobura resource files
rem Copyright (C) 2007-2014 kaoru
rem $Id$

xcopy /y /i "%1res\messages" "%2messages"
rem xcopy /y /i "%1res\images" "%2images"
mkdir "%2images"
xcopy /y /i "%1res\win32\bobura_app.ico" "%2images"
