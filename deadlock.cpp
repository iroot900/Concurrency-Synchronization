#include <unistd.h>
#include <iostream>
#include <pthread.h>
using namespace std;
pthread_mutex_t lok=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lok2=PTHREAD_MUTEX_INITIALIZER;

void* task1(void* p) 
{
	int i=(long) p;
	pthread_mutex_lock(&lok);
	cout<<"Thread "<<i<<" get resource 1(lok1) waiting for resource 2(lok2)"<<endl;
	usleep(100);
	pthread_mutex_lock(&lok2);
	pthread_mutex_unlock(&lok);
	pthread_mutex_unlock(&lok2);
}

void* task2(void*p) 
{
	int i=(long) p;
	pthread_mutex_lock(&lok2);
	usleep(100);
	cout<<"Thread "<<i<<" get resource 2(lok2) waiting for resource 1(lok1)"<<endl;
	pthread_mutex_lock(&lok);
	pthread_mutex_unlock(&lok);
	pthread_mutex_unlock(&lok2);
}
int main(){
	pthread_t id,id2;
	pthread_create(&id,NULL,task1,(void*)1);
	pthread_create(&id2,NULL,task2,(void*)2);
	pthread_join(id2,NULL);
	pthread_join(id,NULL);
	cout<<endl;
}
