#!/usr/bin/perl
# Checks the test cases.
# Copyright (C) 2007-2019 kaoru
# $Id$

use strict;

if (scalar(@ARGV) < 3)
{
	print "Usage: zzz_check_test_cases.pl functions.txt test_cases.txt ignore.txt\n";
	exit(0);
}

my($exit_status) = 0;

# main
{
	my(%functions);
	read_file($ARGV[0], \%functions);
	my(%test_cases);
	read_file($ARGV[1], \%test_cases);
	my(%ignored);
	read_ignore_file($ARGV[2], \%ignored);
	
	foreach my $function (sort(keys(%functions)))
	{
		next if check_ignored(\%ignored, $function);
		
		my($expected_test_case) = to_expected_test_case($function);
		
		if ($test_cases{$expected_test_case} eq 'x')
		{
			$test_cases{$expected_test_case} = 'y'
		}
		else
		{
			print "WARNING: No test case for function:\n";
			print '  '.$function."\n";
			print '  -> '.$expected_test_case."\n";
			$exit_status = 1;
		}
	}
	
	foreach my $test_case (sort(keys(%test_cases)))
	{
		next if check_ignored(\%ignored, $test_case);
		
		if ($test_cases{$test_case} eq 'x')
		{
			print "WARNING: No function for test case:\n";
			print '  '.$test_case."\n";
			$exit_status = 1;
		}
	}
	
	foreach my $ig (sort(keys(%ignored)))
	{
		if ($ignored{$ig} eq 'x')
		{
			print "WARNING: Remove from the ignore file:\n";
			print '  '.$ig."\n";
			$exit_status = 1;
		}
	}
	
	exit($exit_status);
}

sub read_file
{
	my($file_name, $r_result) = @_;
	
	open(my $fh, "<", $file_name) or die("Can't open: ".$file_name);
	while (<$fh>)
	{
		s/\r?\n//g;
		$$r_result{$_} = 'x';
	}
	close($fh);
}

sub read_ignore_file
{
	my($file_name, $r_result) = @_;
	
	open(my $fh, "<", $file_name) or die("Can't open: ".$file_name);
	while (<$fh>)
	{
		s/\r?\n//g;
		next if $_ eq '';
		
		$$r_result{$_} = 'x';
	}
	close($fh);
}

sub check_ignored
{
	my($r_ignored, $name) = @_;
	
	for my $ig (keys(%$r_ignored))
	{
		if ($name =~ /$ig/)
		{
			$$r_ignored{$ig} = 'y';
			return 1;
		}
	}
	return 0;
}

sub to_expected_test_case
{
	my($function) = @_;
	my(@felems) = split(/::/, $function);
	my($felem_count) = scalar(@felems);
	
	my($test_case) = 'test_'.$function;
	if ($felem_count >= 2 && $felems[$felem_count - 1] eq $felems[$felem_count - 2])
	{
		$test_case =~ s/::[a-zA-Z0-9_]+$/::construction/;
	}
	if ($felems[$felem_count - 1] =~ /^operator ([^:]+)$/)
	{
		if    ($1 eq '()')
		{
			$test_case =~ s/::operator [^:]+$/::operator_paren/;
		}
		elsif ($1 eq '==')
		{
			$test_case =~ s/::operator [^:]+$/::operator_equal/;
		}
		elsif ($1 eq '!=')
		{
			$test_case =~ s/::operator [^:]+$/::operator_not_equal/;
		}
		elsif ($1 eq '<')
		{
			$test_case =~ s/::operator [^:]+$/::operator_less_than/;
		}
		elsif ($1 eq '>')
		{
			$test_case =~ s/::operator [^:]+$/::operator_greater_than/;
		}
		elsif ($1 eq '=')
		{
			$test_case =~ s/::operator [^:]+$/::operator_assign/;
		}
		elsif ($1 eq '+')
		{
			$test_case =~ s/::operator [^:]+$/::operator_plus/;
		}
		elsif ($1 eq '-')
		{
			$test_case =~ s/::operator [^:]+$/::operator_minus/;
		}
		elsif ($1 eq '*')
		{
			$test_case =~ s/::operator [^:]+$/::operator_multiply/;
		}
		elsif ($1 eq '/')
		{
			$test_case =~ s/::operator [^:]+$/::operator_divide/;
		}
		elsif ($1 eq '+=')
		{
			$test_case =~ s/::operator [^:]+$/::operator_plus_assign/;
		}
		elsif ($1 eq '-=')
		{
			$test_case =~ s/::operator [^:]+$/::operator_minus_assign/;
		}
		elsif ($1 eq '*=')
		{
			$test_case =~ s/::operator [^:]+$/::operator_multiply_assign/;
		}
		elsif ($1 eq '/=')
		{
			$test_case =~ s/::operator [^:]+$/::operator_divide_assign/;
		}
		elsif ($1 eq '++')
		{
			$test_case =~ s/::operator [^:]+$/::operator_increment/;
		}
		elsif ($1 eq '->')
		{
			$test_case =~ s/::operator [^:]+$/::operator_arrow/;
		}
		elsif ($1 =~ /[a-zA-Z0-9_]+/)
		{
			$test_case =~ s/::operator ([^:]+)$/::operator_$1/;
		}
	}
	
	return $test_case;
}
