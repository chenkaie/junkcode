#include <netpacket/packet.h>
#include <net/ethernet.h>     /* the L2 protocols */
#include <net/if.h>
#include <sys/ioctl.h>
#include <errno.h>

typedef int SOCKET;

int main(int argc, char **argv)
{
	SOCKET sd;
	struct sockaddr_ll TAddr_sll;
	struct ifreq ifr;
	int iSendNum;
	char *interface;

	unsigned char acSendBuf[42]={ // Ethernet + RARP
		0xff,0xff,0xff,0xff,0xff,0xff,	// eth.dest
		0x00,0xc0,0xf6,0xb3,0x9c,0x74,	// eth.src(172.16.7.61)
		0x80,0x35,	// eth.type
		0x00,0x01,// RARP HW type
		0x08,0x00,// RARP PT type
		0x06,// RARP HW size
		0x04,// RARP PT size
		0x00,0x03,// opcode
		0x00,0xc0,0xf6,0xb3,0x9c,0x74,// RARP sender MAC(172.16.7.61)
		0x00,0x00,0x00,0x0,// RARP sender IP
		0x00,0xc0,0xf6,0xb3,0x9c,0x74,// RARP target MAC(172.16.7.61)
		0x00,0x00,0x00,0x00// RARP target IP
	};

	interface = argv[1];

	if ((sd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP))) < 0 )
	{
		printf("Failed socket()\nErrorNum = %d\n", errno);
		return -1;
	}

	bzero(&TAddr_sll, sizeof(TAddr_sll));
	bzero(&ifr, sizeof(ifr));

	/*  First Get the Interface Index  */

	strncpy((char *)ifr.ifr_name, interface, IFNAMSIZ);

	if ((ioctl(sd, SIOCGIFINDEX, &ifr)) == -1)
	{
		printf("Error getting Interface index !\n");
		return -1;
	}

	TAddr_sll.sll_family = AF_PACKET;
	TAddr_sll.sll_ifindex = ifr.ifr_ifindex;
	TAddr_sll.sll_protocol = htons(ETH_P_ARP); 

	if(iSendNum = sendto(sd, acSendBuf, sizeof(acSendBuf), 0, (struct sockaddr *)&TAddr_sll, sizeof(TAddr_sll)) != sizeof(acSendBuf))
	{
		printf("Could only send %d bytes of packet of length %d, errno=%d\n", iSendNum, sizeof(acSendBuf), errno);
		return -1;
	}

	if (iSendNum < 0)
	{
		printf("Failed sendto()\nErrorNum = %d\n", errno);
		return -1;
	}

	close(sd);
	sd = -1;
	return 0;
}
