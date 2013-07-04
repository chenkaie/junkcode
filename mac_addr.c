#include <stdio.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <net/ethernet.h>

#define ETH_ABUFLEN ((ETH_ALEN*2)+1)

void mac_addr(const char* name, unsigned char MAC_str[ETH_ABUFLEN])
{
	int s,i;
	struct ifreq ifr;
	MAC_str[0]='\0';
	if ((s=socket(AF_INET, SOCK_DGRAM, 0)) != -1) {
		strcpy(ifr.ifr_name, name);
		if (ioctl(s, SIOCGIFHWADDR, &ifr) != -1) {
			for (i=0; i<ETH_ALEN; i++)
				sprintf(&MAC_str[i*2],"%02X",((unsigned char*)ifr.ifr_hwaddr.sa_data)[i]);
		}
		close(s);
	}
	MAC_str[ETH_ABUFLEN-1]='\0';
}

unsigned char eth0_MAC_address[ETH_ABUFLEN];

int main(void) {
	mac_addr("eth0",eth0_MAC_address);
	puts(eth0_MAC_address);
}
