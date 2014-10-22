#!/usr/bin/perl
# Checks the #include directives.
# Copyright (C) 2007-2014 kaoru
# $Id$


use strict;


my($source_filename) = $ARGV[0];

my(%occurrence);

open(my $fh, $source_filename) || die "Can't open $source_filename";
my($section);
while(<$fh>)
{
	if (/\/\*+ ([0-9A-Za-z ]+) \*+\//)
	{
		$section = $1.': ';
		next;
	}
	if (/ template class /)
	{
		last;
	}
	if (/[ :](type::[0-9A-Za-z_:]+)/)
	{
		if ($1 ne 'type::value')
		{
			++$occurrence{$section.$1};
		}
	}
}
close($fh);

my($source_filename_shown) = 0;
foreach my $name (sort(keys(%occurrence)))
{
	my($count) = $occurrence{$name};
	
	if ($count >= 2)
	{
		if (!$source_filename_shown)
		{
			print "WARNING: $source_filename: Same type list type is used twice or more.\n";
			$source_filename_shown = 1;
		}
		
		print "  ".$name."\n";
	}
}