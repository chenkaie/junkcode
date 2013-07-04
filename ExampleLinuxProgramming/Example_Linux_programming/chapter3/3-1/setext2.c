/*
 * setext2.c - Set ext2 special flags
 */
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/ext2_fs.h>
#include <sys/ioctl.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    int fd;
    long flags;
    
    /* Usage nag */
    if(argc != 2) {
		puts("USAGE: setext2 {filename}");
		exit(EXIT_FAILURE);
    }
    
    if((fd = open(argv[1], O_RDONLY)) < 0) {
		perror("open");
		exit(EXIT_FAILURE);
    }
    
    /* These are the flags we'll set on the file */
    flags = EXT2_SYNC_FL | EXT2_NODUMP_FL;
    if(ioctl(fd, EXT2_IOC_SETFLAGS, &flags)) {
		perror("ioctl");
		close(fd);
		exit(EXIT_FAILURE);
    }
    
    if(flags & EXT2_SYNC_FL)
		puts("SYNC flag set");
    if(flags & EXT2_NODUMP_FL)
		puts("NODUMP flag set");
    
    close(fd);
    exit(EXIT_SUCCESS);
}
     
