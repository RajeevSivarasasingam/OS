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
	//output
	 vi thread.c
[2021ict102@fedora codec]$ gcc thread.c -o thread
[2021ict102@fedora codec]$ ./thread
Before Thread
Hello World
After Thread
/* ============================================================================================= */

// Multi process
#include<stdio.h>
#include<pthread.h>

//Function to be executed by the thread
void * print_message(void* arg){
	char* message =(char *)arg;
	printf("%s\n",message);
	return NULL;
}

int main()
{
	pthread_t thread1,thread2;
	
	//creat first thread
	pthread_create(&thread1,NULL,print_message,"Hello World Thread1 ");
	//creat second thread
	pthread_create(&thread2,NULL,print_message,"Hello World Thread2 ");
	
	//wait for both threads to finish
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	
	printf("Both threads completed \n");
	return 0;
}

// Output::
Hello World Thread1
Hello World Thread2
Both threads completed

/* ================================================================================== */

// thread using array

#include <stdio.h>
#include <pthread.h>

void * print_message(void * arg)
{
	char* message = (char*)arg;
	printf("%s \n ",message);
	return NULL;
}

int main()
{
	pthread_t thread[3]; // Array to hold thread IDs for 3 threads
	char* message[]={
		"Thread 1 says hi!",
		"Thread 1 says Hello!",
		"Thread 1 says Hey!"
	};
for(int i=0;i<3;i++){
	pthread_create(&thread[i],NULL,print_message,message[i]);
}
for(int i=0;i<3;i++)
{
	pthread_join(&thread[i],NULL);
}
 
 printf("All threads done \n");

return 0;
}

//using thread to compute parts of a sum (partical sum)
#include <stdio.h>
#include <pthread.h>

#define SIZE G

int arr[SIZE]={1,2,3,4,5,6};
int sum1 =0 ,sum2=0;

void* sum_part1(void* arg)
{
	for(int i=0;i<SIZE/2;i++)
	{
		sum1 += arr[i];
	}
	return NULL;
}

void* sum_part2(void* arg)
{
	for(int i=SIZE/2;i<SIZE;i++)
	{
		sum2 += arr[i];
	}
	return NULL;
}

int main()
{
	pthread_t t1,t2;
	
	pthread_create(&t1,NULL,sum_part1,NULL);
	pthread_create(&t2,NULL,sum_part2,NULL);
	
	pthread_join(&t1,NULL);
	pthread_join(&t2,NULL);
	
	printf("Total sum: %d\n",sum1+sum2);
	return 0;
}





