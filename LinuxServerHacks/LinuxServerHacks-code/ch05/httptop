#!/usr/bin/perl -w
#
# $Id: httptop,v 1.1 2002/06/27 00:25:39 rob Exp $

=head1 NAME 

httptop - display top(1)-like per-client HTTP access stats

=head1 SYNOPSIS

    httptop [-f <format>] [-r <refresh_secs>] [-b <backtrack_lines>] <logdir | path_to_log>

=cut

use Time::HiRes qw( time );
use File::Tail ();
use Term::ReadKey;
use Getopt::Std;

use strict;

### Defaults you might be interested in adjusting.

my $Update	= 2;	# update every n secs
my $Backtrack	= 250;	# backtrack n lines on startup
my @Paths	= qw(
    %
    /title/%/logs/access_log 
    /var/log/httpd/%/access_log
    /usr/local/apache/logs/%/access_log
);

my $Log_Format	    = "combined";
my %Log_Fields	    = (
    combined	=> [qw/ Host x x Time URI Response x Referer Client /],
    vhost	=> [qw/ VHost Host x x Time URI Response x Referer Client /]
);

### Constants & other thingies. Nothing to see here. Move along.

my $Version	    = "0.4.1";

sub by_hits_per ()  { $b->{Rate}  <=> $a->{Rate} }
sub by_total ()	    { $b->{Total} <=> $a->{Total} }
sub by_age ()	    { $a->{Last}   <=> $b->{Last} }

my $last_field	= "Client";
my $index	= "Host";
my $show_help	= 0;

my $order   = \&by_hits_per;
my $Help    = "htlwufd?q";
my %Keys    = (
    h	=> [ "Order by hits/second"	    => sub { $order = \&by_hits_per }	], 
    t	=> [ "Order by total recorded hits" => sub { $order = \&by_total }	],
    l	=> [ "Order by most recent hits"    => sub { $order = \&by_age }	],
    w	=> [ "Show remote host"		    => sub { $index = "Host" }		],
    u	=> [ "Show requested URI"	    => sub { $index = "URI" }		],
    f	=> [ "Show referring URL"	    => sub { $index = "Referer" }	],
    d	=> [ "Show referring domain"	    => sub { $index = "Domain" }	],
    '?'	=> [ "Help (this thing here)"	    => sub { $show_help++ }		],
    q	=> [ "Quit"			    => sub { exit }			]
);

my @Display_Fields  = qw/ Host Date URI Response Client Referer Domain /;
my @Record_Fields   = qw/ Host URI Referer Domain /;
my $Max_Index_Width = 50;
my $Initial_TTL	    = 50;

my @Months	    = qw/ Jan Feb Mar Apr May Jun Jul Aug Sep Nov Dec /;
my %Term	    = (
    HOME	=> "\033[H",
    CLS		=> "\033[2J",
    START_TITLE => "\033]0;", # for xterms etc.
    END_TITLE	=> "\007",
    START_RV	=> "\033[7m",
    END_RV	=> "\033[m"
);

my ( %hist, %opt, $spec );

$SIG{INT} = sub { exit };
END { ReadMode 0 };

### Subs.

sub refresh_output 
{
    my ( $cols, $rows ) = GetTerminalSize;
    my $show  = $rows - 3; 
    my $count = $show;
    my $now   = (shift || time);

    for my $type ( values %hist ) {
	for my $peer ( values %$type ) {
	    # if ( --$peer->{_Ttl} > 0 ) {
		my $delta = $now - $peer->{Start};
		if ( $delta >= 1 ) {
		    $peer->{ Rate } = $peer->{ Total } / $delta;
		} else {
		    $peer->{ Rate } = 0
		}

		$peer->{ Last } = int( $now - $peer->{ Date } );
	    # } else {
	    #	delete $type->{$peer}
	    # }
	}
    }

    $count = scalar( values %{$hist{$index}} ) - 1 if $show >= scalar values %{$hist{$index}};
    my @list = ( sort $order values %{$hist{$index}} )[ 0 .. $count ];

    my $first = 0;
    $first = ( $first <= $_ ? $_ + 1 : $first ) for  map { $_ ? length($_->{$index}) : 0 } @list;
    $first = $Max_Index_Width if $Max_Index_Width < $first;

    print $Term{START_TITLE}, "Monitoring $spec at: ", scalar localtime, $Term{END_TITLE} if $ENV{TERM} eq "xterm"; # UGLY!!!

    my $help = "Help/?";
    my $head = sprintf( "%-${first}s  %6s %4s %4s  %s (%d total)", 
	$index, qw{ Hits/s Tot Last }, $last_field, 
	scalar keys %{$hist{$index}}
    );

    #
    # Truncate status line if need be
    #
    $head = substr($head, 0, ($cols - length($help)));
    print @Term{"HOME", "START_RV"}, $head, " " x ($cols - length($head) - length($help)), $help, $Term{END_RV}, "\n";

    for ( @list ) {
	# $_->{_Ttl}++;

	my $line = sprintf( "%-${first}s  %6.3f %4d %3d  %s", 
	    substr( $_->{$index}, 0, $Max_Index_Width ), @$_{(qw{ Rate Total Last }, $last_field)} );
	if ( length($line) > $cols ) {
	    substr( $line, $cols - 1 ) = "";
	} else {
	    $line .= " " x ($cols - length($line));
	}
	print $line, "\n";
    }

    print " " x $cols, "\n" while $count++ < $show;
}	    

sub process_line
{
    my $line = shift;
    my $now = ( shift || time );
    my %hit;

    chomp $line;
    @hit{@{$Log_Fields{$Log_Format}}} = grep( $_, split( /"([^"]+)"|\[([^]]+)\]|\s/o, $line ) );

    $hit{ URI } =~ s/HTTP\/1\S+//gos;

    $hit{ Referer } = "<unknown>" if not $hit{Referer} or $hit{Referer} eq "-";
    ( $hit{Domain} = $hit{Referer} ) =~ s#^\w+://([^/]+).*$#$1#os;

    $hit{ Client } ||= "<none>";
    $hit{ Client } =~ s/Mozilla\/[\w.]+ \(compatible; /(/gos;
    $hit{ Client } =~ s/[^\x20-\x7f]//gos;

    # if $now is negative, try to guess how old the hit is based on the time stamp.
    if ( $now < 0 ) {
	my @hit_t = ( split( m![:/\s]!o, $hit{ Time } ))[ 0 .. 5 ];
	my @now_t = ( localtime )[ 3, 4, 5, 2, 1, 0 ];
	my @mag   = ( 3600, 60, 1 );

	# If the hit didn't parse right, or didn't happen today, the hell with it.
	return unless $hit_t[2] == ( $now_t[2] + 1900 )
	    and $hit_t[1] eq $Months[ $now_t[1] ]
	    and $hit_t[0] == $now_t[0];

	splice( @hit_t, 0, 3 ); 
	splice( @now_t, 0, 3 );

	# Work backward to the UNIX time of the hit.
	$now = time;
	$now -= (shift( @now_t ) - shift( @hit_t )) * $_ for ( 3600, 60, 1 );
    }

    $hit{ Date } = $now;

    for my $field ( @Record_Fields ) {
        my $peer = ( $hist{$field}{$hit{$field}} ||= { Start => $now, _Ttl => $Initial_TTL } );
	@$peer{ @Display_Fields } = @hit{ @Display_Fields };
	$peer->{ Total }++;
    }
}

sub display_help {
    my $msg = "httptop v.$Version";
    print @Term{qw/ HOME CLS START_RV /}, $msg, $Term{END_RV}, "\n\n";
    print " " x 4, $_, " " x 8, $Keys{$_}[0], "\n" for ( split "", $Help );
    print "\nPress any key to continue.\n";
}


### Init.

getopt( 'frb' => \%opt );

$Backtrack  = $opt{b} if $opt{b};
$Update	    = $opt{r} if $opt{r};
$Log_Format = $opt{f} if $opt{f};
$spec	    = $ARGV[0];

die <<End unless $spec and $Log_Fields{$Log_Format};
    Usage: $0 [-f <format>] [-r <refresh_secs>] [-b <backtrack_lines>] <logdir | path_to_log>
    Valid formats are: @{[ join ", ", keys %Log_Fields ]}.
End

for ( @Paths ) {
    last if -r $spec;
    ( $spec = $_ ) =~ s/%/$ARGV[0]/gos;
}
die "No access_log $ARGV[0] found.\n" unless -r $spec;

my $file = File::Tail->new( 
    name	=> $spec, 
    interval	=> $Update / 2, 
    maxinterval	=> $Update,
    tail	=> $Backtrack,
    nowait	=> 1
    ) or die "$spec: $!";

my $last_update = time;
my ( $line, $now );

# Backtracking.
while ( $Backtrack-- > 0 ) {
    last unless $line = $file->read;
    process_line( $line, -1 );
}
$file->nowait( 0 );

ReadMode 4;		    # Echo off.
print @Term{"HOME", "CLS"}; # Home & clear.
refresh_output;

### Main loop.

while (defined( $line = $file->read )) {
    $now = time;

    process_line( $line, $now );

    while ( $line = lc ReadKey(-1) ) {
	$show_help = 0 if $show_help;
	$Keys{$line}[1]->() if $Keys{$line};
    }

    if ( $show_help == 1 ) {
	display_help;
	$show_help++; # Don't display help again.
    } elsif ( $now - $last_update > $Update and not $show_help ) {
	$last_update = $now;
	refresh_output( $now );	
    }
}

__END__

=head1 DESCRIPTION

httptop is intended to be a top(1)-equivalent for httpd access activity.
    
httptop should be invoked with the path to an Apache access_log, or alternately a string that uniquely identifies the directory in which to find the access_log. The search paths can be configured in the source. 

httptop has limited flexibility for dealing with logs of different formats. Run 'httptop' without options to see which format names are available.

While httptop is running, you can obtain a list of terminal commands by pressing '?'. As with top(1), pressing 'q' quits.

=head1 BUGS and other MISCELLANY

httptop doesn't even try to read httpd.conf to figure out where the log files are, or what format they're in, so it's not very robust.

Settings like refresh, backtracking, and log paths should be more easily configurable.

httptop should give cumulative access stats for the whole log, like uptime(1).

=head1 AUTHOR

Schuyler Erle (schuyler@oreilly.com), with suggestions (and minor additions) from Rob Flickenger and Peter Wiggin.

=head1 LICENSE

The software is available under the same terms as perl itself. Patches welcome.

=head1 PREREQUISITES

File::Tail(3), Time::HiRes(3), Term::ReadKey(3)

=head1 SEE ALSO

perl(1), top(1), httpd(8)

=cut
