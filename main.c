#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "list.h"

int check_sentence(char *sent, char *user_sent) {
	int error_count = 0;
	for(int i = 0; sent[i] != '\0'; i++) {
		//printf("%c %c\n", sent[i], user_sent[i]);
		if (sent[i] != user_sent[i]) {
			error_count++;
		}
	}
	return error_count;
}

int main() {
	srand(time(NULL));
	list_t l;
	list_init(&l);
	list_push_from_file(&l, "temp.txt");
	char start_key, sentence[128];
	char *example = list_pop_at_index(&l, rand() % l.size);
	time_t start, end;
	scanf("%c", &start_key);
	start = time(NULL);
	printf("%s\n", example);
	scanf("%[^\n]s", sentence);
	end = time(NULL);
	double elapsed_time = (double)end - start ;
	printf("result: \terrors: %d,\ttime: %f\twpm: %f\n", check_sentence(example, sentence), elapsed_time, (strlen(example) * 60/elapsed_time) / 5);
	list_free(&l);
	return 0;
}




