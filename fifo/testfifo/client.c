#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("Usage: %s fifo_path message\n", argv[0]);
		return -1;
	}

	int ifd;

	if ( ( ifd = open(argv[1], O_WRONLY|O_NONBLOCK )) < 0 )
	{
		printf("Failed to open fifo! %m\n");
		return -1;
	}

	int iLen;

	iLen = strlen(argv[2]);

	printf("Write %s (%d bytes)\n", argv[2], iLen);

	write(ifd, argv[2], iLen);

    while(1)
    {
        sleep(1);
    }

	close(ifd);
    printf("%m\n");

	return 0;
}
