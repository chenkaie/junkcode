/*  serial.c
 *  Copyright (C) 2004 www.jollen.org
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include "serial.h"

static struct termios oldtrm;

int opentty ()
{
	CommParam comm_param = { "/dev/ttyS0", TMT_B192, TMT_FNONE };
	int fd;
	struct termios trm;
	
	fd = open (comm_param.device, O_RDWR | O_NOCTTY);
	if (fd < 0){
		perror("open");
		return -1;
	}
	
	tcgetattr (fd, &oldtrm);
	bzero (&trm, sizeof (trm));
	
	switch (comm_param.bps) {
	case TMT_B3:
		trm.c_cflag = B300 | CS8 | CREAD; break;
	case TMT_B6:
		trm.c_cflag = B600 | CS8 | CREAD; break;
	case TMT_B12:
		trm.c_cflag = B1200 | CS8 | CREAD; break;
	case TMT_B24:
		trm.c_cflag = B2400 | CS8 | CREAD; break;
	case TMT_B48:
		trm.c_cflag = B4800 | CS8 | CREAD; break;
	case TMT_B96:
		trm.c_cflag = B9600 | CS8 | CREAD; break;
	case TMT_B192:
		trm.c_cflag = B19200 | CS8 | CREAD; break;
	}
	
	switch (comm_param.flow) {
	case TMT_FRTSCTS:
		trm.c_cflag |= CRTSCTS ; break;
	case TMT_FXONXOFF:
		trm.c_iflag |= IXON | IXOFF ; break;
	case TMT_FNONE: break;
	}	
	
	trm.c_iflag |= IGNPAR;
	trm.c_oflag = 0;
	trm.c_lflag = 0;
	trm.c_cc[VTIME] = 0;
	trm.c_cc[VMIN] = 0;
	
	tcflush (fd, TCIFLUSH);
	tcsetattr (fd, TCSANOW, &trm);
	
	return fd;
}


int closetty (int fd)
{
	tcsetattr (fd, TCSANOW, &oldtrm);
	if (close (fd) < 0) {
		perror("close");
		return -1;
	}
	else
		return 0;
}

void command_filter(const char *cmd, void *fd)
{
	if (strncmp(cmd, "exit", 4) == 0) {
		closetty(*(int *)fd);
		exit(0);
	}
}

void *send(void *fd)
{
	int c;
	char buf[255];

	c = 0;
	do {
		memset(buf, 0, 255);
		read(STDIN_FILENO, buf, 255);

		command_filter(buf, fd);

		if (strlen(buf) > 0) {
			if (write(*(int *)fd, buf, strlen(buf)) == -1)
				perror("write");
		}
	} while(1);
}

void *receive(void *fd)
{
	int r;
	char buf[255];

	do {
		memset(buf, 0, 255);
		r = read (*(int *)fd, buf, 255);
		if (r == -1) {
			perror ("read");
		}

		if (strlen(buf) > 0)
			write(STDOUT_FILENO, buf, strlen(buf));
	} while (1);
}

int main()
{
	pthread_t thread1, thread2;
	int fd;
	
	fd = opentty ();
	if (fd < 0) {
		perror ("Error: cannot open tty\n");
		return -1;
	}

	pthread_create(&thread1, NULL, &receive, &fd);
	pthread_create(&thread2, NULL, &send, &fd);
	printf("Tiny Minicom 0.2.0\n\n");

	do {
	} while (1);

	return 0;
}