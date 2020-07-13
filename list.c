#include "list.h"

list_t list_init() {
	list_t tmp;
	tmp.head = NULL;
	tmp.size = 0;
	return tmp;
}

void list_free(list_t *l) {
	while (l->size != 0) {
		list_pop(l);
	}
}

node_t *create_new_node(void *val, type_t t) {
	node_t *temp = malloc(sizeof(node_t));
	temp->type = t;
	temp->value = val;
	temp->next = NULL;
	return temp;
}

void list_push(list_t *l, node_t *n) {
	if (l->head == NULL) {
		l->head = n;
	} else {
		n->next = l->head;
		l->head = n;
	}
	l->size++;
}

void list_push_from_file(list_t *l, char *file_name) {
	FILE *fp = fopen(file_name, "r");
	char *buffer = malloc(sizeof(char) * CHUNK);
	while(fgets(buffer, CHUNK, fp) != NULL) {
		char *bufr = malloc(sizeof(char) * CHUNK);
		strcpy(bufr, buffer);
		bufr[strlen(bufr) - 1] = '\0';
		list_push(l, create_new_node(bufr, STRING));
		free(bufr);
	}
	free(buffer);
}

void *list_pop(list_t *l) {
	if (l->head == NULL) {
		perror("Empty list");
		return NULL;
	}
	node_t *temp = l->head;
	void *returnval = temp->value;
	l->head = l->head->next;
	free(temp->value);
	free(temp);
	l->size--;
	return returnval;
}

void *list_pop_at_index(list_t *l, int index) {
	if (l->head == NULL) {
		perror("Empty list");
		return NULL;
	} else if (index > l->size - 1 || index < 0) {
		perror("Index out of bounds");
		return NULL;
	}
	node_t *temp = l->head;
	for (int i = 0; i < index - 1; i++) {
		temp = temp->next;
	}
	node_t *temp2 = temp->next;
	void *returnval = temp2->value;
	temp->next = temp2->next;
	free(temp2);
	l->size--;
	return returnval;
}

void *list_peek(list_t l) {
	if (l.head == NULL) {
		perror("Empty list");
		return NULL;
	}
	return l.head->value;
}

void *list_peek_at_index(list_t l, int index) {
	if (l.head == NULL) {
		perror("Empty list");
		return NULL;
	} else if (index > l.size - 1 || index < 0) {
		perror("Index out of bounds");
		return NULL;
	}
	node_t *temp = l.head;
	for (int i = 0; i < index; i++) {
		temp = temp->next;
	}
	return temp->value;
}
	
void list_print(list_t l) {
	node_t *temp = l.head;
	while (temp != NULL) {
		switch(temp->type) {
			case INT:
				printf("%d -> ",*(int*)temp->value);
				break;
			case DOUBLE:
				printf("%f -> ",*(double*)temp->value);
				break;
			case CHAR:
				printf("%c -> ",*(char*)temp->value);
				break;
			case STRING:
				printf("%s -> ",(char*)temp->value);
				break;
			case OTHER:
				printf("%p -> ",temp->value);
		}
		temp = temp->next;
	}
	printf("NULL\n");
}

