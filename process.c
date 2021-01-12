

//fork is used to create child
/*
fork internally calls clone function
fork system call when called it will return two values
one is >0 that is for parent
one==0 that is child
with this identity we can spot which is child and whis is parenent
it is not mandatory that sparent should be executed first always
child can also get executiom time
*/

#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<stdlib.h>

void dosomework(char *name)
{
const int  NUM_TIMES=2;
for(int i=0;i<NUM_TIMES;i++)
{
sleep(rand()%4);
printf("done pass %d for %s\n",i,name);
}

}





int main(void)
{
int value = 20;
int ret;
ret=fork();
// creating child process
//this will now throw two return values one >0 and other==0
//>0 is the parent equal to 0 is child

if(ret==0)
{

printf("\n this is child");
printf("\n my pid is %d\n",getpid());
dosomework("child");

}

if(ret>0)
{
printf("\n this is parent");
printf("\n my pid is %d\n",getpid());
printf("\nParent waiting for child to exit\n");
wait(0); //wait for child to exit
printf("Child exited\n");
}


return 0;
}

