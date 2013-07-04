#include <stdio.h>
#include <string.h>

int priority(char x)
{
	switch (x) {
		case '+':
		case '-': 
			return 0;
		case '*':
		case '/': return 1;
		default: return 2;
	}
}

main()
{
	char exp[500], stack[500], pre[500];
	int prelen, top = 0;
	int i;

	printf("Input expression: ");
	scanf("%s", exp);

	pre[499] = '\0';
	prelen = 499;

	for (i = strlen(exp)-1; i >= 0; i--) {
		if (exp[i] == '(') {
			top--;
			while (stack[top] != ')')
				pre[--prelen] = stack[top--];
			continue;
		}
		if (exp[i] >= '0' && exp[i] <= '9') {
			pre[--prelen] = exp[i];
			continue;
		}
		if (priority(stack[top-1]) >= priority(exp[i]) && top) {
			while (priority(stack[top-1]) >= priority(exp[i]) && top)
				pre[--prelen] = stack[--top];
		}
		stack[top++] = exp[i];
	}
	while (top)
		pre[--prelen] = stack[--top];

	printf("Prefix: %s\n", &pre[prelen]);
}

