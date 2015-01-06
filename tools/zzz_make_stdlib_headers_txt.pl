#!/usr/bin/perl
# Makes stdlib_headers.txt.
# Copyright (C) 2007-2015 kaoru
# $Id$


use strict;
use File::Basename;
use lib dirname($0);
use zzz_stdlib_usage;


# main
{
	if (scalar(@ARGV) < 2)
	{
		print_usage();
		exit 1;
	}
	
	my $source_filename = $ARGV[0];
	my $stdlib_headers_filename = $ARGV[1];
	
	my %stdlib_header_mappings;
	make_stdlib_headers_mappings($stdlib_headers_filename, \%stdlib_header_mappings);
	
	my %usages;
	collect_stdlib_usages($source_filename, \%stdlib_header_mappings, 0, \%usages);
	
	print_stdlib_usages(\%usages);
}

sub print_usage
{
	print STDERR "Usage: ./zzz_make_stdlib_headers_txt.pl source_file stdlib_headers.txt\n"
}

sub print_stdlib_usages
{
	my($r_usages) = @_;
	
	while (my($usage, $header) = each(%$r_usages))
	{
		$header = '<<_UNKNOWN_HEADER_>>' if $header eq '';
		printf("%-48s %s\n", $usage, $header);
	}
}

