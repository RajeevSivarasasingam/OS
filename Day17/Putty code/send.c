//send
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MAX 10
//structure for msg queue
struct mesg_buffer{
long mesg_Type;
char mesg_text[100];
}message;
int main()
{
	key_t key;
	int msgid;
	//ftok to generate unique key
	key=ftok("send",1109);
	//msgget creates a message queue
	//and returns identifier
	msgid=msgget(key,0666|IPC_CREAT);
	message.mesg_Type=1;
	printf("Write data: ");
	fgets(message.mesg_text,MAX,stdin);
	//msgsnd to send message
	//msgsnd(msgid, &message, sizeof(message.mesg_text), 0);

	msgsnd(msgid,&message,sizeof(message),0);
	//display the message
	printf("Data send is : %s \n",message.mesg_text);
	return 0;
}
