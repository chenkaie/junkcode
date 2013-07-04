#include <stdio.h>

int main(void){
	FILE *file;
	if((file=tmpfile())==NULL) {
		printf("Cannot open temporary work file.\n");
		exit(1);
	}
	fprintf(file, "Hello! How are you.");
	fflush(file);

	char msg[10];
	fseek(file, 0, SEEK_SET);
	fscanf(file, "%s", msg);
	printf("msg=%s", msg);
	fclose(file);  
}
