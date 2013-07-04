#include <stdio.h>

int main(void)
{
	FILE *fp;
	char buf[256];
	int line=1;
	fp = popen("ls -al" ,"r");
	while (fgets(buf,256,fp) != NULL)
	{
		printf("%d: %s", line++, buf);
	}

	pclose(fp);
}
