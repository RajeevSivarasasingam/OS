/*exercise02
first child:slept for 1 second
second child:slept for 3 seconds
parent:both children have finished
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	pid_t pid;
	printf("Parent process started. PID: %d\n",getpid());
	
	pid=fork();
	
	if(pid<0){
		perror("fork failed\n");
		exit(1);
	}
	
	if (pid==0){
		printf("I am Child1. My parent ID: %d\n",getppid());
		printf("Child1 process. PID: %d, sleeping for 1 seconds...\n",getpid());
		sleep(1);
		printf("Child1 process exiting.\n");
		exit(0);
	}
	else{
		pid_t pid2;
		pid2=fork();
		if(pid2<0){
		perror("fork failed\n");
		exit(1);
		}
		
		if (pid2==0){
		printf("I am Child2. My parent ID: %d\n",getppid());
		printf("Child2 process. PID: %d, sleeping for 3 seconds...\n",getpid());
		sleep(3);
		printf("Child2 process exiting.\n");
		exit(0);
		}
		else
		{
			int status;
			printf("Parent waiting for both child to finish...\n");
			wait(&status);
			if(WIFEXITED(status)){
				printf("Children exited with status. %d\n", WEXITSTATUS(status));
			}
			else{
				printf("Children did not exit normally.\n");
			}
			printf("Parent process ending.\n");
		}
	}
}