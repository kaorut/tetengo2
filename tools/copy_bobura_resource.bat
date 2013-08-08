@echo off
rem Copies Bobura resource files
rem Copyright (C) 2007-2013 kaoru
rem $Id$

xcopy /y /i "%1res\messages" "%2messages"
xcopy /y /i "%1res\images" "%2images"
copy /y "%1res\win32\bobura_app.ico" "%2images"
