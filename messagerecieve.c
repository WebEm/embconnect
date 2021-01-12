#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>

struct msg_buffer
{
long msg_type;
char msg[100];
}message;

int main()
{

key_t my_key;
int msg_id;
my_key=ftok("messagesend.c",66);
msg_id=msgget(my_key,0644|IPC_CREAT);
msgrcv(msg_id,&message,sizeof(message),1,0);
printf("received message is:%s\n",message.msg);
msgctl(msg_id,IPC_RMID,NULL);
return 0;
}
