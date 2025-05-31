#include<stdio.h>
#include <unistd.h>//for exit()
#include <stdlib.h>//for sleep()
int main(){
	printf("Program started.\n");
	
	printf("Sleeping for 3 seconds...\n");
	sleep(3);//pause for 3 seconds
	
	printf("Eiting the program.\n");
	exit(0);//clean exit
	
	return(0);
}