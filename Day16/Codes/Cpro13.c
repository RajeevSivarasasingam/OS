/* Exercise02
   First child: sleeps for 2 seconds, exits with status 2
   Second child: sleeps for 1 second, exits with status 1
   Parent: waits twice and prints which child (by PID or exit code)
   finished first and second
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2;
    int status;

    printf("Parent process started. PID: %d\n", getpid());

    pid1 = fork();

    if (pid1 < 0) {
        perror("fork failed for child1");
        exit(1);
    }

    if (pid1 == 0) {
        printf("I am Child1. My parent ID: %d\n", getppid());
        printf("Child1 process. PID: %d, sleeping for 2 seconds...\n", getpid());
        sleep(2);
        printf("Child1 process exiting with status 2.\n");
        exit(2);
    }

    pid2 = fork();

    if (pid2 < 0) {
        perror("fork failed for child2");
        exit(1);
    }

    if (pid2 == 0) {
        printf("I am Child2. My parent ID: %d\n", getppid());
        printf("Child2 process. PID: %d, sleeping for 1 second...\n", getpid());
        sleep(1);
        printf("Child2 process exiting with status 1.\n");
        exit(1);
    }

    pid_t finished1 = wait(&status);
    printf("First finished child: PID = %d, Exit status = %d\n", finished1, WEXITSTATUS(status));

    pid_t finished2 = wait(&status);
    printf("Second finished child: PID = %d, Exit status = %d\n", finished2, WEXITSTATUS(status));

    printf("Parent process ending.\n");
    return 0;
}
