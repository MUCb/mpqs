#!/usr/bin/perl -w
use strict;

my $p = 169;
my $t;
my $t2 = 87;

my $i = 1;
while($i)
{
	$t = sqrt($t2);
		print "t = $t\n";
	if($t =~ s/\.//g)
	{
		print "t = $t\n";
		$t2 += $p;
	}
	else{
		$i = 0;
	}
	print "t2 = $t2\n";
	# exit(0);
}