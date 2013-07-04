#!/usr/bin/perl -w 
use strict;

my %ads; 

# define each of your QUERY_STRINGS, 
# and the matching "real name" here. 
# this script will only look for 
# QUERY_STRINGS that are letters and 
# numbers only (no dashes, etc.) 
$ads{"xml"} = "XML.com"; 
$ads{"nyt"} = "New York Times"; 
$ads{"ora"} = "O'Reilly and Associates"; 

# your Apache access log location. 
my $logfile = "/var/log/httpd/access_log"; 

# define some counters. 
my %ads_count; my $total; 

# open the logfile. 
open(LOG, "<$logfile") or die $!; 

# and loop through each line. 
while (<LOG>) { 
  # skip over lines we're not interested in. 
 next unless /GET/; next unless /\?(\w+)\s/; 
  #  save the query_string. 
  my $query_string = $1; 
  # move on if not defined, else increment. 
  next unless exists $ads{$query_string}; 
  $total++; $ads_count{$query_string}++; 
} 

# and print out the data. 
print "There were a total of $total ad referrals.\n"; 
foreach ( sort keys %ads_count ) { 
  print "$ads{$_} had $ads_count{$_} ad referrals.\n"; 
} 

# close logfile and 
# exit the program. 
close(LOG); exit;
