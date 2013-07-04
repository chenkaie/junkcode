#include <stdio.h>

void test()
{
	int iTmp = 10;
	fprintf(stderr, "[%s] %s, iTmp = %d\n", __func__, "I am here", iTmp);
}

int main(int argc, const char *argv[])
{
	char acDead[128];
	char a[64*1024];
	memset(a, '1', sizeof(a));
	//sprintf(acDead, "%s", "12345678901234567890123456789012345678901234567890123456789012345678901234567890");
	//test();
	int ret = snprintf(acDead, sizeof(acDead), "%s", a);
	fprintf(stderr, "[%s] ret=%d\n", __func__, ret);
	/*snprintf(acDead, 2, "%s", "1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz");*/
	printf("[%s] sizeof(acDead)=%d, acDead = %c,%c,%c, acDead=%s\n", __func__, sizeof(acDead), acDead[0], acDead[1], acDead[2], acDead);

	return 0;
}
