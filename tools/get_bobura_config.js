/*
	bobra_config.h Getter
	Copyright (C) 2007-2012 kaoru
	$Id$
*/

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


if (WScript.Arguments.length < 1)
{
	WScript.Echo("Usage: cscript get_bobura_config.js SOLUTION_DIRECTORY MACRO_NAME");
	WScript.Quit(1);
}
var solutionDirectory = WScript.Arguments(0);
var macroName = WScript.Arguments(1);

var stream =
	WScript.CreateObject("Scripting.FileSystemObject").OpenTextFile(
		solutionDirectory + "bobura_config.h", 1, false, 0
	);
try
{
	WScript.Echo(getMacroValue(stream, macroName));
}
finally
{
	stream.Close();
}
