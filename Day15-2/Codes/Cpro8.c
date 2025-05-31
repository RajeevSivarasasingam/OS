#include<stdio.h>
#include <unistd.h>
#include <stdbool.h>
int A,B,C;

void getInput()
{
	printf("Enter number for A: ");
    scanf("%d", &A);
	printf("Enter number for B: ");
    scanf("%d", &B);
	printf("Enter number for C: ");
    scanf("%d", &C);
}

void Pfact()
{
	unsigned long long factorial = 1;

	if (A < 0)
		printf("Factorial is not defined for negative numbers.\n");
	else {
		for (int i = 1; i <= A; ++i) {
			factorial *= i;
		}
	printf("Factorial of %d = %llu\n", A, factorial);
	}
}


void Pfibo()
{
	int first=0;
	int second=1;
	int next;
	
	printf("Fibonacci series of given number is:\n");
	for (int i=0;i<B;i++) {
		if (i<=1)
			next=i;
		else {
			next=first+second;
			first=second;
			second=next;
		}
		printf("%d\n", next);
	}

}

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;

    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}


int main(){
	
		getInput();
		int f=fork();
        if(f==0)
        {
                printf("I am child\n");
                printf("My parent ID %d\n",getppid());
				
				Pfact();
			
        }
        else
        {
            int f1=fork();
			if(f1==0)
			{
				printf("I am sibling\n");
                printf("My parent ID %d\n",getppid());
				Pfibo();
				
				if(isPrime(C))
				{
					printf("%d is a prime number.\n",C);
				}
				else
				{
					printf("%d is not a prime number.\n",C);
				}
				
			}
			else
			{
				printf("I am parent\n");
                printf("My ID %d\n",getpid());
				printf("My parent ID %d\n",getppid());
			}
        }
        return 0;
}