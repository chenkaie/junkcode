
int main(void){
	int i,j;

	printf("%c\n","not a character");	/* -Wformat */
	
	if(i=10) printf("oops\n");		/* -Wparentheses */

	if(j!=10) printf("oops\n");		/* -Wuninitialized */

	/* /* */				/* -Wcomment */
	
	no_decl();				/* -Wmissing-declarations */
}

int no_decl(void){
	printf("no decl\n");
	return 0;
}
