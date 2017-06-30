#!/usr/bin/perl

use strict;
use warnings;
use 5.012;

my $rawTime   = time();
my @localTime = localtime($rawTime);

my $hour   = $localTime[2];
my $minute = $localTime[1];

my $str_hour   = sprintf("%02d" , $hour);
my $str_minute = sprintf("%02d" , $minute);

print "$str_hour:$str_minute\n\n";

my $imagesDirectory = "/home/pi/Big_Ben/images";
my $executable      = "/home/pi/Big_Ben/bin/showtime";
my $bigBenPath      = "/home/pi/Big_Ben/special_images/bigben1.jpg";
my @namesList;
opendir(my $dirHandle , $imagesDirectory);
while(readdir $dirHandle)
{
	if ($_ ne "." && $_ ne "..")
	{
		push @namesList , $_;
	}
}
closedir $dirHandle;

my $index = int(rand(scalar(@namesList)));
print "$index : $imagesDirectory/$namesList[$index]\n";
my $command;
if ($minute == 0 || $minute == 30)
{
	$command = "$executable $bigBenPath                         $str_hour $str_minute";
}else{
	$command = "$executable $imagesDirectory/$namesList[$index] $str_hour $str_minute";
}
print "$command\n";
`$command`;
print "Finished\n";
