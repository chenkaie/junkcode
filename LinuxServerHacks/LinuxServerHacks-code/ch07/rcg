#!/usr/bin/perl -w

=head1 NAME

rcg - Look at the world through Regex Colored Glasses

=head1 SYNOPSIS

	rcg sudo: RED < /var/log/messages

	tail /var/log/syslog | rcg '\d\d:\d\d:\d\d' "BOLD . BLUE" 

=head1 DESCRIPTION

rcg is a simple filter that uses Term::ANSIColor to colorize arbitrary
regexs, specified on the commandline.  It is intended to help visually slog
through log files.

You must pass 'rcg' an even number of commandline parameters.  The odd terms
specify the regex, the even terms specify the color.

=head1 EXAMPLES

Suppose you wanted anything with the word 'sendmail' in your messages log to
show up magenta, instead of grey:

	rcg sendmail MAGENTA < /var/log/messages | less -r

The 'less -r' is optional, but handy if you have less(1) installed.

You can use any arbitrary regex as an odd term:

	rcg '\d+\.\d+\.\d+\.\d+' GREEN < /var/log/maillog

Or chain colors together:

	tail -50 /var/log/messages | rcg WARNING "BOLD . YELLOW . ON_RED" 

Or specify any number of regex / color code pairs on a single commandline. 
This is where teeny shell scripts would come in handy (one for messages, one
for firewall logs, one for apache...)
 
See the Term::ANSIColor docs for the full list of colors and combinations.

Some other useful strings:

    '\w+=\S+'				variables, like TERM=xyz
    '\d+\.\d+\.\d+\.\d+'		probably an IP address
    '^(J|F|M|A|S|O|N|D)\w\w (\d| )\d'	might be a date
    '\d\d:\d\d:\d\d'			possibly the time
    '.*last message repeated.*'		make this "BOLD . WHITE"


Use your imagination.

=head1 PREREQUISITES

Term::ANSIColor

less -R (or even -r) is nice...

=head1 BUGS

=over 4

=item * Color params are just eval()'d.  You have been warned.

=item * Colorization is applied in arbitrary order, so it's not possible to
guarantee the behavior of overlapping regex's...

=back

=head1 AUTHOR

A particularly demented Rob Flickenger <rob@oreillynet.com> on a late
evening.  Use at your own risk!  Demand a refund!  See where it gets you!

=head1 SEE ALSO

regex(7).  No, don't look at that.  Look at Camel3 or Mastering Regular
Expressions in Perl...

=cut

use strict;
use Term::ANSIColor qw(:constants);

my %target = ( );

while (my $arg = shift) {
  my $clr = shift;

  if(($arg =~ /^-/) | (!$clr)) {
    print "Usage: rcg [regex] [color] [regex] [color] ...\n";
    exit;
  }

  #
  # Ugly, lazy, pathetic hack here
  #
  $target{$arg} = eval($clr);
}

my $rst = RESET;

while(<>) {
  foreach my $x (keys(%target)) {
    s/($x)/$target{$x}$1$rst/g;
  }
  print;
}
