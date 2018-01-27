#!/usr/bin/perl
# Makes a function definition list.
# Copyright (C) 2007-2018 kaoru
# $Id$

use strict;
use File::Copy "copy";

my($ctags_command) = 'ctags -f - --language-force="C++" --file-scope=no --fields=+aK --C++-kinds=+p ';

if (scalar(@ARGV) < 1)
{
	print "Usage: zzz_make_function_list.pl input\n";
	exit(0);
}

my($file_name) = $ARGV[0];
$file_name =~ /(\.[a-zA-Z0-9]+)$/;
my($file_name_tmp) = $file_name.'.tmp'.$1;
`sed \"s/\\boverride\\b//\" < $file_name > $file_name_tmp`;

foreach my $output (`$ctags_command $file_name_tmp`)
{
	$output =~ s/\r?\n//g;
	next if $output =~ /^!/;
	
	my($name, $file, $description, $type, $namespace, $access) = split(/\t/, $output);
	if ($namespace =~ /^namespace:/)
	{
		next if $type ne 'function';
		next if $namespace =~ /__anon/;
		next if $namespace =~ /::detail::/;
		next if $namespace =~ /::detail$/;
	}
	else
	{
		next if $name =~ /~/;
		next if $type ne 'function';
		next if $namespace =~ /__anon/;
		next if $namespace =~ /::impl/;
		next if $namespace =~ /::detail::/;
		next if $namespace =~ /::detail$/;
		next if $access eq 'access:private' && $description !~ /\bvirtual\b/;
	}
	
	$namespace =~ s/^namespace://;
	$namespace =~ s/^class://;
	$namespace =~ s/^struct://;
	
	if ($description =~ /\bvirtual\b/)
	{
		$name =~ s/_impl$//;
	}
	
	print $namespace.'::'.$name."\n";
}

unlink($file_name_tmp);
