#!/usr/bin/perl
# Checks typedefs.
# Copyright (C) 2007-2013 kaoru
# $Id$

use strict;

if (scalar(@ARGV) < 2)
{
	print "Usage: zzz_check_typedefs.pl base_path input\n";
	exit(0);
}

my($base_path) = $ARGV[0];
my($file_path) = $ARGV[1];

my(@defined_typedefs);
foreach my $typedef (`$base_path/zzz_list_typedefs.pl $file_path`)
{
	$typedef =~ s/\r?\n//g;
	push(@defined_typedefs, $typedef);
}

my(%typedef_count);
open(my $fh, "<", $file_path) or die("Can't open: ".$file_path);
while (<$fh>)
{
	my($line) = $_;
	foreach my $defined_typedef (@defined_typedefs)
	{
		if ($line =~ /$defined_typedef/)
		{
			$typedef_count{$defined_typedef}++;
		}
	}
}
close($fh);

while (my($typedef, $count) = each(%typedef_count))
{
	if ($count <= 1)
	{
		print 'WARNING: not used: '.$file_path.': '.$typedef."\n";
	}
}
