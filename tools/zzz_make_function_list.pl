#!/usr/bin/perl
# Makes a function definition list.
# Copyright (C) 2007-2013 kaoru
# $Id$

use strict;

my($ctags_command) = 'ctags -f - --language-force="C++" --file-scope=no --fields=+aK ';

if (scalar(@ARGV) < 1)
{
	print "Usage: zzz_make_function_list.pl input\n";
	exit(0);
}

my($file_name) = $ARGV[0];

foreach my $output (`$ctags_command $file_name`)
{
	$output =~ s/\r?\n//g;
	next if $output =~ /^!/;
	
	my($name, $file, $description, $type, $namespace, $access) = split(/\t/, $output);
	next if $name =~ /~/;
	next if $type ne 'function';
	next if $namespace =~ /::__anon/;
	next if $namespace =~ /::impl/;
	next if $namespace =~ /::detail::/;
	next if $access ne 'access:public' && $access ne 'access:protected';
	
	$namespace =~ s/^class://;
	$namespace =~ s/^struct://;
	print $namespace.'::'.$name."\n";
}
