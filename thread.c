#include<stdio.h>

#include<stdlib.h>
#include<pthread.h>
//the sum computed by background thread
long long sum=0;
//thread function to genrete 0 to n
void *sum_runner(void* arg)
{
long long *limit_ptr=(long long*)arg;
long long limit=*limit_ptr;

for(long long i=0;i<=limit;i++)
{

sum+=i;
printf("%lld value is %lld\n",i,sum);
}
//SUm iS global variable so other threads can acess
pthread_exit(0);
}

int main(int argc,char **argv)

{
int fail;

long long limit=4;
//thread id
pthread_t tid;

fail=pthread_create(&tid,NULL,sum_runner,&limit);

if (fail) {
		printf("Thread creation failed %d\n", fail);
		return -1;
	}
//wait until thread is done
pthread_join(tid,NULL);
printf("\ntotal sum is %lld\n",sum);
}
