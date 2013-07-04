#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define CLEAR(s) memset(&(s), 0, sizeof(s))
#define SANITIZE(obj) { memset(&obj, 0, sizeof(typeof(obj))); }
#define PAL2NTSC_HEIGHT_RATIO           1.2f

typedef enum
{
	epdfNoItem				 = 0x00,
	epdfPan                  = 0x01,
	epdfTilt                 = 0x02,
	epdfZoom                 = 0x04,
} EXYZPosDiffFlags;

int main(int argc, const char *argv[])
{
    unsigned long long int test = 4294967295;
    printf("test = %lld\n", test);
	puts("=========================================");
    printf("sizeof(double) = %ld\n", sizeof(double));
    printf("sizeof(float) = %ld\n", sizeof(float));
    printf("sizeof(long long int) = %ld\n", sizeof(long long int));
    printf("sizeof(long long) = %ld\n", sizeof(long long));
    printf("sizeof(long int) = %ld\n", sizeof(long int));
    printf("sizeof(long) = %ld\n", sizeof(long));
    printf("sizeof(int) = %ld\n", sizeof(int));
    printf("sizeof(int *) = %ld\n", sizeof(int *));
    printf("sizeof(unsigned int) = %ld\n", sizeof(unsigned int));
    printf("sizeof(short) = %ld\n", sizeof(short));
    printf("sizeof(unsigned short) = %ld\n", sizeof(unsigned short));
    printf("sizeof(char) = %ld\n", sizeof(char));
    printf("sizeof(enum) = %ld\n", sizeof(epdfNoItem));
	puts("=========================================");
    printf("sizeof(int8_t) = %ld\n", sizeof(int8_t));
	printf("sizeof(uint8_t) = %ld\n", sizeof(uint8_t));
    printf("sizeof(int16_t) = %ld\n", sizeof(int16_t));
	printf("sizeof(uint16_t) = %ld\n", sizeof(uint16_t));
    printf("sizeof(int32_t) = %ld\n", sizeof(int32_t));
	printf("sizeof(uint32_t) = %ld\n", sizeof(uint32_t));
	puts("=========================================");
    printf("sizeof(time_t) = %ld\n", sizeof(time_t));
    printf("sizeof(off_t) = %ld\n", sizeof(off_t));
    printf("sizeof(size_t) = %ld\n", sizeof(size_t));
    printf("sizeof(uid_t) = %ld\n", sizeof(uid_t));
    printf("sizeof(dev_t) = %ld\n", sizeof(dev_t));
    printf("sizeof(pid_t) = %ld\n", sizeof(pid_t));
	puts("=========================================");
    return 0;
}
