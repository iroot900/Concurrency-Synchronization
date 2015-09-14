#include <iostream>
#include <pthread.h>
#include <getopt.h>
#include <time.h>
using namespace std;

int SIZE=5000;
int NUM=2;

long long  **A,**B,**C;
int sum=0;

void init(long long **&mat,bool result=false)
{
	int i=0,j=0,val=0;
	mat= new long long*[SIZE];
	for(int i=0;i<SIZE;i++)
	{
		mat[i]=new long long [SIZE];
		for(int j=0;j<SIZE;j++)
		{
			if(!result)
			mat[i][j]=++val;
			else 
			mat[i][j]=0;
		}
	}
}

void print(long long **mat)
{
	for(int i=0;i<SIZE;i++)
	{
		for(int j=0;j<SIZE;j++)
		{
			cout<<mat[i][j]<<" ";
		}
		cout<<endl;
	}
}

void* multiply (void *p)
{
	int col=(long)p;
	col=col*(SIZE/NUM);
	int end=0;
	if((long)p==NUM-1) end=SIZE;
	else   end=col+SIZE/NUM;
	for(int i=col;i<end;i++)
	{
		for(int j=0;j<SIZE;j++)
		{
			C[i][j]+=A[i][j]*B[j][i];
		}
	}
}

int main(int argc,char** argv)
{
	int c;
	while((c=getopt(argc,argv,"ht:s:"))!=-1)
	{
		switch(c)
		{
			case 'h':
				cout<<"-t :number of threads, default 2"<<endl
					<<"-s :size of matrix,deafult 5000x5000"<<endl;
				return 0;
				break;
			case 's':
				SIZE=atoi(optarg);
				break;
			case 't':
				NUM=atoi(optarg);
				break;
			case '?':
				break;
			default:
				cout<<"wrong input"<<endl;
				return -1;
		}
	}
	clock_t start=clock();
	init(A);
	init(B);
	init(C,true);
//  print(A),print(B);	
	pthread_t pt[NUM];
	for(int i=0;i<NUM;i++)
	{
		pthread_create(&pt[i],NULL,multiply,(void *)i);
	}

	for(int i=0;i<NUM;i++)
	{
		pthread_join(pt[i],NULL);
	}
//	print(C); if your matrix size is not so big, do it. Otherwise, simply just don't;
	cout<<"For size "<<SIZE<<"x"<<SIZE<<" running time with "<<NUM<<" threads is "<<clock()-start<<endl;
	return 0;
}
