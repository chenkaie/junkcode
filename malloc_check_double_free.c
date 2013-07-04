#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) 
{
	char *cptr;
	char *cptr2;

	/* malloc() always provides aligned memory */
	cptr = malloc(sizeof(char));

	*cptr = 10;
	printf("before free, sizeof(char) = %ld, sizeof(cptr) = %ld\n", sizeof(char), sizeof(cptr));

	/*free(cptr);
	printf("after first free\n");*/

	printf("hello, cptr = %d, %x\n", *cptr, cptr);

	// Ref code: /home/vivotek/mv_pro_5.0/montavista/pro/devkit/arm/v5t_le/target/usr/src/debug/glibc-2.5.90/malloc/malloc.c:4665
	// Try to break "heap metadata"
	//*(cptr-8) = 0x21; // double free or corruption (fasttop) --> Default double free message
	//*(cptr-8) = 0x19; // invalid size
	//*(cptr-5) = 0x1; // double free or corruption (!out)
	//*(cptr-7) = 0x1; // double free or corruption (!prev)

	// For DM36X Arm platform
	//*(cptr-3) = 0x1; // double free or corruption (!prev)

	//free(cptr);
	//printf("after double free\n");

	// Heap metadata is recorded at (cptr-8 ~ cptr-1)
	/* ========================================================================================================================================
	~ # cat /proc/26415/maps
	00008000-00009000 r-xp 00000000 00:11 320865516  /home/kent/Junkcode/malloc_check_double_free.dm365.out
	00010000-00011000 rw-p 00000000 00:11 320865516  /home/kent/Junkcode/malloc_check_double_free.dm365.out
	00011000-00032000 rwxp 00011000 00:00 0          [heap]

	~ # ./malloc_check_double_free.dm365.out
	hello, cptr = 10, 11008
	hello, cptr2 = 10, 11018
	*** glibc detected *** /home/kent/Junkcode/malloc_check_double_free.dm365.out: double free or corruption (!prev): 0x00011018 ***

    (gdb) x/60t 0x11000
    0x11000:        00000000        00000000        00000000        00000000        00010001        00000000        00000000        00000000
    0x11008:        00001010(10)    00000000        00000000        00000000        00000000        00000000        00000000        00000000
    0x11010:        00000000        00000000        00000000        00000000        00010001        00000001(!prev) 00000000        00000000
    0x11018:        00001010(10)    00000000        00000000        00000000        00000000        00000000        00000000        00000000
    0x11020:        00000000        00000000        00000000        00000000        11100001        00001111        00000010        00000000
    0x11028:        00000000        00000000        00000000        00000000        00000000        00000000        00000000        00000000
    0x11030:        00000000        00000000        00000000        00000000        00000000        00000000        00000000        00000000
    0x11038:        00000000        00000000        00000000        00000000

	======================================================================================================================================== */

	cptr2 = malloc(sizeof(char));
	*cptr2 = 10;
	printf("hello, cptr2 = %d, %x\n", *cptr2, cptr2);
	//*(cptr2-3) = 0x1; // double free or corruption (!prev)
	printf("cptr2 = %d,%d,%d,%d,%d\n", *(cptr2-4), *(cptr2-3), *(cptr2-2), *(cptr2-1), *(cptr2-0));
	free(cptr2);

	return 0;
}

