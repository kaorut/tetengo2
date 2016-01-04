#!/usr/bin/perl
# Checks the #include directives.
# Copyright (C) 2007-2016 kaoru
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
	collect_stdlib_usages($source_filename, \%stdlib_header_mappings, 1, \%usages);
	
	my @includes;
	collect_stdlib_includes($source_filename, \@includes);
	
	check($source_filename, \%usages, \@includes, \%stdlib_header_mappings);
	
	exit exit_status();
}

sub print_usage
{
	print STDERR "Usage: ./zzz_check_include.pl source_file stdlib_headers.txt\n"
}

sub collect_stdlib_includes
{
	my($source_filename, $r_includes) = @_;
	
	open(my $fh, $source_filename) || die "Can't open $source_filename";
	while(<$fh>)
	{
		chomp;
		my $line = $_;
		if ($line =~ /^\s*#\s*include\s+<([^>]+)>/)
		{
			if (is_stdlib_header($1))
			{
				push(@$r_includes, $1);
			}
		}
		
	}
	close($fh);
}

sub is_stdlib_header
{
	my($header_name) = @_;
	
	return 1 if $header_name =~ /^[a-z0-9_\/]+$/;
	return 1 if $header_name =~ /^boost\/.+\.hpp$/;
	return 1 if $header_name =~ /^boost\/.+\.h$/;
	return 1 if $header_name =~ /^Windows\.h$/;
	return 1 if $header_name =~ /^windowsx\.h$/;
	return 1 if $header_name =~ /^atlbase\.h$/;
	return 1 if $header_name =~ /^CommCtrl\.h$/;
	return 1 if $header_name =~ /^d2d1\.h$/;
	return 1 if $header_name =~ /^dxgiformat\.h$/;
	return 1 if $header_name =~ /^dwrite\.h$/;
	return 1 if $header_name =~ /^GdiPlus\.h$/;
	return 1 if $header_name =~ /^ObjBase\.h$/;
	return 1 if $header_name =~ /^Sh[a-zA-Z0-9]+\.h$/;
	return 1 if $header_name =~ /^Unknwn\.h$/;
	return 1 if $header_name =~ /^wincodec\.h$/;
	
	return 0;
}

sub check
{
	my($source_filename, $r_usages, $r_includes, $r_mappings) = @_;
	
	check_include_order($source_filename, $r_includes) if $source_filename !~ /tetengo2\/stdalt\.h/;
	check_header_includes($source_filename, $r_usages, $r_includes, $r_mappings);
	check_header_usages($source_filename, $r_usages, $r_includes);
}

sub check_include_order
{
	my($source_filename, $r_includes) = @_;
	
	if (scalar(sort_and_uniq($r_includes)) != scalar(@$r_includes))
	{
		print_warning($source_filename, 'Duplicate #includes found.');
		for my $include (@$r_includes)
		{
			print_warning($source_filename, '  '.$include);
		}
	}
	
	{
		# Standard Library
		my @original;
		for my $include (@$r_includes)
		{
			next if $include !~ /^[a-z0-9_\/]+$/;
			
			push(@original, $include);
		}
		
		my @sorted = sort(@original);
		
		if (join("\0", @sorted) ne join("\0", @original))
		{
			print_warning($source_filename, 'The standard libary header #include is not sorted.');
			for my $include (@original)
			{
				print_warning($source_filename, '  '.$include);
			}
		}
	}
	{
		# Boost Library
		my @original;
		for my $include (@$r_includes)
		{
			next if $include !~ /^boost\/.+\.hpp$/ && $include !~ /^boost\/.+\.h$/;
			
			push(@original, $include);
		}
		
		my @sorted = sort(@original);
		
		if (join("\0", @sorted) ne join("\0", @original))
		{
			print_warning($source_filename, 'The Boost libary header #include is not sorted.');
			for my $include (@original)
			{
				print_warning($source_filename, '  '.$include);
			}
		}
	}
}

sub sort_and_uniq
{
	my($r_array) = @_;
	
	my %hash;
	for my $element (@$r_array)
	{
		$hash{$element} = 1;
	}
	
	my @result = sort(keys(%hash));
	return @result;
}

sub check_header_includes
{
	my($source_filename, $r_usages, $r_includes, $r_mappings) = @_;
	
	for my $usage (keys(%$r_usages))
	{
		my $headers = $$r_mappings{$usage};
		for my $header (split(/\,/, $headers))
		{
			if (!exists_in_array($r_includes, $header))
			{
				print_warning($source_filename, 'Include <'.$header.'>.');
			}
		}
	}
}

sub exists_in_array
{
	my($r_array, $element) = @_;
	
	for my $array_element (@$r_array)
	{
		if ($array_element eq $element)
		{
			return 1;
		}
	}
	
	return 0;
}

sub check_header_usages
{
	my($source_filename, $r_usages, $r_includes) = @_;
	
	my @used_headers = values(%$r_usages);
	for my $include (@$r_includes)
	{
		my $found = -1;
		for (my $i = 0; $i < scalar(@used_headers); ++$i)
		{
			for my $used_header (split(/\,/, $used_headers[$i]))
			{
				if ($used_header eq $include)
				{
					$found = $i;
					last;
				}
			}
		}
		if ($found < 0)
		{
			print_warning($source_filename, '<'.$include.'> is unused.');
		}
	}
}
