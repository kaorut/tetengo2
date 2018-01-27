/*
	Solution Config Getter
	Copyright (C) 2007-2018 kaoru
	$Id$
*/

function include(script)
{
	var path = WScript.ScriptFullName.replace(new RegExp(WScript.ScriptName + "$"), "");
	var stream = WScript.CreateObject("Scripting.FileSystemObject").OpenTextFile(path + script, 1, false, 0);
	try { return stream.ReadAll(); } finally { stream.Close(); }
}
eval(include("zzz_parse_solution_config.js"));


if (WScript.Arguments.length < 1)
{
	WScript.Echo("Usage: cscript zzz_get_solution_config.js CONFIG_FILE_NAME MACRO_NAME");
	WScript.Quit(1);
}
var configFileName = WScript.Arguments(0);
var macroName = WScript.Arguments(1);

var stream = WScript.CreateObject("Scripting.FileSystemObject").OpenTextFile(configFileName, 1, false, 0);
try
{
	WScript.Echo(getMacroValue(stream, macroName));
}
finally
{
	stream.Close();
}
