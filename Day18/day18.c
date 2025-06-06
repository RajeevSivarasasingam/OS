
[2021ict102@fedora ~]$ touch progFile1
[2021ict102@fedora ~]$ chmod 644 progFile1
[2021ict102@fedora ~]$



//send 

#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#define MAX 10

//structure for meassage queue
struct mesg_buffer{
	long mesg_type;
	char mesg_text[100];
	}
	message;
	
	int main()
	{
		key_t key;
		int msgid;
		//ftok to generate  uique key
		key = ftok("progFile1",102);
		//msgget creates a meassage queue
		//and returns indentifier
		msgid = msgget(key,0666 | IPC_CREAT);
		message.mesg_type = 1;
		printf("Write Data: ");
		fgets(message.mesg_text,MAX,stdin);
		//msgsnd to  send meassage
		msgsnd(msgid,&message,sizeof(message),0);
		//display the message
		printf("Data send is : %s\n",message.mesg_text);
		
	return 0;
	}
	
	
//Recive
#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#define MAX 10

//structure for meassage queue
struct mesg_buffer{
	long mesg_type;
	char mesg_text[100];
	}
	message;
int main()
{
	 
		key_t key;
		int msgid;
	
	//ftok to generate unique key
	key = ftok("progFile1",102);
	//mesget creates a meassage queue
	msgid = msgget(key,0666 | IPC_CREAT);
	//msgrcv to receive  meassage
	msgrcv(msgid, &message, sizeof(message),1,0);
	//display the meassage
	printf("Data Recived is: %s \n",message.mesg_text);
	//to destroy the message queue
	msgctl(msgid,IPC_RMID,NULL);
		return 0;
	
}	



