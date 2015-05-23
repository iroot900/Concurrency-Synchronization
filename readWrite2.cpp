#include <unistd.h>
#include <iostream>
#include <pthread.h>
using namespace std;
pthread_rwlock_t rwlock=PTHREAD_RWLOCK_INITIALIZER;
pthread_mutex_t llock=PTHREAD_MUTEX_INITIALIZER;//synchronize IO. (no need, just for see it clear)
string article;

void* reader(void *p)
{
	int i=(long)p;
	while(1)
	{	
		pthread_rwlock_rdlock(&rwlock);
		pthread_mutex_lock(&llock);
		cout<<"  Reader: "<<i<<" is reading "<<article<<endl;
		pthread_mutex_unlock(&llock);
		pthread_rwlock_unlock(&rwlock);
		if(article.size()>40) return NULL;
	}
}

void* writer(void *p)
{
	int i=(long)p;
	while(1)
	{
		pthread_rwlock_wrlock(&rwlock);
		article+=string(1,i+'0');
		cout<<"Writer: "<<i<<" is writing "<<article<<endl;
		pthread_rwlock_unlock(&rwlock);
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
