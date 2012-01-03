#!/usr/bin/perl
# Checks the #include order.
# Copyright (C) 2007-2012 kaoru
# $Id$

use strict;

my(@stdlibs);
my(@boostlibs);

while (<STDIN>)
{
	s/\r?\n$//;
	my($line) = $_;
	
	if ($line =~ /(\#include\s+<[a-z0-9]+>)/)
	{
		push(@stdlibs, $1);
	}
	
	if ($line =~ /(\#include\s+<boost\/[a-z0-9_\/\.]+>)/)
	{
		push(@boostlibs, $1);
	}
}

{
	my(@sorted) = sort(@stdlibs);
	if (!(\@sorted, \@stdlibs))
	{
		print "WARNING: The standard headers are not sorted.";
	}
}

{
	my(@sorted) = sort(@boostlibs);
	if (!equal(\@sorted, \@boostlibs))
	{
		print "WARNING: The Boost headers are not sorted.\n";
	}
}


sub equal
{
	my($r_array1, $r_array2) = @_;
	
	return 0 if scalar(@$r_array1) != scalar(@$r_array2);
	
	for (my($i) = 0; $i < scalar(@$r_array1); ++$i)
	{
		return 0 if $$r_array1[$i] ne $$r_array2[$i];
	}
	
	return 1;
}

