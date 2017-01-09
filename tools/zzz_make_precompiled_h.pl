#!/usr/bin/perl
# Makes precompiled.h.
# Copyright (C) 2007-2017 kaoru
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
	
	my $stdlib_headers_filename = $ARGV[0];
	my $precompiled_template_filename = $ARGV[1];
	
	my %stdlib_header_mappings;
	make_stdlib_headers_mappings($stdlib_headers_filename, \%stdlib_header_mappings);
	
	my %stdlib_headers;
	my %boost_headers;
	collect_headers(\%stdlib_header_mappings, \%stdlib_headers, \%boost_headers);
	
	print_precompiled_h(\%stdlib_headers, \%boost_headers, $precompiled_template_filename);
}

sub print_usage
{
	print STDERR "Usage: ./zzz_make_precompiled_h.pl stdlib_headers.txt precompiled.template.h\n"
}

sub collect_headers
{
	my($r_mappings, $r_stdlib_headers, $r_boost_headers) = @_;
	
	for my $value (values(%$r_mappings))
	{
		if ($value =~ /^boost\// && $value !~ /^boost\/test\//)
		{
			$$r_boost_headers{$value} = 1;
		}
		elsif ($value =~ /^[a-z0-9_]+$/)
		{
			$$r_stdlib_headers{$value} = 1;
		}
	}
}

sub print_precompiled_h
{
	my($r_stdlib_headers, $r_boost_headers, $precompiled_template_filename) = @_;
	
	open(my $fh, $precompiled_template_filename) || die("Can't open $precompiled_template_filename");
	while (<$fh>)
	{
		if (/^\/\/\/\/STDLIB_BOOST_INCLUDES\/\/\/\//)
		{
			print "// The standard library headers\n";
			for my $key (sort(keys(%$r_stdlib_headers)))
			{
				print '#include <'.$key.'>'."\n";
			}
			print "\n";
			
			print "// The Boost library headers\n";
			for my $key (sort(keys(%$r_boost_headers)))
			{
				print '#include <'.$key.'>'."\n";
			}
			print "\n";
		}
		else
		{
			print $_;
		}
	}
}
