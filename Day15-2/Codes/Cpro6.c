#include<stdio.h>
#include<unistd.h>
int main(){
        int f=fork();
        if(f==0)
        {
                printf("I am child\n");
                printf("My parent ID is %d\n",getppid());
        }
        else
        {
                printf("I am parent\n");
                printf("My ID is %d\n",getpid());
                printf("My parent ID is %d\n",getppid());
        }

        return 0;
}