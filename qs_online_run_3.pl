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


open(FILE, "data.txt") or die("Unable to open file");

my @data = <FILE>;

foreach my $line1 (@data)
{
    my $filename_write = 'prime_1';
   open(my $fh_1, '>', $filename_write) or die "Could not open file '$filename_write' $!";
    print $fh_1 "$line1\n";
   close $fh_1;


    foreach my $line2 (@data)
    {
        if ($line1 == $line2)
        {
            next;
        }
        #print "$line1   $line2 \n";
    my $filename_write = 'prime_2';
   open(my $fh_1, '>', $filename_write) or die "Could not open file '$filename_write' $!";
    print $fh_1 "$line2\n";
   close $fh_1;

    #system("./tests/qs_unit_matrix_big_online_test.out");
   system("./tests/qs_unit_matrix_big_standart_test.out");

    }


}

close(FILE);

