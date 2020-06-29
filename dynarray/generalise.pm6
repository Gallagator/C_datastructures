#!/usr/bin/perl


my $file = <STDIN>;
chomp $file;
open(my $in, '<', $file) || die;

while(my $line = <$in>)
{
    print "$line";
}

