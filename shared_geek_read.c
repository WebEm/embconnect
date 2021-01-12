
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>




int main(int argc,char *argv[])
{

int shmid,retval;

void *shm=NULL;
char *s;



shmid=shmget((key_t)123456789,6,IPC_CREAT|0666);
if(shmid<0)


{

printf("\n failed to creat an id");
exit(1);
}
printf("id for created shared memory %d\n",shmid);
shm=shmat(shmid,NULL,0);
s=(char*)shm;
if(s==NULL)
{
printf("\ncould not able to attach the process to shared memory\n");

}

printf("\n sent message is%s\n",s);



retval=shmdt(s);

if(retval<0)

{
printf("\n detached properly");
return 0;
}
}
