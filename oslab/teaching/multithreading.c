#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

void printing() {
	printf("hello world!\n");
	sleep(1);
}

int main() {
	pthread_t t1, t2, t3, t4, t5;

	printing();
	printing();
	printing();
	printing();
	printing();
	printf("\n\n\n");

	pthread_create(&t1, NULL, printing, NULL);	
	pthread_create(&t2, NULL, printing, NULL);	
	pthread_create(&t3, NULL, printing, NULL);	
	pthread_create(&t4, NULL, printing, NULL);	
	pthread_create(&t5, NULL, printing, NULL);
		
	printf("This is the main process xD\n");

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	pthread_join(t4, NULL);
	pthread_join(t5, NULL);
	return 0;
}