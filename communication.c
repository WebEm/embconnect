#include<stdlib.h>
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include <sys/types.h>
  #include <sys/wait.h>


void handle_sigusr1(int sig)
{
printf("(HINT)remember that multiplication is repetatative addition\n");
}
int main(int argc,char *argtv[])
{

int pid=fork();

if(pid==-1)
{

return 1;
}

if(pid==0)
{
// child process
sleep(5);
kill(getpid(),SIGUSR1);
}
else
{

struct sigaction sa;
sa.sa_flags=SA_RESTART;// for scanf 
sa.sa_handler=&handle_sigusr1;
sigaction(SIGUSR1,&sa,NULL);
//parent process
int x;
printf("what is the result of 3 x 5:");
scanf("%d",&x);
if(x==15)
{
printf("right\n");
}
else
{
printf("wrong");
}
wait(NULL);
}

return 0;

}

