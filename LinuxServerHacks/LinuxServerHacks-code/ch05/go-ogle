#!/usr/bin/perl
use Socket;
$|++;

open(NG,"ngrep -d en1 -lqi '(GET|POST).*/(search|find)' |");
print "Go ogle online.\n";
my ($go,$i) = 0;
my %host = ( );

while(<NG>) {

  if(/^T (\d+\.\d+.\d+\.\d+):\d+ -> (\d+\.\d+\.\d+\.\d+):80/) {
    $i = inet_aton($1);
    $host{$1} ||= gethostbyaddr($i, AF_INET) || $1;
    $i = inet_aton($2);
    $host{$2} ||= gethostbyaddr($i, AF_INET) || $2;
    print "$host{$1} -> $host{$2} : ";
    $go = 1;
    next;   
  }
  if(/(q|p|query|for)=(.*)?(&|HTTP)/) {
    next unless $go;
    my $q = $2;
    $q =~ s/(\+|&.*)/ /g;
    $q =~ s/%(\w+)/chr(hex($1))/ge;
    print "$q\n";
    $go = 0;
  }
  if(/^$/) {
    next unless $go;
    $go = 0;
    print "\n";
  }
}
