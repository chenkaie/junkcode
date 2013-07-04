#!/usr/bin/env python
"USAGE: nslookup.py <inet_address>"
import socket, sys
print socket.gethostbyname(sys.argv[1])
