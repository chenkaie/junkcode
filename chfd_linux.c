/*  chfd - exchange fd's between 2 or 3 running processes.
 *  
 *  This was written for Linux/intel and is *very* system-specific.
 *  Needs read/write access to /dev/kmem; setgid kmem is usually enough.
 *
 *  Use: chfd pid1 fd1 pid2 fd2 [pid3 fd3]
 *
 *  With two sets of arguments, exchanges a couple of fd between the 
 *  two processes.
 *  With three sets, the second process gets the first's fd, the third gets
 *  the second's fd, and the first gets the third's fd.
 *
 *  Note that this is inherently unsafe, since we're messing with kernel
 *  variables while the kernel itself might be changing them.  It works
 *  in practice, but no self-respecting program would want to do this.
 *
 *  Written by: orabidoo <odar@pobox.com>
 *  First version: 14 Feb 96
 *  This version: 2 May 97
 */


#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#define __KERNEL__		/* needed to access kernel-only definitions */
#include <linux/sched.h>

/* #define OLDLINUX */		/* uncomment this if you're using Linux 1.x;
							   tested only on 1.2.13 */

#define TASK 0x00192d28		/* change this! look at the system map,
							   usually /boot/System.map, for the address
							   of the "task" symbol */

#ifdef OLDLINUX
#  define FD0 ((char *)&ts.files->fd[0] - (char *)&ts)
#  define AD(fd) (taskp + FD0 + 4*(fd))
#else
#  define FILES ((char *)&ts.files - (char *)&ts)
#  define FD0 ((char *)&fs.fd[0] - (char *)&fs)
#  define AD(fd) (readvalz(taskp + FILES) + FD0 + 4*(fd))
#endif


int kfd;
struct task_struct ts;
struct files_struct fs;
int taskp;

int readval(int ad) {
	int val, r;

	if (lseek(kfd, ad, SEEK_SET) < 0)
		perror("lseek"), exit(1);
	if ((r = read(kfd, &val, 4)) != 4) {
		if (r < 0)
			perror("read");
		else fprintf(stderr, "Error reading...\n");
		exit(1);
	}
	return val;
}

int readvalz(int ad) {
	int r = readval(ad);
	if (r == 0)
		fprintf(stderr, "NULL pointer found (fd not open?)\n"), exit(1);
	return r;
}

void writeval(int ad, int val) {
	int w;

	if (lseek(kfd, ad, SEEK_SET) < 0)
		perror("lseek"), exit(1);
	if ((w = write(kfd, &val, 4)) != 4) {
		if (w < 0)
			perror("write");
		else fprintf(stderr, "Error writing...\n");
		exit(1);
	}
}

void readtask(int ad) {
	int r;

	if (lseek(kfd, ad, SEEK_SET)<0)
		perror("lseek"), exit(1);
	if ((r = read(kfd, &ts, sizeof(struct task_struct))) !=
			sizeof(struct task_struct)) {
		if (r < 0)
			perror("read");
		else fprintf(stderr, "Error reading...\n");
		exit(1);
	}
}

void findtask(int pid) {
	int adr;

	for (adr=TASK; ; adr+=4) {
		if (adr >= TASK + 4*NR_TASKS)
			fprintf(stderr, "Process not found\n"), exit(1);
		taskp = readval(adr);
		if (!taskp) continue;
		readtask(taskp);
		if (ts.pid == pid) break;
	}
}

int main(int argc, char **argv) {
	int pid1, fd1, pid2, fd2, ad1, val1, ad2, val2, pid3, fd3, ad3, val3;
	int three=0;

	if (argc != 5 && argc != 7)
		fprintf(stderr, "Use: %s pid1 fd1 pid2 fd2 [pid3 fd3]\n", argv[0]), 
			exit(1);

	pid1 = atoi(argv[1]), fd1 = atoi(argv[2]);
	pid2 = atoi(argv[3]), fd2 = atoi(argv[4]);
	if (argc == 7)
		pid3 = atoi(argv[5]), fd3 = atoi(argv[6]), three=1;

	if (pid1 == 0)
		pid1 = getpid(), fd1 = open("/dev/null", O_RDWR);
	if (pid2 == 0)
		pid2 = getpid(), fd2 = open("/dev/null", O_RDWR);
	if (three && pid3 == 0)
		pid3 = getpid(), fd3 = open("/dev/null", O_RDWR);

	kfd = open("/dev/kmem", O_RDWR);
	if (kfd < 0)
		perror("open"), exit(1);

	findtask(pid1);
	ad1 = AD(fd1);
	val1 = readvalz(ad1);
	printf("Found fd pointer 1, value %.8x, stored at %.8x\n", val1, ad1);

	findtask(pid2);
	ad2 = AD(fd2);
	val2 = readvalz(ad2);
	printf("Found fd pointer 2, value %.8x, stored at %.8x\n", val2, ad2);

	if (three) {
		findtask(pid3);
		ad3 = AD(fd3);
		val3 = readvalz(ad3);
		printf("Found fd pointer 3, value %.8x, stored at %.8x\n", val3, ad3);
	}

	if (three) {
		if (readval(ad1)!=val1 || readval(ad2)!=val2 || readval(ad3)!=val3) {
			fprintf(stderr, "fds changed in memory while using them - try again\n");
			exit(1);
		}
		writeval(ad2, val1);
		writeval(ad3, val2);
		writeval(ad1, val3);
	} else {
		if (readval(ad1)!=val1 || readval(ad2)!=val2) {
			fprintf(stderr, "fds changed in memory while using them - try again\n");
			exit(1);
		}
		writeval(ad1, val2);
		writeval(ad2, val1);
	}
	printf("Done!\n");
}

