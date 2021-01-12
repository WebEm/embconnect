#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void handlesignals(int signum);

int main()
{

void (*sighandlerinterrupt)(int);
void (*sighandlerquit)(int);
void (*sighandlerreturn)(int);

sighandlerinterrupt=sighandlerquit=handlesignals;
sighandlerreturn=signal(SIGINT,sighandlerinterrupt);
if(sighandlerreturn==SIG_ERR)
{
perror("signal error:");
return 1;
}

sighandlerreturn=signal(SIGQUIT,sighandlerquit);

if(sighandlerreturn==SIG_ERR)
{
perror("signal error:");
return 1;
}
while(1)
{

printf("\n to terminate this program perform the following:\n");

printf("1.open another terminal\n");
printf("2.issue command :kill %d or issue CTRL+C 2 times(second time it terminates)\n",getpid());
sleep(10);
}

return 0;
}

void handlesignals(int signum)
{
switch(signum)
{
case SIGINT:
printf("\n you pressd  CTRL+C \n ");
printf("now reverting SIGINT signals to default actipn\n");
signal(SIGINT,SIG_DFL);
break;
case SIGQUIT:
printf("\n you pressed CTRL+\\ \n");
break;
default:
printf("\n received signal number %d\n",signum);
break;
}
return;
}
