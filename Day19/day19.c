 //writer process
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <sys/shm.h>
#include <sys/ipc.h>

#define SHM_SIZE 1024	//size of shared memory segment

int main()
{
	key_t key = ftok("Shmifle",102);	//generate unique key
	int shmid = shmget(key,SHM_SIZE,IPC_CREAT | 0666); //create shared memory segment
	if(shmid == -1) {
		perror("shget");
		exit(1);
	}
	
	char *shmaddr = (char *) shmat(shmid,NULL,0); //Attach to shared memory
	if(shmaddr == (char*)-1){
		perror("shamt");
		exit(1);
	}
	
	printf("Write Data: ");
	fgets(shamddr,SHM_SIZE,stdin); //write data to shared memory
	
	printf("Data written in memory: %s \n");
	
	shmdt(shmaddr);	 // Detach from shared memory
	
	return 0;
}


//reader
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/shm.h>
#include <sys/ipc.h>

#define SHM_SIZE 1024  //size of shared memory segment

int main(){
	key_t key = ftok('shmfile',102); //generate unique key
	int shmid = shmget(key,SHM_SIZE,0666); //Access shared memory segment
	if(shmid == -1){
		perror("shmget");
		exit(1);
	}
	
	char *shmaddr = (char*) shmat(shmid,NULL,0); //Attach to shared memory
	if(shmaddr == (char*)-1){
		perror("shmat");
		exit(1);
	}
	
	printf("Data read from memory: %s\n",shamddr); //Read data from shared memory
	
	shmdt(shamddr); //Detach from shared memory
	shmctl(shmid,IPC_RMID,NULL);	// Remove shared memory segment
	return 0;
}


#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

int main(){
	size_t size = 4096;
	char *shared_mem = mmap(NULL,size,PROT_READ | PROT_WRITE , MAP_SHARED | MAP_ANONYMOUS, -1,0);
	if(shared_mem == MAP_FAILED){
		perror("mmap failed");
		exit(1);
	}
	
	pid_t pid = fork();
	if(pid == 0){
		//child process
		sprintf(shared_mem, "Hello from child");
		printf("child wrote: %s\n",shared_mem);
		exit(0);
	}
	else if(pid>0){
		//parent process
		wait(NULL); // wait for child to finish
		printf("Parent read: %s\n", shared_mem);
		munmap(shared_mem,size);
	}
	else{
		perror("Fork failed");
		exit(1);
	}
	return 0;
}
