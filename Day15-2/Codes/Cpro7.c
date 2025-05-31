#include<stdio.h>
#include<unistd.h>
int main(){
	int num=1;
	int sum=0;
		int f=fork();
        if(f==0)
        {
			printf("I am child\n");
			while(num<=5){
				printf("%d\n",num);
				sum=sum+num;
				num++;
			}
        }
        else
        {
				num=6;
                printf("I am parent\n");
                while(num<=10){
				printf("%d\n",num);
				sum=sum+num;
				num++;
			}
        }
		printf("Summation is %d\n",sum);
        return 0;
}