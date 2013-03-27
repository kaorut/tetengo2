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
	if ($namespace =~ /^namespace:/)
	{
		next if $type ne 'typedef';
		next if $namespace =~ /__anon/;
		next if $namespace =~ /::detail::/;
		next if $namespace =~ /::detail$/;
	}
	else
	{
		next if $name =~ /~/;
		next if $type ne 'typedef';
		next if $namespace =~ /__anon/;
		next if $namespace =~ /::impl/;
		next if $namespace =~ /::detail::/;
		next if $namespace =~ /::detail$/;
		next if $access ne 'access:public' && $access ne 'access:protected' && $access ne 'access:friend';
	}
	
	print $name."\n";
}
