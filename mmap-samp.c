#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define MAP_SIZE 1024
#define MAP_MASK (MAP_SIZE-1)

#define SERIAL_MAP_ADDRESS 0x11000000
#define SMC_MAP_ADDRESS 	0x30000000	

#define FATAL do { fprintf(stderr, "Error at line %d, file %s (%d) [%s]\n", \
        __LINE__, __FILE__, errno, strerror(errno)); exit(1); } while(0)

#define u8 		unsigned char
#define u16 	unsigned short
#define u32 	unsigned int

char *teststr = "This is test string";

int main(void){
    int fd,i;
    void *smc_addr,*serial_addr,*psmc_addr,*pserial_addr;
    u32 u32tmp;
    u16 u16tmp;
    u8 u8tmp;

    /* Must be O_SYNC, non cache */
    if((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1) FATAL;

    printf("/dev/mem opened.\n");
    fflush(stdout);

    psmc_addr = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED,\
            fd,SMC_MAP_ADDRESS & ~MAP_MASK);

    pserial_addr = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED,\
            fd,SERIAL_MAP_ADDRESS & ~MAP_MASK);

    if(psmc_addr == (void *) -1) {
        printf("map_base:%x \n",psmc_addr); FATAL;}
    printf("Memory mapped at address %p.\n", psmc_addr);


    if(pserial_addr == (void *) -1) {
        printf("map_base:%x \n",pserial_addr); FATAL;}
    printf("Memory mapped at address %p.\n", pserial_addr);

    fflush(stdout);

    smc_addr 	= psmc_addr + (SMC_MAP_ADDRESS & MAP_MASK);
    serial_addr = pserial_addr + (SERIAL_MAP_ADDRESS & MAP_MASK);


    /* Set Static Memory Address */
    u32tmp = (*(volatile u32 *)(smc_addr));
    *(volatile u32 *)(smc_addr+8) 	= 0x11000000;
    *(volatile u32 *)(smc_addr+12)	= 0x001FF3FF;


    /* Configure UART to 38400 */
    *(volatile u8 *)(serial_addr+3)	= 0x93;
    *(volatile u8 *)(serial_addr+0)	= 0x03;
    *(volatile u8 *)(serial_addr+1)	= 0x00;
    *(volatile u8 *)(serial_addr+3)	= 0x13;
    *(volatile u8 *)(serial_addr+4)	= 0x00;


    /* Send character to serial */
    for(i=0;i<20; i++){
        *(volatile u8 *)(serial_addr+0)	= teststr[i];
        usleep(50);
    }

    close(fd);
}
