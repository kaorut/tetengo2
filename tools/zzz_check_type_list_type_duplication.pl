#!/usr/bin/perl
# Checks the #include directives.
# Copyright (C) 2007-2014 kaoru
# $Id$


use strict;


my($source_filename) = $ARGV[0];

my(%occurrence);

open(my $fh, $source_filename) || die "Can't open $source_filename";
while(<$fh>)
{
	if (/[ :](type::[0-9A-Za-z_:]+)/)
	{
		if ($1 ne 'type::value')
		{
			++$occurrence{$1};
		}
	}
}
close($fh);

my($source_filename_shown) = 0;
while (my($name, $count) = each(%occurrence))
{
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