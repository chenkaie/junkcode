#include <stdlib.h>

int main(int argc,char *argv[]){
	int *ptr;
	ptr=malloc(sizeof(int)*100);		//此為ANSI C的寫法
	ptr=(int *)malloc(sizeof(int)*100);	//此為舊的寫法
}
