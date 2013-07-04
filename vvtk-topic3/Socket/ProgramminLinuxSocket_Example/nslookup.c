/* Bare nslookup utility (w/ minimal error checking) */
#include <stdio.h> /* stderr, stdout */
#include <netdb.h> /* hostent struct, gethostbyname() */
#include <arpa/inet.h> /* inet_ntoa() to format IP address */
#include <netinet/in.h> /* in_addr structure */
int main(int argc, char **argv) 
{
    struct hostent *host; /* host information */
    struct in_addr h_addr; /* Internet address */
    if (argc != 2) 
    {
        fprintf(stderr, "USAGE: nslookup <inet_address>\n");
        exit(1);
    }
    
    if ((host = gethostbyname(argv[1])) == NULL) 
    {
        fprintf(stderr, "(mini) nslookup failed on '%s'\n", argv[1]);
        exit(1);
    }
    
    h_addr.s_addr = *((unsigned long *) host->h_addr_list[0]);
    fprintf(stdout, "%s\n", inet_ntoa(h_addr));
    exit(0);
}
