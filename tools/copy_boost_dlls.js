/*
    Boost DLL Copier
    Copyright (C) 2007-2015 kaoru
    $Id$
*/

function getDestinationDirectory(solutionDirectory, releaseOrDebug, platform)
{
    var filesystem = WScript.CreateObject("Scripting.FileSystemObject");
    
    return filesystem.BuildPath(solutionDirectory, "bin\\" + releaseOrDebug + "." + platform);
}

function getLibNames(stream)
{
    var libNames = new Array;
    while (!stream.AtEndOfStream)
        libNames.push(stream.ReadLine());
    return libNames;
}

function getDllNames(boostLibsStream, version, debug)
{
    var libNames = getLibNames(boostLibsStream);
    
    var dllNames = new Array;
    for (i = 0; i < libNames.length; ++i)
    {
        dllNames.push(libNames[i] + "-*-mt-" + (debug ? "gd-" : "") + version + ".dll");
    }
    
    return dllNames;
}

function copyFile(sourceDirectory, destinationDirectory, fileName)
{
    var filesystem = WScript.CreateObject("Scripting.FileSystemObject");
    
    var sourceFile = filesystem.BuildPath(sourceDirectory, fileName);
    WScript.Echo("Copying \"" + sourceFile + "\" to \"" + destinationDirectory + "\" ...");
    filesystem.CopyFile(sourceFile, destinationDirectory);
}


// main

function include(script)
{
    var path = WScript.ScriptFullName.replace(new RegExp(WScript.ScriptName + "$"), "");
    var stream = WScript.CreateObject("Scripting.FileSystemObject").OpenTextFile(path + script, 1, false, 0);
    try { return stream.ReadAll(); } finally { stream.Close(); }
}
eval(include("zzz_parse_solution_config.js"));

if (WScript.Arguments.length <= 4)
{
    WScript.Echo("Usage: cscript copy_boost_dlls.js boost_libs.txt config.h SOLUTION_DIRECTORY  RELEASE_OR_DEBUG PLATFORM");
    WScript.Quit(1);
}
var boostLibsFileName = WScript.Arguments(0);
var configFileName = WScript.Arguments(1);
var solutionDirectory = WScript.Arguments(2);
var releaseOrDebug = WScript.Arguments(3);
var platform = WScript.Arguments(4);

var boostLibsStream = WScript.CreateObject("Scripting.FileSystemObject").OpenTextFile(boostLibsFileName, 1, false, 0);
try
{
    var configStream = WScript.CreateObject("Scripting.FileSystemObject").OpenTextFile(configFileName, 1, false, 0);
    try
    {
        var version = getMacroValue(configStream, "BOOST_VERSION");
        var sourceDirectory = getMacroValue(configStream, "BOOST_LIB_" + platform);
        var destinationDirectory = getDestinationDirectory(solutionDirectory, releaseOrDebug, platform);
        var dllNames = getDllNames(boostLibsStream, version, releaseOrDebug.toLowerCase() == "debug");

        for (var i = 0; i < dllNames.length; ++i)
            copyFile(sourceDirectory, destinationDirectory, dllNames[i]);
    }
    finally
    {
        configStream.Close();
    }
}
finally
{
    boostLibsStream.close();
}
