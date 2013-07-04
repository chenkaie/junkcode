#!/usr/local/bin/perl
#
# Disk aging report generator
# Written by Seann Herdejurgen
#
# May 1998

use File::Find;

# Initialize variables
@levels=(30,60,90,180,365,9999);

# Check for verbose flag
if ($ARGV[0] eq "-v") {
   $verbose++;
   shift(@ARGV);
}

$ARGV[0]=$ENV{'PWD'} if ($ARGV[0] eq "");

foreach $dir (@ARGV) {
   foreach $level (@levels) {
       $modified{$level}=0;
       $accessed{$level}=0;
       $mfiles{$level}=0;
       $afiles{$level}=0;
   }
   print("\nDisk aging analysis for $dir:\n\n");
   print (" mod  acc   size file\n") if ($verbose);

   # Traverse desired filesystems
   find(\&wanted,$dir);

   print("                 last    num      last     num\n");
   print(" Age (days)    modified files    accessed files\n");
   $msize=$asize=$mtotal=$atotal=$lastlevel=0;

   foreach $level (@levels) {
       printf("%4d - %4d %8d Kb %5d %8d Kb %5d\n",$lastlevel,$level,$modified{$level}/1024,$mfiles{$level},$accessed{$level}/1024,$afiles{$level});
       $msize+=$modified{$level}/1024;
       $asize+=$accessed{$level}/1024;
       $mtotal+=$mfiles{$level};
       $atotal+=$afiles{$level};
       $lastlevel=$level+1;
   }

   printf("            ----------- ----- ----------- -----\n");
   printf("      Total %8d Kb %5d %8d Kb %5d\n",$msize,$mtotal,$asize,$atotal);
}

exit;

sub wanted {
    (($dev,$ino,$mode,$nlink,$uid,$gid,$rdev,$size) = lstat($_));
    $mod=int(-M _);
    $acc=int(-A _);
    foreach $level (@levels) {
       if ($mod<=$level) { $modified{$level}+=$size; $mfiles{$level}++; last; }
    }
    foreach $level (@levels) {
       if ($acc<=$level) { $accessed{$level}+=$size; $afiles{$level}++; last; }
    }
    printf("%4d %4d %6d %s\n",$mod,$acc,$size,$_) if ($verbose);
}
