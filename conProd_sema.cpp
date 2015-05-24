#include <unistd.h>
#include <iostream>
#include <semaphore.h>
#include <pthread.h>
using namespace std;

sem_t prod;
sem_t con;
sem_t mmutex;

int wines[10];

static int i=0;
static int j=0;

void* producer(void *p)
{
	int n=(long) p;
	while(1)
	{
		sem_wait(&prod);
		sem_wait(&mmutex);
		wines[i%10]=i+1;++i;
		cout<<"Producer "<<n<<" produced wine "<<i<<endl;
		sem_post(&mmutex);
		sem_post(&con);
	}
}

void* consumer(void *p)
{
	int n=(long) p;
	while(1)
	{
		sem_wait(&con);
		sem_wait(&mmutex);
		cout<<" Consumer "<<n<<" drink wine "<<wines[j%10]<<endl;
		++j;
		sem_post(&mmutex);
		sem_post(&prod);
	}
}

int main()
{
	sem_init(&prod,0,10);
	sem_init(&con,0,0);
	sem_init(&mmutex,0,1);

	pthread_t pt;
	try
	{
		for(int i=0;i<3;i++)
		{
			if (pthread_create(&pt,NULL,producer,(void *)i)!=0)
				throw -1;
		}
		for(int i=0;i<3;i++)
			if(pthread_create(&pt,NULL,consumer,(void *)i)!=0)
				throw -1;
	}
	catch(int a)
	{
		cout<<"Fail creat threads!"<<endl;
	}
	usleep(200);
}
