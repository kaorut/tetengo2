#!/usr/bin/perl
# Checks the #include directives.
# Copyright (C) 2007-2011 kaoru
# $Id$

use strict;
use File::Basename;

if (scalar(@ARGV) < 3)
{
	print "Usage: check_includes.pl ".
		"solution_directory source_file stdlib_headers.txt [show_progress]\n";
	exit(0);
}

my(@special_header_patterns) = (
	'^bobura\.',
	'^tetengo2\.',
	'^concept_',
);
my(@special_header_directories) = (
	$ARGV[0].'/bobura/src',
	$ARGV[0].'/bobura/test',
	$ARGV[0].'/bobura_model/include',
	$ARGV[0].'/bobura_model/test',
	$ARGV[0].'/tetengo2/include',
	$ARGV[0].'/tetengo2/test',
);

my($show_progress) = $ARGV[3] ne '';

# main
{
	my(%stdlib_headers);
	read_stdlib_headers($ARGV[2], \%stdlib_headers);

	my(%includes, %subincludes, %stdlib_header_usage);
	
	scan_source(
		$ARGV[1],
		\%stdlib_headers,
		\%includes,
		\%subincludes,
		\%stdlib_header_usage
	);
	
	while (my($key, $value) = each(%stdlib_header_usage))
	{
		foreach my $include (split(/\,/, $value))
		{
			if ($includes{$include} eq '')
			{
				if ($subincludes{$include} eq '')
				{
					print 'WARNING: Include <'.$include.">.\n";
				}
				else
				{
					print 'WARNING: Include <'.$include.
						"> but comment it out.\n";
				}
			}
		}
	}
	
	{
		my(@used_includes) = values(%stdlib_header_usage);
		foreach my $include (keys(%includes))
		{
			if (!contains_string(\@used_includes, $include))
			{
				print 'WARNING: UNUSED: <'.$include.">.\n";
			}
		}
	}
	
	foreach my $key (sort(keys(%includes)))
	{
		my($value) = $includes{$key};
		print 'INC: '.$value.' #include <'.$key.">\n";
	}
	foreach my $key (sort(keys(%subincludes)))
	{
		my($value) = $subincludes{$key};
		print 'SUBINC: #include <'.$key.'> in '.$value."\n";
	}
	while (my($key, $value) = each(%stdlib_header_usage))
	{
		printf("%-48s %s\n", $key, $value);
	}
}

sub read_stdlib_headers
{
	my($file_name, $r_stdlib_headers) = @_;
	
	open(my $fh, $file_name) || die("Can't open $file_name");
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
	
	print STDERR "Scanning: $file_name        \r" if $show_progress;
	open(my $fh, $file_name) || die("Can't open $file_name");
	while (<$fh>)
	{
		s/\r?\n$//;
		my($line) = $_;
		
		my(@parsed_include);
		if (parse_include($line, \@parsed_include))
		{
			my($commented) = $parsed_include[0];
			my($quotation) = $parsed_include[1];
			my($subfile_name) = $parsed_include[2];
			if ($quotation eq '<' && !special_header($subfile_name))
			{
				if ($$r_includes{$subfile_name} ne '')
				{
					print "WARNING: #include duplicated: $3\n";
				}
				if (is_std_or_boost_header($subfile_name))
				{
					$$r_includes{$subfile_name} =
						$commented eq '' ? '  ' : $commented;
				}
			}
			else
			{
				my(@directories) = @special_header_directories;
				push(@directories, dirname($file_name));
				scan_subsource(
					$subfile_name, \@directories, $r_subincludes
				);
			}
		}
		elsif ($r_stdlib_header_usage)
		{
			my($code_line) = $line;
			while (
				$code_line =~ /(std::[a-zA-Z0-9_\:]*)/ ||
				$code_line =~ /(assert)/ ||
				$code_line =~ /(NULL)/ ||
				$code_line =~ /(boost::[a-zA-Z0-9_\:]*)/ ||
				$code_line =~ /(BOOST_[A-Z0-9_]*)/ ||
				$code_line =~ /[^a-zA-Z0-9_\:](::[A-Z][a-zA-Z0-9_\:]*)/ ||
				$code_line =~ /(ATL::[a-zA-Z0-9_\:]*)/ ||
				$code_line =~ /(Gdiplus::[a-zA-Z0-9_\:]*)/
			)
			{
				my($usage) = $1;
				
				if ($$r_stdlib_headers{$usage} eq '')
				{
					$$r_stdlib_header_usage{$usage} = '<< UNKNOWN HEADER >>';
				}
				else
				{
					$$r_stdlib_header_usage{$usage} =
						$$r_stdlib_headers{$usage};
				}
				
				$code_line =~ s/$usage//;
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
				print "WARNING: should *NOT* comment out: ".
					"#include <$include>\n";
			}
		}
		else
		{
			if ($subfound)
			{
				print "WARNING: *SHOULD* comment out: ".
					"#include <$include>\n";
			}
		}
	}
	print STDERR "Scanned: $file_name        \n" if $show_progress;
}

sub scan_subsource
{
	my($file_name, $r_directories, $r_includes) = @_;
	
	print STDERR "Scanning: $file_name        \r" if $show_progress;
	my($fh);
	my($opened) = 0;
	foreach my $directory (@$r_directories)
	{
		if (open($fh, $directory.'/'.$file_name))
		{
			$opened = 1;
			last;
		}
	}
	if (!$opened)
	{
		print "WARNING: Can't open $file_name\n";
		return;
	}
	while (<$fh>)
	{
		s/\r?\n$//;
		my($line) = $_;
		
		my(@parsed_include);
		if (parse_include($line, \@parsed_include))
		{
			my($commented) = $parsed_include[0];
			my($quotation) = $parsed_include[1];
			my($subfile_name) = $parsed_include[2];
			if ($quotation eq '<' && !special_header($subfile_name))
			{
				if (is_std_or_boost_header($subfile_name))
				{
					$$r_includes{$subfile_name} .= basename($file_name).", ";
				}
			}
			else
			{
				my(@directories) = @special_header_directories;
				push(@directories, dirname($file_name));
				scan_subsource(
					$subfile_name, \@directories, $r_includes
				);
			}
		}
	}
	close($fh);
}

sub parse_include
{
	my($line, $r_parsed) = @_;
	if ($line !~ /(\/\/|)\s*\#\s*include\s+([\"<])([^\">]+)[\">]/)
	{
		return 0;
	}
	
	push(@$r_parsed, $1);
	push(@$r_parsed, $2);
	push(@$r_parsed, $3);
	
	return 1;
}

sub special_header
{
	my($file_name) = @_;
	
	foreach my $pattern (@special_header_patterns)
	{
		return 1 if $file_name =~ /$pattern/;
	}
	
	return 0;
}

sub is_std_or_boost_header
{
	my($header_name) = @_;
	
	return 1 if $header_name =~ /^[a-z0-9_\/]+$/;
	return 1 if $header_name =~ /^boost\/.+\.hpp$/;
	return 1 if $header_name =~ /^Windows\.h$/;
	return 1 if $header_name =~ /^atlbase\.h$/;
	return 1 if $header_name =~ /^CommCtrl\.h$/;
	return 1 if $header_name =~ /^GdiPlus\.h$/;
	return 1 if $header_name =~ /^ObjBase\.h$/;
	return 1 if $header_name =~ /^ShObjIdl\.h$/;
	
	return 0;
}

sub contains_string
{
	my($r_array, $value) = @_;
	foreach my $element (@$r_array)
	{
		foreach my $element2 (split(/\,/, $element))
		{
			return 1 if $element2 eq $value;
		}
	}
	return 0;
}
