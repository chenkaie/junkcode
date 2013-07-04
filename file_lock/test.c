#include <stdio.h>
#include <sys/file.h>

int main(void)
{
	int fd;

	fd = open("/mnt/ramdisk/video.txt", O_RDWR);

	if (flock(fd, LOCK_EX) < 0)
	{
		perror("flock");
		return -1;
	}

	getchar();

	if (flock(fd, LOCK_UN) < 0)
        {
                perror("flock");
                return -1;
        }

	close(fd);
	

	return 0;
}
