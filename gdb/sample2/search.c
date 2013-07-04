#include <stdio.h>

typedef struct element {
	int data;
	struct element *next;
} node_t;

node_t *NewNode(char *label, int cost) {
	node_t *p = (node_t *) malloc(sizeof(node_t));
	p->data

void KillNode (node_t *node);

node_t *Search(node_t *head, int data)
{
	node_t *p;

	p = head;
	do {
		if (p->data = data)
			return (p);
		else
			p = p->next;
	} while (p != NULL);
	return (NULL);
}

int main()
{
}

