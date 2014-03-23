#!/usr/bin/perl
# The standard library usage utility.
# Copyright (C) 2007-2014 kaoru
# $Id$


use strict;


sub make_stdlib_headers_mappings
{
	my($stdlib_headers_filename, $r_stdlib_header_mappings) = @_;
	
	open(my $fh, $stdlib_headers_filename) || die "Can't open $stdlib_headers_filename";
	while(<$fh>)
	{
		chomp;
		my $line = $_;
		my ($stdlib_usage, $header_name) = split(/\s+/, $line);
		$$r_stdlib_header_mappings{$stdlib_usage} = $header_name;
	}
	close($fh);
}

sub collect_stdlib_usages
{
	my($source_filename, $r_mappings, $r_usages) = @_;
	
	open(my $fh, $source_filename) || die "Can't open $source_filename";
	while(<$fh>)
	{
		chomp;
		my $line = $_;
		
		next if $line =~/\#include\s+/;
		
		while (
			$line =~ /(std::[a-zA-Z0-9_\:]*[a-zA-Z0-9_])/ ||
			$line =~ /(assert)/ ||
			$line =~ /(boost::[a-zA-Z0-9_\:]*[a-zA-Z0-9_])/ ||
			$line =~ /(BOOST_[A-Z0-9_]*[a-zA-Z0-9_])/ ||
			$line =~ /[^a-zA-Z0-9_\:](::[A-Z][a-zA-Z0-9_\:]*[a-zA-Z0-9_])/ ||
			$line =~ /(ATL::[a-zA-Z0-9_\:]*[a-zA-Z0-9_])/ ||
			$line =~ /(Gdiplus::[a-zA-Z0-9_\:]*[a-zA-Z0-9_])/ ||
			$line =~ /(D2D1::[a-zA-Z0-9_\:]*[a-zA-Z0-9_])/ ||
			$line =~ /(D2DERR_[A-Z0-9_]*)/ ||
			$line =~ /(WINCODEC_[A-Z0-9_]*)/ ||
			$line =~ /(VK_[A-Z0-9_]*)/ ||
			$line =~ /(WM_[A-Z0-9_]*)/ ||
			$line =~ /(GET_[XY]_LPARAM)/ ||
			$line =~ /(WINAPI)/
		)
		{
			my $header = $$r_mappings{$1};
			if ($header eq '')
			{
				print_warning($source_filename, '"'.$1.'" is unknown in stdlib_headers.txt.');
				$line =~ s/$1//g;
				next;
			}
			$$r_usages{$1} = $header;
			$line =~ s/$1//g;
		}
	}
	close($fh);
}

1;
