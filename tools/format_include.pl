#!/usr/bin/perl
# Format the #include directives.
# Copyright (C) 2007-2012 kaoru
# $Id$

use strict;

while (<STDIN>)
{
	if (/\#\s*include\s+(.*)$/)
	{
		print '#include '.$1."\n";
	}
}
