#!/usr/bin/perl
# Checks the #include order.
# Copyright (C) 2007-2013 kaoru
# $Id$

use strict;

my(@stdlibs);
my(@boostlibs);

if (scalar(@ARGV) < 1)
{
	print "Usage: zzz_include_order.pl source_file\n";
	exit(0);
}

my($file_name) = $ARGV[0];

open(my $fh, $file_name) || die("Can't open $file_name");
while (<$fh>)
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
close($fh);

{
	my(@sorted) = sort(@stdlibs);
	if (!(\@sorted, \@stdlibs))
	{
		print "[".$file_name."]\n";
		print "WARNING: The standard headers are not sorted.";
	}
}

{
	my(@sorted) = sort(@boostlibs);
	if (!equal(\@sorted, \@boostlibs))
	{
		print "[".$file_name."]\n";
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

