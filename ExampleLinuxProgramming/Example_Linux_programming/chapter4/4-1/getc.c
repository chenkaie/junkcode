#include <stdio.h>

int main(void){
	FILE *a[]={stdin};
	FILE **p=a;
	getc(*p++);
}
