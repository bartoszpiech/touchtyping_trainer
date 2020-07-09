#include <stdio.h>
#include <time.h>
#include <unistd.h>

int check_sentence(char *sent, char *user_sent) {
	int error_count = 0;
	for(int i = 0; sent[i] != '\0'; i++) {
		printf("%c %c\n", sent[i], user_sent[i]);
		if (sent[i] != user_sent[i]) {
			error_count++;
		}
	}
	return error_count;
}

int main() {
	char start_key, sentence[128];
	char example[] = "A quick brown fox jumped over the red fence.";
	time_t start, end;
	scanf("%c", &start_key);
	start = time(NULL);
	printf("%s\n", example);
	scanf("%[^\n]s", sentence);
	end = time(NULL);
	double elapsed_time = (double)end - start ;
	printf("result: \terrors: %d,\ttime: %f\n", check_sentence(example, sentence), elapsed_time);
	return 0;
}




