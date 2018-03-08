#! /usr/bin/perl
use strict;
use warnings;
 

#my $filename = 'data.txt';
#open(my $fh, '<:encoding(UTF-8)', $filename)
#    or die "Could not open file '$filename' $!";
 
#while (my $row = <$fh>) {
#    chomp $row;
#    print "$row\n";

#    my $filename_write = 'prime_2';
#   open(my $fh_1, '>', $filename_write) or die "Could not open file '$filename_write' $!";
#    print $fh_1 "$row\n";
#   close $fh_1;
#
    #system("./tests/qs_unit_matrix_big_online_test.out");
#   system("./tests/qs_unit_matrix_big_standart_test.out");
#}
#close $fh;


open(FILE1, "results_0.txt") or die("Unable to open file");

my @data_1 = <FILE1>;

close(FILE1);

open(FILE2, "results_1.txt") or die("Unable to open file");

my @data_2 = <FILE2>;

close(FILE2);

my $e1;
my $e2;
foreach $e1 (@data_1)
{
    my $filename_write = 'prime_1';
   open(my $fh_1, '>', $filename_write) or die "Could not open file '$filename_write' $!";
    print $fh_1 "$e1\n";
   close $fh_1;

   foreach $e2 (@data_2) {
       my $filename_write = 'prime_2';
       open(my $fh_2, '>', $filename_write) or die "Could not open file '$filename_write' $!";
       print $fh_2 "$e2\n";
       close $fh_2;

       print  "$e1 $e2";
       system("./tests/qs_unit_matrix_big_standart_test.out");
       #system("./tests/qs_unit_matrix_big_online_test.out");
   }



}

