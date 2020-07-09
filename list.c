//#ifndef _LIST_H
//#define _LIST_H
#include <stdio.h>

typedef struct node {
	void *value;
	struct node *next;
} node;

typedef struct {
	node *head;
	int size;
} list;

list list_init() {
	list tmp;
	tmp.head = NULL;
	tmp.size = 0;
	return tmp;
}



int main() {
	list l1 = list_init();



	return 0;
}


//#endif
