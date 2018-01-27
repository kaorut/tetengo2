/*
	Solution Config Parser
	Copyright (C) 2007-2018 kaoru
	$Id$
*/

function trim(value)
{
	value = value.replace(/^\s+/, "");
	value = value.replace(/\s+$/, "");
	
	value = value.replace(/^\"/, "");
	value = value.replace(/\"$/, "");
	
	value = value.replace(/\\\\/g, "\\");
	
	value = value.replace(/\r?\n$/g, "");
	
	return value;
}

function parse(line, key)
{
	var pattern = "^\\s*\#\\s*define\\s+" + key +"\\s+";
	var matched = line.match(new RegExp(pattern));
	if (matched == null) return null;
	
	return trim(line.substring(matched.lastIndex));
}

function getMacroValue(stream, key)
{
	while (!stream.AtEndOfStream)
	{
		var parsed = parse(stream.ReadLine(), key);
		if (parsed != null)
		{
			return parsed;
		}
	}
	
	return null;
}

