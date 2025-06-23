// Thread
#include<stdio.h>		 // Standard input/output library for functions like printf
#include<stdlib.h>		// Standard library for functions like exit.
#include<unistd.h>	   // Provides access to the POSIX operating system API, including the sleep function.
#include<pthread.h>	  // Header file for the POSIX threads library, which provides functions for creating and managing threads.

void *helloworld(void *vargp)
{
	sleep(1);
	printf("Hello World \n");
	return NULL;
}

int main()
{
	pthread_t thread_id;
	printf("Before Thread \n");
	pthread_create(&thread_id,NULL,helloworld,NULL);
	pthread_join(thread_id,NULL);
	printf("After Thread\n");
	exit(0);
}