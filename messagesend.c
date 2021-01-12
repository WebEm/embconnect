#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/types.h>
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
message.msg_type=1;
printf("write message:");
fgets(message.msg,100,stdin);
msgsnd(msg_id,&message,sizeof(message),0);
printf("sent message is:%s\n",message.msg);
}
