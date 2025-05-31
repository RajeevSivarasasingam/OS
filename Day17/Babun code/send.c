
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MAX 10

struct mesg_buffer{
long mesg_Type;
char mesg_text[100];
}message;
int main()
{
	key_t key;
	int msgid;
	
	key=ftok("send",1109);
	
	msgid=msgget(key,0666|IPC_CREAT);
	message.mesg_Type=1;
	printf("Write data: ");
	fgets(message.mesg_text,MAX,stdin);
	msgsnd(msgid,&message,sizeof(message),0);
	printf("Data send is : %s \n",message.mesg_text);
	return 0;
}
