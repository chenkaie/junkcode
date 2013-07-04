#include <stdio.h>

typedef struct lnode { 
	struct lnode *next;
	void *obj;
} ListNode;

typedef struct {
	ListNode *head;
} List;

void ListNew(List *list) {
	list->head = NULL;
}

void ListAdd(List *list, ListNode *node) {
	if (node == NULL) return;
	node->next = list->head;
	list->head = node;
}

typedef void(*F1)(void*);

void ListPrint(List *list, F1 f) {
	ListNode *p;
	for (p = list->head; p != NULL; p=p->next)
		f(p->obj);
}

typedef struct {
	char *name;
	int age;
} Person;

void PersonPrint(Person *p) {
	printf("%s is %d years old\n", p->name, p->age);  
}

int main() {
	Person john = {
		.name = "John",
		.age = 40
	};
	Person mary = {
		.name = "Mary",
		.age = 32
	};
	Person george = {
		.name = "George",
		.age = 26
	};
	ListNode jnode = { .obj=&john, .next=NULL };
	ListNode mnode = { .obj=&mary, .next=NULL };
	ListNode gnode = { .obj=&george, .next=NULL };
	List list;
	ListNew(&list);
	ListAdd(&list, &jnode);
	ListAdd(&list, &mnode);
	ListAdd(&list, &gnode);
	ListPrint(&list, (F1) PersonPrint);
	return 0;
}
