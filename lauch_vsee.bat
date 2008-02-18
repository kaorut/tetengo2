@echo off

rem Visual Studio Express Edition Launcher.
rem
rem Visual Studio Express Edition (VSEE) is lack of some essential files for
rem Win32 programming such as afxres.h.
rem The environment variable USE_VSEE makes VSEE include alternatives instead
rem of the essential files.
rem
rem $Id$
rem Copyright (C) 2007-2008 kaoru

set USE_VSEE=USE_VSEE

start bobura.sln
