
int main(void){
	int fd[2];
	char buf[128];

	pipe(fd);

	write(fd[1],"test\n\0",6);
	read(fd[0],buf,128);
	printf("%s",buf);
}
