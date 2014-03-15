#!/usr/bin/perl
# Checks the #include directives.
# Copyright (C) 2007-2014 kaoru
# $Id$


use strict;


my $source_filename_displayed = 0;

my $exit_status = 0;

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
	collect_stdlib_usages($source_filename, \%stdlib_header_mappings, \%usages);
	
	my %includes;
	collect_stdlib_includes($source_filename, \%includes);
	
	check($source_filename, \%usages, \%includes, \%stdlib_header_mappings);
	
	exit $exit_status;
}

sub print_usage
{
	print STDERR "Usage: ./chk_include.pl source_file stdlib_headers.txt\n"
}

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
				$$r_includes{$1} = 1;
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
	
	for my $usage (keys(%$r_usages))
	{
		my $header = $$r_mappings{$usage};
		if (!$$r_includes{$header})
		{
			print_warning($source_filename, 'Include <'.$header.'>.');
		}
	}
	
	my @used_headers = values(%$r_usages);
	for my $include (keys(%$r_includes))
	{
		my $found = -1;
		for (my $i = 0; $i < scalar(@used_headers); ++$i)
		{
			if ($used_headers[$i] eq $include)
			{
				$found = $i;
				last;
			}
		}
		if ($found < 0)
		{
			print_warning($source_filename, '<'.$include.'> is unused.');
		}
	}
}

sub print_warning
{
	my($source_filename, $message) = @_;
	
	if (!$source_filename_displayed)
	{
		print '['.$source_filename.']'."\n";
		$source_filename_displayed = 1;
	}
	
	print 'WARNING: '.$message."\n";
	
	$exit_status = 1;
}
