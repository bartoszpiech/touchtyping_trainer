#include "list.h"

node_t *create_new_node(void *val, type_t t) {
	node_t *temp = malloc(sizeof(node_t));
	temp->type = t;
	temp->value = val;
	temp->next = NULL;
	return temp;
}

int node_cmp(node_t n, void *val) {
	switch(n.type) {
		case INT:
			if(*(int*)n.value == *(int*) val) return 0;
			break;
		case DOUBLE:
			if(*(double*)n.value == *(double*) val) return 0;
			break;
		case CHAR:
			if(*(char*)n.value == *(char*) val) return 0;
			break;
		case STRING: // todo
			if(strcmp((char*)n.value, (char*) val) == 0) return 0;
			break;
		case OTHER:
			break;
	}
	return -1;
}

void node_print(FILE *stream, node_t n) {
	switch(n.type) {
		case INT:
			fprintf(stream,"%d",*(int*)n.value);
			break;
		case DOUBLE:
			fprintf(stream,"%f",*(double*)n.value);
			break;
		case CHAR:
			fprintf(stream,"%c",*(char*)n.value);
			break;
		case STRING:
			fprintf(stream,"%s",(char*)n.value);
			break;
		case OTHER:
			fprintf(stream,"%p",n.value);
	}
}


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

void list_push_old(list_t *l, node_t *n) {
	if (l->head == NULL) {
		l->head = n;
	} else {
		n->next = l->head;
		l->head = n;
	}
	l->size++;
}

void list_push_i(list_t *l, int val) {
	int *ptr = malloc(sizeof(int));
	*ptr = val;
	node_t *n = create_new_node(ptr, INT);
	list_push_old(l, n);
}

void list_push_c(list_t *l, char val) {
	int *ptr = malloc(sizeof(char));
	*ptr = val;
	node_t *n = create_new_node(ptr, CHAR);
	list_push_old(l, n);
}

void list_append(list_t *l, node_t *n) {
	if (l->head == NULL) {
		l->head = n;
	} else {
		node_t *temp = l->head;
		while(temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = n;
	}
	l->size++;
}

void list_read_from_file(list_t *l, char *file_name,
												 void (*list_add)(list_t*, node_t*)) {
	FILE *fp = fopen(file_name, "r");
	if (fp == NULL) {
		perror("Cannot open file for reading");
		return;
	}
	char buffer[CHUNK];
	while(fgets(buffer, CHUNK, fp) != NULL) {
		buffer[strlen(buffer) - 1] = '\0';
		(*list_add)(l, create_new_node(strdup(buffer), STRING));
	}
	fclose(fp);
}

/*
void list_push_from_file(list_t *l, char *file_name) {
	FILE *fp = fopen(file_name, "r");
	char *buffer = malloc(sizeof(char) * CHUNK);
	char bufr;
	while(fgets(buffer, CHUNK, fp) != NULL) {
		bufr = malloc(sizeof(char) * CHUNK);
		strcpy(bufr, buffer);
		bufr[strlen(bufr) - 1] = '\0';
		list_push(l, create_new_node(bufr, STRING));
	}
	//free(bufr);
	free(buffer);
}
*/

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
	//free(temp2->value); to do memleak
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

void list_print_to_stream(FILE *stream, list_t l) {
	node_t *temp = l.head;
	fprintf(stream, "size: %d\n", l.size);
	while (temp != NULL) {
		node_print(stream,*temp);
		fprintf(stream, " -> ");
		temp = temp->next;
	}
	fprintf(stream, "NULL\n");
}

void list_print_to_file(char* file_name, list_t l) {
	FILE *fp = fopen(file_name, "w");
	if (fp == NULL) {
		perror("Cannot open file for writing");
		return;
	}
	node_t *temp = l.head;
	while (temp != NULL) {
		node_print(fp, *temp);
		fprintf(fp, "\n");
		temp = temp->next;
	}
}

int list_search(list_t l, void *val) {
	node_t *temp = l.head;
	//for (int i = 0; temp != NULL; i++) {
	for (int i = 0; i < l.size; i++) {
		if (node_cmp(*temp, val) == 0) {
			return i;
		}
		temp = temp->next;
	}
	return -1;
}

