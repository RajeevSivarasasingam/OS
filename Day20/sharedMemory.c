(Exercide 01)
//writer process

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_SIZE 1024 // Size of the shared memory

int main() {
    key_t key = ftok("shmfile", 1089); // Generate unique key
    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666); // Create shared memory segment

    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    char *shmaddr = (char*) shmat(shmid, NULL, 0); // Attach to shared memory
    if (shmaddr == (char*) -1) {
        perror("shmat");
        exit(1);
    }

    printf("Write data: ");
    fgets(shmaddr, SHM_SIZE, stdin); // Write data to shared memory
    printf("Data written in memory: %s\n", shmaddr);

    shmdt(shmaddr); // Detach from shared memory

    return 0;
}

//reader
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_SIZE 1024 // Size of shared memory

int main() {
    key_t key = ftok("shmfile", 1089); // Generate unique key
    int shmid = shmget(key, SHM_SIZE, 0666); // Access existing shared memory

    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    char *shmaddr = (char*) shmat(shmid, NULL, 0); // Attach to shared memory
    if (shmaddr == (char*) -1) {
        perror("shmat");
        exit(1);
    }

    printf("Data read from memory: %s\n", shmaddr); // Read data from shared memory

    shmdt(shmaddr); // Detach from shared memory
	
	shmctl(shmid, IPC_RMID, NULL); //remove shared memory segment

    return 0;
}
============================================================================================================================================================================================
(Exercise 02)
//parent - child IPC via shared memory
The child should write the message to the shared memory
the parent should read that message from the shared memory and print that message
all the parent and child process should print their pid.
use fork()

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>

#define SHM_SIZE 1024 // Shared memory size

int main() {
    key_t key = ftok("shared_memory_key", 1089); // Generate unique key
    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666); // Create shared memory segment

    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    char *shmaddr = (char*) shmat(shmid, NULL, 0); // Attach to shared memory
    if (shmaddr == (char*) -1) {
        perror("shmat");
        exit(1);
    }

    pid_t pid = fork(); // Create child process

    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) { // Child process
        printf("Child PID: %d\n", getpid());
        printf("Enter message: ");
        fgets(shmaddr, SHM_SIZE, stdin); // Write message to shared memory
        strtok(shmaddr, "\n"); // Remove trailing newline
        printf("Message written to shared memory.\n");

        shmdt(shmaddr); // Detach from shared memory
        exit(0); // Ensure child exits properly
    } else { // Parent process
        wait(NULL); // Wait for child to finish writing
        printf("Parent PID: %d\n", getpid());
        printf("Message read from shared memory: %s\n", shmaddr);

        shmdt(shmaddr); // Detach from shared memory
        shmctl(shmid, IPC_RMID, NULL); // Remove shared memory segment
    }

    return 0;
}
----------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

int main() {
    size_t size = 4096;
    char *shared_mem = mmap(NULL, size, PROT_READ | PROT_WRITE,
	MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (shared_mem == MAP_FAILED) {
        perror("mmap failed");
        exit(1);
    }

    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        sprintf(shared_mem, "Hello from child!");
        printf("Child wrote: %s\n", shared_mem);
        exit(0);
    } else if (pid > 0) {
        // Parent process
        wait(NULL); // Wait for child to finish
        printf("Parent read: %s\n", shared_mem);
        munmap(shared_mem, size);
    } else {
        perror("fork failed");
        exit(1);
    }

    return 0;
}

============================================================================================================================================================================================
(Exercise 03)
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

typedef struct {
    int n, r;
    unsigned long long fact_n, fact_r, fact_n_r;
} shared_data_t;

unsigned long long factorial(int x) {
    unsigned long long result = 1;
    for (int i = 2; i <= x; i++) result *= i;
    return result;
}

int main() {
    shared_data_t *shared_mem = mmap(NULL, sizeof(shared_data_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    if (fork() == 0) { // Writer (Child Process)
        printf("[Child] Enter n: "); scanf("%d", &shared_mem->n);
        printf("[Child] Enter r: "); scanf("%d", &shared_mem->r);

        if (shared_mem->r > shared_mem->n || shared_mem->n < 0 || shared_mem->r < 0) {
            printf("[Child] Invalid input.\n");
            exit(1);
        }

        shared_mem->fact_n = factorial(shared_mem->n);
        shared_mem->fact_r = factorial(shared_mem->r);
        shared_mem->fact_n_r = factorial(shared_mem->n - shared_mem->r);
        printf("[Child] Factorials computed.\n");
        exit(0);
    }

    wait(NULL); // Reader (Parent Process)
    printf("[Parent] nCr(%d, %d) = %llu\n", shared_mem->n, shared_mem->r, shared_mem->fact_n / (shared_mem->fact_r * shared_mem->fact_n_r));
    printf("[Parent] nPr(%d, %d) = %llu\n", shared_mem->n, shared_mem->r, shared_mem->fact_n / shared_mem->fact_n_r);

    munmap(shared_mem, sizeof(shared_data_t)); // Cleanup
    return 0;
}
