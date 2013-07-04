
enum data{A,B,C,D,E};
int main(){
	enum data var; 
	var=C;
	switch(var){
		case A...E:
			printf("%d\n",var);
			break;
	}
}
