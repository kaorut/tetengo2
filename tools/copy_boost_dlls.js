/*
	Boost DLL Copier
	Copyright (C) 2007-2011 kaoru
	$Id$
*/

function trim(string)
{
	var trimmed = string;
	
	var character_offset = trimmed.search(/[^ \t]/);
	if (character_offset == -1) return "";
		trimmed = trimmed.substring(character_offset);
	var whitespace_offset = trimmed.search(/[ \t]+$/);
	if (whitespace_offset >= 0)
		trimmed = trimmed.substring(0, whitespace_offset);
	
	return trimmed;
}

function parseLine(line, pattern)
{
	var trimmed = trim(line);
	
	var found_define_lib = trimmed.match(pattern);
	if (found_define_lib == null) return null;
	
	var key_value = trimmed.substring(found_define_lib.lastIndex);
	var found_whitespace = key_value.match(/\s+/);
	if (found_whitespace == null)
	{
		WScript.Echo("Syntax Error: " + trimmed);
		return null;
	}
	
	var key = key_value.substring(0, found_whitespace.index);
	var value = trim(key_value.substring(found_whitespace.lastIndex));
	value = value.replace(/\\\\/g, "\\");
	value = value.replace(/\"/g, "");
	return new Array(key, value);
}

function getSourceAndVersion()
{
	var source = new Array;
	var version = null;
	
	var filesystem = WScript.CreateObject("Scripting.FileSystemObject");
	var stream = filesystem.OpenTextFile("..\\bobura_config.h", 1, false, 0);
	while (!stream.AtEndOfStream)
	{
		var line = stream.ReadLine();
		
		var parsed1 = parseLine(line, /^#\s*define\s+BOOST_LIB_/);
		if (parsed1 != null)
		{
			source[parsed1[0]] = parsed1[1];
			continue;
		}
		
		var parsed2 = parseLine(line, /^#\s*define\s+BOOST_VERSION/);
		if (parsed2 != null)
		{
			version = parsed2[1];
			continue;
		}
	}
	stream.Close();
	
	return new Array(source, version);
}

function getDestination(solutionDirectory, releaseOrDebug)
{
	var filesystem = WScript.CreateObject("Scripting.FileSystemObject");
	
	return filesystem.BuildPath(solutionDirectory, "bin\\" + releaseOrDebug);
}

function getDllNames(version, debug)
{
	var dllNames = new Array;
	
	dllNames.push("boost_filesystem-*-mt-" + (debug ? "gd-" : "") + version + ".dll");
	dllNames.push("boost_program_options-*-mt-" + (debug ? "gd-" : "") + version + ".dll");
	dllNames.push("boost_system-*-mt-" + (debug ? "gd-" : "") + version + ".dll");
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

if (WScript.Arguments.length < 3)
{
	WScript.Echo(
		"Usage: cscript copy_boost_dlls.js SOLUTION_DIRECTORY RELEASE_OR_DEBUG PLATFORM"
	);
	WScript.Quit(1);
}
var solutionDirectory = WScript.Arguments(0);
var releaseOrDebug = WScript.Arguments(1);
var platform = WScript.Arguments(2);

var sourceAndVersion = getSourceAndVersion();
var destination = getDestination(solutionDirectory, releaseOrDebug);

var sourceDirectory = sourceAndVersion[0][platform];
if (sourceDirectory == null || sourceDirectory.length == 0)
{
	WScript.Echo("The Boost source directory is unknown.");
	WScript.Quit(1);
}
var destinationDirectory = destination + "." + platform;
var version = sourceAndVersion[1];
if (version == null || version.length == 0)
{
	WScript.Echo("The Boost version is unknown.");
	WScript.Quit(1);
}

var dllNames =
	getDllNames(version, releaseOrDebug.toLowerCase() == "debug");
for (var i = 0; i < dllNames.length; ++i)
	copyFile(sourceDirectory, destinationDirectory, dllNames[i]);

