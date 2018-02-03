#! /usr/bin/perl
use strict;
use warnings;
 

my $filename = 'data.txt';
open(my $fh, '<:encoding(UTF-8)', $filename)
    or die "Could not open file '$filename' $!";
 
while (my $row = <$fh>) {
    chomp $row;
    print "$row\n";

    my $filename_write = 'prime_2';
   open(my $fh_1, '>', $filename_write) or die "Could not open file '$filename_write' $!";
    print $fh_1 "$row\n";
   close $fh_1;

    #system("./tests/qs_unit_matrix_big_online_test.out");
   system("./tests/qs_unit_matrix_big_standart_test.out");
}
close $fh;


