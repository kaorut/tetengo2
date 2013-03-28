#!/usr/bin/perl
# Lists typedefs.
# Copyright (C) 2007-2013 kaoru
# $Id$

use strict;

my($ctags_command) = 'ctags -f - --language-force="C++" --file-scope=no --fields=+aK ';

if (scalar(@ARGV) < 1)
{
	print "Usage: zzz_list_typedefs.pl input\n";
	exit(0);
}

my($file_name) = $ARGV[0];

foreach my $output (`$ctags_command $file_name`)
{
	$output =~ s/\r?\n//g;
	next if $output =~ /^!/;
	
	my($name, $file, $description, $type, $namespace, $access) = split(/\t/, $output);
	next if $type ne 'typedef';
	next if $namespace =~ /_traits$/;
	
	$namespace =~ s/^namespace://;
	$namespace =~ s/^class://;
	$namespace =~ s/^struct://;
	print $namespace."\t".$name."\n";
}
