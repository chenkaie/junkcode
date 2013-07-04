#!/usr/bin/perl -w
#
#  Roll over and compress Apache log files, following Includes within the
#  httpd.conf (and all other configuration files).
#
#
use strict;
$|++;

my $server_root = "/usr/local/apache";
my $conf = "$server_root/conf/httpd.conf";
my $gid	= "wwwadmin";

my (%logs, %included, @files, @gzip);

my $date = `date +%Y%m%d`; chomp $date;

push @files, $conf;

for $conf (@files) {
  open(CONF, "<$conf") || die "Cannot open config file $conf: $!\n";

  while (<CONF>) {
    chomp;
    next if /^(\s+)?#/;

    if (/(Transfer|Custom|Error)Log\s+(\S+)(\s+)/i) {
	  $logs{$2}++;

    } elsif (/^(ResourceConfig|Include)\s+(\S+)/i) {
      if(!$included{$2}) {
        push @files, $2;
        $included{$2}++;
      }
    }
  }

  close CONF;
}

for my $logfile (sort keys %logs) {
  $logfile = "$server_root/$logfile" unless ($logfile =~ m|^/|);
  rename($logfile, "$logfile.$date");
  push(@gzip, "$logfile.$date");
}

system("$server_root/bin/apachectl restart");

for my $logfile (@gzip) {
  system("gzip $logfile");

  # Correctly set the ownerships so that selected folks can uncompress them.
  system("chgrp $gid $logfile.gz");
  system("chmod 664 $logfile.gz");
}



