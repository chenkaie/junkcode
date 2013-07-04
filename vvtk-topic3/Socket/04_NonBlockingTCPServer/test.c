#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/select.h>

/* The source code is almost the same with the code in Unix Network Programming Vol1 page 411 */

int connect_time (int sock, struct sockaddr *addr, int size_addr, int timeout)
{
    int error = 0;
    int flags;
    fd_set  rset, wset;
    int     n;

    struct timeval tval;

    flags = fcntl (sock, F_GETFL, 0);
    fcntl (sock, F_SETFL, flags | O_NONBLOCK);      // set the socket as nonblocking IO

    if ((n = connect (sock, addr, size_addr)) < 0) {        // we connect, but it will return soon
        if (errno != EINPROGRESS) {

            perror ("Suck Connect");
            return -1;
        }
    }

    if (n == 0)
        goto done;

    FD_ZERO (&rset);
    FD_ZERO (&wset);
    FD_SET (sock, &rset);
    FD_SET (sock, &wset);
    tval.tv_sec = timeout;

    tval.tv_usec = 0;

    /* We "select()" until connect() returns its result or timeout */
    if ( (n = select(sock+1, &rset, &wset, NULL, timeout ? &tval : NULL)) == 0) {   

        close (sock);
        printf ("Connect Timeout\n");
        errno = ETIMEDOUT;
        return -1;
    }
    if (FD_ISSET(sock, &rset) || FD_ISSET(sock, &wset)) 
    {
        int len = sizeof(error);
        if (getsockopt (sock, SOL_SOCKET, SO_ERROR, &error, &len) < 0) {
            perror ("getsockopt");
            return -1;
        }
    }
    else 
    {
        printf ("Strange bug\n");
        return -1;
    }

done:


    /* We change the socket options back to blocking IO */
    fcntl (sock, F_SETFL, flags);
    if (errno) 
    {
        printf ("Connect failed\n");
        close (sock);
        return -1;
    }
    printf ("Connect success\n");
    return 0;
}

int main(int argc, char **argv)
{

    struct sockaddr_in  srvaddr;
    int sock;
    int r;

    bzero (&srvaddr, sizeof(srvaddr));
    srvaddr.sin_family = AF_INET;
    srvaddr.sin_port = atoi (argv[2]);
    inet_aton (argv[1], &srvaddr.sin_addr);

    sock = socket (AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        printf ("Suck sock\n");
        return 1;
    }
    r = connect_time (sock, (struct sockaddr*)&srvaddr, sizeof(srvaddr), atoi(argv[3]));
    exit(0);
}   

