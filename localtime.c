#include <time.h>
#include <stdio.h>

int main(int argc, const char *argv[])
{
	time_t timep;
	struct tm *p;
	time(&timep);
	p=localtime(&timep);
	printf("%d/%d/%d ",(1900+p->tm_year), (1+p->tm_mon),p->tm_mday );
	printf("%d:%d:%d\n", p->tm_hour, p->tm_min, p->tm_sec);

	return 0;
}
