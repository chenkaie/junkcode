#!/usr/bin/perl -w

use strict;
$|++;

my $host=`/bin/hostname`;
chomp $host;

while(1) {

  open(LOAD,"/proc/loadavg") || die "Couldn't open /proc/loadavg: $!\n";

  my @load=split(/ /,<LOAD>);
  close(LOAD);

  print "\033]0;";
  print "$host: $load[0] $load[1] $load[2] at ", scalar(localtime);
  print "\007";

  sleep 2;
}

