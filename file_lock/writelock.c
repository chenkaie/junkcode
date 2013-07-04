#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char * argv[])
{
	struct flock fl = {F_WRLCK, SEEK_SET, 0, 0, 0};
	int fd;
	char *pcTarg = NULL;


	int c;

	while ((c = getopt(argc, argv, "i:")) != -1)
	{
		switch(c)
		{
			case 'i':
				pcTarg = optarg;
				break;
			default:
				printf("Please specify your input!\n");
				exit(1);
		}
	}

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

	if (pcTarg != NULL)
		write(fd, pcTarg, strlen(pcTarg));

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
