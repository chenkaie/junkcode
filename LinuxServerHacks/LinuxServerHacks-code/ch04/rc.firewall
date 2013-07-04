#
# A simple firewall initialization script
#
WHITELIST=/usr/local/etc/whitelist.txt
BLACKLIST=/usr/local/etc/blacklist.txt
ALLOWED="22 25 80 443"

#
# Drop all existing filter rules
#
iptables -F

#
# First, run through $WHITELIST, accepting all traffic from the hosts and networks
# contained therein.
#
for x in `grep -v ^# $WHITELIST | awk '{print $1}'`; do 
  echo "Permitting $x..."
  iptables -A INPUT -t filter -s $x -j ACCEPT
done

#
# Now run through $BLACKLIST, dropping all traffic from the hosts and networks
# contained therein.
#
for x in `grep -v ^# $BLACKLIST | awk '{print $1}'`; do 
  echo "Blocking $x..."
  iptables -A INPUT -t filter -s $x -j DROP
done

#
# Next, the permitted ports:  What will we accept from hosts not appearing 
# on the blacklist?
#
for port in $ALLOWED; do 
  echo "Accepting port $port..."
  iptables -A INPUT -t filter -p tcp --dport $port -j ACCEPT
done

#
# Finally, unless it's mentioned above, and it's an inbound startup request,
# just drop it.
#
iptables -A INPUT -t filter -p tcp --syn -j DROP
