##
# Create syn-flood chain for detecting Denial of Service attacks
#
iptables -t nat -N syn-flood

##
# Limit 12 connections per second (burst to 24)
#
iptables -t nat -A syn-flood -m limit --limit 12/s --limit-burst 24 -j RETURN
iptables -t nat -A syn-flood -j DROP

##
# Check for DoS attack
#
iptables -t nat -A PREROUTING -i $EXT_IFACE -d $DEST_IP -p tcp --syn -j syn-flood


##
# Setup transparent Squid proxy for internal network
#
# For details on setting up Squid, see:
# http://www.linuxdoc.org/HOWTO/mini/TransparentProxy.html
#
iptables -t nat -A PREROUTING -i $INT_IFACE -p tcp --dport 80 -j REDIRECT --to-port 3128


##
# DROP XMAS & NULL TCP packets
#
iptables -t nat -A PREROUTING -p tcp --tcp-flags ALL ALL -j DROP
iptables -t nat -A PREROUTING -p tcp --tcp-flags ALL NONE -j DROP


##
# DROP inbound port scans
#
iptables -t nat -A PREROUTING -i $EXT_IFACE -d $DEST_IP -m psd -j DROP


##
# DROP packets from hosts with more than 16 active connections
#
iptables -t nat -A PREROUTING -i $EXT_IFACE -p tcp --syn -d $DEST_IP -m iplimit --iplimit-above 16 -j DROP


##
# DROP HTTP packets related to CodeRed and Nimda viruses silently
#
iptables -t filter -A INPUT -i $EXT_IFACE -p tcp -d $DEST_IP --dport http -m string --string "/default.ida?" -j DROP
iptables -t filter -A INPUT -i $EXT_IFACE -p tcp -d $DEST_IP --dport http -m string --string ".exe?/c+dir" -j DROP
iptables -t filter -A INPUT -i $EXT_IFACE -p tcp -d $DEST_IP --dport http -m string --string ".exe?/c+tftp" -j DROP


##
# Use DNAT to port forward http
#
iptables -t nat -A PREROUTING ! -i $INT_IFACE -p tcp --destination-port 80 -j DNAT --to 10.0.0.3:80


##
# Code Red filter for forwarder
#
iptables -t filter -A FORWARD -p tcp --dport http -m string --string "/default.ida?" -j DROP

