#include <stdio.h>
#include <string.h>
#include <sys/types.h>

void xor_encrypt(char *key, char *string, int n)
{
	int i;
	int keyLength = strlen(key);
	for( i = 0 ; i < n ; i++ )
	{
		string[i]=string[i]^key[i%keyLength];
	}
}

void xor_encrypt2(const u_int8_t *key, u_int8_t *string, int n)
{
	int i;
	int keyLength = sizeof(key)/sizeof(u_int8_t);
	for( i = 0 ; i < n ; i++ )
	{
		string[i]=string[i]^key[i%keyLength];
	}
}
int main(void) {
	char plain[] = "This is plain text";
	u_int8_t plain2[] = "\x54\x68\x00\x73\x20\x69\x00\x20";

	char key[] = "Abcdabcdabciabcdabcd";
	const u_int8_t key2[] = "\x81\x93\xe0\xc4";
	int n = strlen(plain);
	printf("[%s] strlen(palin) = %d\n", __func__, n);
	// encrypt:
	xor_encrypt(key, plain, n);
	xor_encrypt2(key2, plain2, 8);
	printf("encrypted string: \n");
	for(int ii = 0; ii < n; ii++) {
		if(plain[ii] > 0x32 && plain[ii] < 0x7F ) printf("%c", plain[ii]);
		else printf(" 0x%02x ", plain[ii]);
	}
	printf("\n");
	for(int ii = 0; ii < 8; ii++) {
		printf(" 0x%02x ", plain2[ii]);
	}
	printf("\n");
	xor_encrypt(key, plain, n);
	printf("after round trip, plain string is '%s'\n", plain);
	printf("\n");
	xor_encrypt2(key2, plain2, 8);
	printf("after round trip, plain string is '%s'\n", (char *)plain2);
	for(int ii = 0; ii < 8; ii++) {
		printf(" 0x%02x ", plain2[ii]);
	}
	printf("\n");
}

