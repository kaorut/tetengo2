#!/usr/bin/perl
# Makes a test case list.
# Copyright (C) 2007-2013 kaoru
# $Id$

use strict;

if (scalar(@ARGV) < 1)
{
	print "Usage: make_test_case_list.pl input\n";
	exit(0);
}

my(@suit);

open(my $fh, "<", $ARGV[0]) or die("Can't open: ".$ARGV[0]);
while (<$fh>)
{
	s/\r?\n//g;
	my ($line) = $_;
	if    ($line =~ /BOOST_AUTO_TEST_SUITE\(([a-zA-Z0-9_]+)\)/)
	{
		push(@suit, $1);
	}
	elsif ($line =~ /BOOST_AUTO_TEST_SUITE_END\(\)/)
	{
		pop(@suit);
	}
	elsif ($line =~ /BOOST_AUTO_TEST_CASE\(([a-zA-Z0-9_]+)\)/)
	{
		print join('::', @suit, $1)."\n";
	}
}
close($fh);
