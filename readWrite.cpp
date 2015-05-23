#include <unistd.h>
#include <iostream>
#include <pthread.h>
using namespace std;
pthread_mutex_t rwlock=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t llock=PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t stdlock=PTHREAD_MUTEX_INITIALIZER;//since many readers are reading, the std IO will be messing up ;
int readers=0;
string article;

void* reader(void *p)
{
	int i=(long)p;
	while(1)
	{
		pthread_mutex_lock(&llock);
		++readers;
		if(readers==1)	{ pthread_mutex_lock(&rwlock); }// first one try to get rwlock,if not then, wait, all other reader's can't get in coz llock;
		pthread_mutex_unlock(&llock);
	
		pthread_mutex_lock(&stdlock);
		cout<<"  Reader: "<<i<<" is reading "<<article<<endl;
		pthread_mutex_unlock(&stdlock);
		
		pthread_mutex_lock(&llock);
		--readers;
		if(readers==0)
			pthread_mutex_unlock(&rwlock);	
		pthread_mutex_unlock(&llock);
		if(article.size()>40) return NULL;
		usleep(200);
		// if comment out the above line, serious starving for readers
	}
}

void* writer(void *p)
{
	int i=(long)p;
	while(1)
	{
		pthread_mutex_lock(&rwlock);
		article+=string(1,i+'0');
		cout<<"Writer: "<<i<<" is writing "<<article<<endl;
		pthread_mutex_unlock(&rwlock);
		if(article.size()>40) return NULL;
	}
}

int main()
{
	pthread_t pt;
	try
	{
		for(int i=0;i<10;i++)
		{
			if (pthread_create(&pt,NULL,reader,(void *)i)!=0)
				throw -1;
		}
		for(int i=0;i<10;i++)
			if(pthread_create(&pt,NULL,writer,(void *)i)!=0)
				throw -1;
	}
	catch(int a)
	{
		cout<<"Fail creat threads!"<<endl;
	}
	pthread_exit(NULL);
}
