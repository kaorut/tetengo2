#!/usr/bin/perl
# Checks typedefs.
# Copyright (C) 2007-2014 kaoru
# $Id$

use strict;

if (scalar(@ARGV) < 3)
{
	print "Usage: zzz_check_typedefs.pl tools_directory input typedef_check_ignore.txt\n";
	exit(0);
}

my($tools_directory) = $ARGV[0];
my($file_path) = $ARGV[1];
my($typedef_ignore_path) = $ARGV[2];

my($exit_status) = 0;

my(@defined_typedefs);
foreach my $typedef (`$tools_directory/zzz_list_typedefs.pl $file_path`)
{
	$typedef =~ s/\r?\n//g;
	push(@defined_typedefs, $typedef);
}

my(%typedef_count);
open(my $fh, "<", $file_path) or die("Can't open: ".$file_path);
while (<$fh>)
{
	my($line) = $_;
	foreach my $defined_namespace_typedef (@defined_typedefs)
	{
		my($namespace, $defined_typedef) = split(/\s+/, $defined_namespace_typedef);
		if ($line =~ /::$defined_typedef/)
		{
			if (
				$line =~ / $defined_typedef/ ||
				$typedef_count{$namespace.'::'.$defined_typedef} > 0
			)
			{
				$typedef_count{$namespace.'::'.$defined_typedef}++;
			}
		}
		elsif ($line =~ /$defined_typedef/)
		{
			$typedef_count{$namespace.'::'.$defined_typedef}++;
		}
	}
}
close($fh);

my(%ignored);
open(my $ignore_fh, "<", $typedef_ignore_path) or die("Can't open: ".$typedef_ignore_path);
while (<$ignore_fh>)
{
	s/\r?\n//g;
	$ignored{$_} = 'x';
}
close($ignore_fh);

my($file_path_printed) = 0;
while (my($typedef, $count) = each(%typedef_count))
{
	if ($count <= 1 && $ignored{$typedef} ne 'x')
	{
		if (!$file_path_printed)
		{
			print "\n";
			print 'In '.$file_path.': '."\n";
			$file_path_printed = 1;
		}
		print '    WARNING: not used: '.$typedef."\n";
		$exit_status = 1;
	}
}

exit($exit_status);
