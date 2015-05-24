#include <unistd.h>
#include <iostream>
#include <pthread.h>
using namespace std;

pthread_mutex_t llock=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t space=PTHREAD_COND_INITIALIZER;
pthread_cond_t goods=PTHREAD_COND_INITIALIZER;

int amount=0;
int wines[10];

static int i=0;
static int j=0;

void* producer(void *p)
{
	int n=(long) p;
	while(1)
	{
		pthread_mutex_lock(&llock);
		while(amount==10) pthread_cond_wait(&space,&llock);
		++amount;
		wines[i%10]=i+1;++i;
		cout<<"Producer "<<n<<" produced wine "<<i<<endl;
		pthread_cond_signal(&goods);
		pthread_mutex_unlock(&llock);
	}
}

void* consumer(void *p)
{
	int n=(long) p;
	while(1)
	{
		pthread_mutex_lock(&llock);
		while(amount==0) pthread_cond_wait(&goods,&llock);
		cout<<" Consumer "<<n<<" drink wine "<<wines[j%10]<<endl;
		++j;
		--amount;
		pthread_cond_signal(&space);
		pthread_mutex_unlock(&llock);
	}
}

int main()
{

	pthread_t pt;
	try
	{
		for(int i=0;i<10;i++)
		{
			if (pthread_create(&pt,NULL,producer,(void *)i)!=0)
				throw -1;
		}
		for(int i=0;i<10;i++)
			if(pthread_create(&pt,NULL,consumer,(void *)i)!=0)
				throw -1;
	}
	catch(int a)
	{
		cout<<"Fail creat threads!"<<endl;
	}
	usleep(500);
}
