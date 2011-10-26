/*
	Boost DLL Copier
	Copyright (C) 2007-2011 kaoru
	$Id$
*/

function getDestinationDirectory(solutionDirectory, releaseOrDebug, platform)
{
	var filesystem = WScript.CreateObject("Scripting.FileSystemObject");
	
	return filesystem.BuildPath(
		solutionDirectory, "bin\\" + releaseOrDebug + "." + platform
	);
}

function getDllNames(version, debug)
{
	var dllNames = new Array;
	
	dllNames.push("boost_date_time-*-mt-" + (debug ? "gd-" : "") + version + ".dll");
	dllNames.push("boost_filesystem-*-mt-" + (debug ? "gd-" : "") + version + ".dll");
	dllNames.push("boost_program_options-*-mt-" + (debug ? "gd-" : "") + version + ".dll");
	dllNames.push("boost_system-*-mt-" + (debug ? "gd-" : "") + version + ".dll");
	dllNames.push("boost_thread-*-mt-" + (debug ? "gd-" : "") + version + ".dll");
	dllNames.push("boost_unit_test_framework-*-mt-" + (debug ? "gd-" : "") + version + ".dll");
	
	return dllNames;
}

function copyFile(sourceDirectory, destinationDirectory, fileName)
{
	var filesystem = WScript.CreateObject("Scripting.FileSystemObject");
	
	var sourceFile = filesystem.BuildPath(sourceDirectory, fileName);
	WScript.Echo(
		"Copying \"" + sourceFile + "\" to \"" + destinationDirectory +
		"\" ..."
	);
	filesystem.CopyFile(sourceFile, destinationDirectory);
}


// main

function include(script)
{
	var path =
		WScript.ScriptFullName.replace(
			new RegExp(WScript.ScriptName + "$"), ""
		);
	var stream =
		WScript.CreateObject("Scripting.FileSystemObject").OpenTextFile(
			path + script, 1, false, 0
		);
	try { return stream.ReadAll(); } finally { stream.Close(); }
}
eval(include("parse_bobura_config.js"));

if (WScript.Arguments.length < 2)
{
	WScript.Echo(
		"Usage: cscript copy_boost_dlls.js SOLUTION_DIRECTORY RELEASE_OR_DEBUG PLATFORM"
	);
	WScript.Quit(1);
}
var solutionDirectory = WScript.Arguments(0);
var releaseOrDebug = WScript.Arguments(1);
var platform = WScript.Arguments(2);

var stream =
	WScript.CreateObject("Scripting.FileSystemObject").OpenTextFile(
		solutionDirectory + "bobura_config.h", 1, false, 0
	);
try
{
	var version = getMacroValue(stream, "BOOST_VERSION");
	var sourceDirectory = getMacroValue(stream, "BOOST_LIB_" + platform);
	var destinationDirectory =
		getDestinationDirectory(solutionDirectory, releaseOrDebug, platform);
	var dllNames =
		getDllNames(version, releaseOrDebug.toLowerCase() == "debug");

	for (var i = 0; i < dllNames.length; ++i)
		copyFile(sourceDirectory, destinationDirectory, dllNames[i]);
}
finally
{
	stream.Close();
}
