#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int main(void)
{
	struct flock fl = {F_RDLCK, SEEK_SET, 0, 0, 0};
	int fd;

	fl.l_pid = getpid();

	if ((fd = open("/mnt/ramdisk/video.txt", O_RDWR)) == -1)
	{
		perror("open");
		return -1;
	}

	if (fcntl(fd, F_SETLKW, &fl) == -1)
	{
		perror("fcntl");
                return -1;
	}

	char szBuff[128];
	int iLen = 0;

	iLen = read(fd, szBuff, 128);

	if (iLen > 0)
	{
		szBuff[iLen] = '\0';
		printf("Read from /mnt/ramdisk/video.txt: \n%s\n", szBuff);
	}

	printf("locked!\n");
	printf("press any key to unlock it!\n");

	getchar();

	fl.l_type = F_UNLCK;

	if (fcntl(fd, F_SETLK, &fl) == -1)
        {
                perror("fcntl");
                return -1;
        }

	printf("unlocked!\n");

	close(fd);
	

	return 0;
}
