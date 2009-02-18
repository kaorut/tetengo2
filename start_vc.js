/*
	Visual C++ Launcher for Bobura
	Copyright (C) 2007-2009 kaoru
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

function normalizeLine(line)
{
	var normalized = line;
	
	var comment_offset = normalized.indexOf("#");
	if (comment_offset >= 0)
		normalized = normalized.substring(0, comment_offset);
	
	return trim(normalized);
}

function parseSettingLine(line)
{
	var equal_offset = line.indexOf("=");
	if (equal_offset == -1)
		return new Array(trim(line), "");
	
	return new Array(
		trim(line.substring(0, equal_offset)),
		trim(line.substring(equal_offset + "=".length))
	);
}

function readSettings()
{
	var settings = new Array;
	
	var filesystem = WScript.CreateObject("Scripting.FileSystemObject");
	var stream = filesystem.OpenTextFile("start_vc_config.txt", 1, false, 0);
	while (!stream.AtEndOfStream)
	{
		var normalized = normalizeLine(stream.ReadLine());
		if (normalized.length == 0) continue;
		settings.push(parseSettingLine(normalized));
	}
	stream.Close();
	
	return settings;
}

function setEnvironment(environment, settings)
{
	for (var i = 0; i < settings.length; ++i)
		environment(settings[i][0]) = settings[i][1];
}

// main

var shell = WScript.CreateObject("WScript.Shell");
var environment = shell.Environment("Process");
var settings = readSettings();
setEnvironment(environment, settings);
shell.Run("cmd");
//shell.Run("bobura.sln");
