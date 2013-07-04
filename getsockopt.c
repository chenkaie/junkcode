#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <errno.h>
#include <stdio.h>

int main()
{
   int socketHandle;

   // create socket

   if((socketHandle = socket(AF_INET, SOCK_STREAM, IPPROTO_IP)) < 0)
   {
      close(socketHandle);
      perror("socket");
   }

    int iSocketOption = 0;
    int iSocketOptionLen = sizeof(int);;

    struct linger SocketOptionLinger;
    int iSocketOptionLingerLen = sizeof(struct linger);;

    getsockopt(socketHandle, IPPROTO_TCP, TCP_NODELAY, (char *)&iSocketOption, &iSocketOptionLen);
    printf("Socket TCP_NODELAY = %d\n", iSocketOption);

    getsockopt(socketHandle, IPPROTO_TCP, TCP_MAXSEG, (char *)&iSocketOption, &iSocketOptionLen);
    printf("Socket TCP_MAXSEG = %d\n", iSocketOption);

    getsockopt(socketHandle, IPPROTO_TCP, TCP_CORK, (char *)&iSocketOption, &iSocketOptionLen);
    printf("Socket TCP_CORK = %d\n", iSocketOption);

    getsockopt(socketHandle, IPPROTO_TCP, TCP_KEEPIDLE, (char *)&iSocketOption, &iSocketOptionLen);
    printf("Socket TCP_KEEPIDLE = %d\n", iSocketOption);

	int optval = 5;
	int optlen = sizeof(optval);
	if(setsockopt(socketHandle, IPPROTO_TCP, TCP_KEEPIDLE, &optval, optlen) < 0) {
		perror("setsockopt()");
		close(socketHandle);
		exit(1);
	}

    getsockopt(socketHandle, IPPROTO_TCP, TCP_KEEPIDLE, (char *)&iSocketOption, &iSocketOptionLen);
    printf("Socket TCP_KEEPIDLE = %d\n", iSocketOption);

    getsockopt(socketHandle, IPPROTO_TCP, TCP_KEEPINTVL, (char *)&iSocketOption, &iSocketOptionLen);
    printf("Socket TCP_KEEPINTVL = %d\n", iSocketOption);

	optval = 3;
	optlen = sizeof(optval);
	if(setsockopt(socketHandle, IPPROTO_TCP, TCP_KEEPINTVL, &optval, optlen) < 0) {
		perror("setsockopt()");
		close(socketHandle);
		exit(1);
	}

    getsockopt(socketHandle, IPPROTO_TCP, TCP_KEEPINTVL, (char *)&iSocketOption, &iSocketOptionLen);
    printf("Socket TCP_KEEPINTVL = %d\n", iSocketOption);

    getsockopt(socketHandle, IPPROTO_TCP, TCP_KEEPCNT, (char *)&iSocketOption, &iSocketOptionLen);
    printf("Socket TCP_KEEPCNT = %d\n", iSocketOption);
	optval = 3;
	optlen = sizeof(optval);
	if(setsockopt(socketHandle, IPPROTO_TCP, TCP_KEEPCNT, &optval, optlen) < 0) {
		perror("setsockopt()");
		close(socketHandle);
		exit(1);
	}


    getsockopt(socketHandle, IPPROTO_TCP, TCP_KEEPCNT, (char *)&iSocketOption, &iSocketOptionLen);
    printf("Socket TCP_KEEPCNT = %d\n", iSocketOption);

    getsockopt(socketHandle, IPPROTO_TCP, TCP_SYNCNT, (char *)&iSocketOption, &iSocketOptionLen);
    printf("Socket TCP_SYNCNT = %d\n", iSocketOption);

    getsockopt(socketHandle, IPPROTO_TCP, TCP_LINGER2, (char *)&iSocketOption, &iSocketOptionLen);
    printf("Socket TCP_LINGER2 = %d\n", iSocketOption);

    getsockopt(socketHandle, SOL_SOCKET, SO_REUSEADDR, (char *)&iSocketOption, &iSocketOptionLen);
    printf("Socket SO_REUSEADDR = %d\n", iSocketOption);

    getsockopt(socketHandle, SOL_SOCKET, SO_ERROR, (char *)&iSocketOption, &iSocketOptionLen);
    printf("Socket SO_ERROR = %d\n", iSocketOption);

    getsockopt(socketHandle, SOL_SOCKET, SO_BROADCAST, (char *)&iSocketOption, &iSocketOptionLen);
    printf("Socket SO_BROADCAST = %d\n", iSocketOption);

    getsockopt(socketHandle, SOL_SOCKET, SO_KEEPALIVE, (char *)&iSocketOption, &iSocketOptionLen);
    printf("Socket SO_KEEPALIVE = %d\n", iSocketOption);

    getsockopt(socketHandle, SOL_SOCKET, SO_SNDBUF, (char *)&iSocketOption, &iSocketOptionLen);
    printf("Socket SO_SNDBUF = %d\n", iSocketOption);

    getsockopt(socketHandle, SOL_SOCKET, SO_RCVBUF, (char *)&iSocketOption, &iSocketOptionLen);
    printf("Socket SO_RCVBUF = %d\n", iSocketOption);

    getsockopt(socketHandle, SOL_SOCKET, SO_LINGER, (char *)&SocketOptionLinger, &iSocketOptionLingerLen);
    printf("Socket SO_LINGER = %d  time = %d\n", SocketOptionLinger.l_onoff, SocketOptionLinger.l_linger);

    getsockopt(socketHandle, SOL_SOCKET, SO_RCVLOWAT, (char *)&iSocketOption, &iSocketOptionLen);
    printf("Socket SO_RCVLOWAT = %d\n", iSocketOption);
}
          
