#!/usr/bin/perl
# Checks the #include directives.
# Copyright (C) 2007-2010 kaoru
# $Id$

use strict;
use File::Basename;

if (scalar(@ARGV) < 2)
{
	print "Usage: check_includes.pl source_file stdlib_headers.txt\n";
	exit(0);
}

# main
{
	my(%stdlib_headers);
	read_stdlib_headers($ARGV[1], \%stdlib_headers);

	my(%includes, %subincludes, %stdlib_header_usage);
	
	scan_source(
		$ARGV[0],
		\%stdlib_headers,
		\%includes,
		\%subincludes,
		\%stdlib_header_usage
	);
	
	foreach my $key (sort(keys(%includes)))
	{
		my($value) = $includes{$key};
		print 'INC: '.$value.' #include <'.$key.">\n";
	}
	foreach my $key (sort(keys(%subincludes)))
	{
		my($value) = $subincludes{$key};
		print 'SUBINC: #include <'.$key.">\n";
	}
	while (my($key, $value) = each(%stdlib_header_usage))
	{
		print $key.' -> '.$value."\n";
	}
}

sub read_stdlib_headers
{
	my($file_name, $r_stdlib_headers) = @_;
	
	my($fh);
	open($fh, $file_name);
	if (!$fh)
	{
		die("Can't open $file_name");
	}
	while (<$fh>)
	{
		s/\r?\n$//;
		my($element, $headers) = split(/\s+/);
		$$r_stdlib_headers{$element} = $headers;
	}
	close($fh);
}

sub scan_source
{
	my(
		$file_name,
		$r_stdlib_headers,
		$r_includes,
		$r_subincludes,
		$r_stdlib_header_usage
	) = @_;
	
	print "SCANNING: $file_name\n";
	my($fh);
	open($fh, $file_name);
	if (!$fh)
	{
		die("Can't open $file_name");
	}
	while (<$fh>)
	{
		s/\r?\n$//;
		my($line) = $_;
		
		if ($line =~ /(\/\/|)\s*\#\s*include\s+([\"<])([^\">]+)[\">]/)
		{
			if ($2 eq '<')
			{
				if ($$r_includes{$3} ne '')
				{
					print "WARINING: #include duplicated: $3\n";
				}
				$$r_includes{$3} = $1 eq '' ? '  ' : $1;
			}
			elsif ($2 eq '"')
			{
				scan_subsource(dirname($file_name).'/'.$3, $r_subincludes);
			}
		}
		elsif ($r_stdlib_header_usage)
		{
			while (
				my($stdlib_element, $stdlib_header) = each(%$r_stdlib_headers)
			)
			{
				if ($line =~ /$stdlib_element/)
				{
					$$r_stdlib_header_usage{$stdlib_element} = $stdlib_header;
				}
			}
		}
	}
	close($fh);
	
	while (my($include, $commented) = each(%$r_includes))
	{
		my($subfound) = $$r_subincludes{$include} ne '';
		if ($commented eq '//')
		{
			if (!$subfound)
			{
				print "WARING: should *NOT* be commented out: ".
					"#include <$include>\n";
			}
		}
		else
		{
			if ($subfound)
			{
				print "WARING: *SHOULD* be commented out: ".
					"#include <$include>\n";
			}
		}
	}
}

sub scan_subsource
{
	my($file_name, $r_includes) = @_;
	
	print "SCANNING: $file_name\n";
	my($fh);
	open($fh, $file_name);
	if (!$fh)
	{
		die("Can't open $file_name");
	}
	while (<$fh>)
	{
		s/\r?\n$//;
		my($line) = $_;
		
		if ($line =~ /(\/\/|)\s*\#\s*include\s+([\"<])([^\">]+)[\">]/)
		{
			if ($2 eq '<')
			{
				$$r_includes{$3} = 'SUBINC';
			}
			elsif ($2 eq '"')
			{
				scan_subsource(dirname($file_name).'/'.$3, $r_includes);
			}
		}
	}
	close($fh);
}
