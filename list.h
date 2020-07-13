#ifndef _LIST_H_
#define _LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define CHUNK 256

typedef enum TYPE_STRUCT_T { INT, DOUBLE, CHAR , STRING, OTHER} type_t;

typedef struct node_t {
	type_t type;
	void *value;
	struct node_t *next;
} node_t;
/*
 * node functions predefinitions
 */
node_t *create_new_node(void *val, type_t t);

typedef struct list_t{
	node_t *head;
	int size;
} list_t;

/*
 * list functions predefinitions
 */
list_t list_init();
void list_free(list_t *l);
void list_push(list_t *l, node_t *n);
void list_push_from_file(list_t *l, char *file_name);
void *list_pop(list_t *l);
void *list_pop_at_index(list_t *l, int index);
void *list_peek(list_t l);
void *list_peek_at_index(list_t l, int index);
void list_print(list_t l);
#endif
