#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("Usage: %s fifo_name read_bytes\n", argv[0]);
		return -1;
	}

	int iRet;
	iRet = mkfifo(argv[1], 0777);

	if (iRet != 0)
	{
		printf("Create fifo failed! %m\n");
		//return -1;
	}

	int ifd = open(argv[1], O_RDONLY | O_NONBLOCK);
	open(argv[1], O_WRONLY);

	if (ifd < 0)
	{
		printf("Open fifo failed! %m");
		return -1;
	}

	struct timeval  tTime;
	fd_set 			readset;
	int 			iSelect, iRdSz;
	char 			szCmd[1024];

	memset(szCmd, 0, 1024);

	while (1)
	{
		tTime.tv_sec = 5;
		tTime.tv_usec = 0;

		FD_ZERO(&readset);
		FD_SET(ifd, &readset);

		iSelect = select(ifd + 1, &readset, NULL, NULL, &tTime);

		if (iSelect > 0)
		{
			printf("Selected!\n");
			if (FD_ISSET(ifd, &readset))
			{
				iRdSz = read(ifd, szCmd, atoi(argv[2]));
				printf("Got %s from %d\n", szCmd, ifd);
				memset(szCmd, 0, 1024);
			}
		}
		else
		{
			printf("Nothing!!\n");
		}
		sleep(1);
	}

	return 0;
}
