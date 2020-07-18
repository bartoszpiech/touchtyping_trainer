#ifndef _LIST_H_
#define _LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define CHUNK 256
//#define CHUNK 1024

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
int node_cmp(node_t n, void *val);
void node_print(FILE *stream, node_t n);


typedef struct list_t{
	node_t *head;
	int size;
} list_t;

/*
 * list functions predefinitions
 */
list_t list_init();
void list_free(list_t *l);
void list_push_old(list_t *l, node_t *n);
void list_push_i(list_t *l, int val);
void list_push_c(list_t *l, char val);
void list_push_d(list_t *l, double val);
void list_push_s(list_t *l, char *val);
void list_push_o(list_t *l, void *val);
#define list_push(a, b) _Generic(b,		\
				int: list_push_i,							\
				char: list_push_c,						\
				double: list_push_d,					\
				char*: list_push_s,						\
				void*: list_push_o)						\
				(a, b)
void list_append(list_t *l, node_t *n);
void list_read_from_file(list_t *l, char *file_name,
												 void (*list_add)(list_t*, node_t*));
void *list_pop(list_t *l);
void *list_pop_at_index(list_t *l, int index);
void *list_peek(list_t l);
void *list_peek_at_index(list_t l, int index);
void list_print_to_stream(FILE *stream, list_t l);
void list_print_to_file(char *file_name, list_t l);
#define list_print(a, b) _Generic(a,	\
				 FILE*: list_print_to_stream, \
				 char*: list_print_to_file)		\
				 (a, b)
int  list_contains(list_t l, void *val);
int  list_search(list_t l, void *val);
#endif
