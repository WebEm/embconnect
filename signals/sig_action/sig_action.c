#include<stdio.h>
#include<unistd.h>
#include<signal.h>


void handlesignal(int signum);

int main()
{
void(*sighandlerreturn)(int);
struct sigaction mysigaction;

mysigaction.sa_handler=handlesignal;
sigemptyset(&mysigaction.sa_mask);
mysigaction.sa_flags=0;
sigaction(SIGINT,&mysigaction,NULL);

if(mysigaction.sa_handler==SIG_ERR)
{
perror("signal error:");
return 1;
}

mysigaction.sa_handler=handlesignal;
sigemptyset(&mysigaction.sa_mask);
mysigaction.sa_flags=0;
sigaction(SIGQUIT,&mysigaction,NULL);

if(mysigaction.sa_handler==SIG_ERR)
{
perror("signal error:");
return 1;
}

while(1)
{
printf("to terminate perform either one of folllowing two\n");
printf("1.open other terminal and issue command :kill %d\n",getpid());
printf("2.open other terminal and type ctrl +c 2 times\n");
sleep(10);
}
return 0;
}

void handlesignal(int signum)
{
switch(signum)
{
case SIGINT:
printf("\n you have entered CTRL+c \n");
printf("now reverting SIGINT signal to perfrom default action\n");
signal(SIGINT,SIG_DFL);
break;
case SIGQUIT:
printf("\n you entered CTRL+\\ \n");
break;
default:
printf("\n received signal number %d\n",signum);
break;
}
return;
}
