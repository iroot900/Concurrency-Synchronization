#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
using namespace std;

class ProCon
{
	public:
	
	ProCon(int size_):size(size_) {}

	void prod()
	{
		while(1)
		{
			unique_lock<mutex> lock(mu);
			space.wait(lock,[this]{return que.size()< size;});

			que.push(index++);
			cout<<"thread 1 prod: "<<index<<endl;
			goods.notify_one();
			lock.unlock();
		}
	}

	void cons() 
	{
		while(1)
		{
			unique_lock<mutex> lock(mu);
			goods.wait(lock,[this]{return !(que.empty());});
			cout<<"Thread 2 consume: "<<que.front()<<endl; que.pop();
			space.notify_one();
			lock.unlock();
		}
	}

	private:
		int size;
		int index=0;
		mutex mu;
		condition_variable goods;
		condition_variable space;
		queue<int> que;
};

void fun(ProCon & conPro)
{
	while(1)
	{
		conPro.prod();
	}
}

void fun2(ProCon & conPro)
{
	while(1)  conPro.cons();
}

int main()
{

	ProCon conPro(5);
	thread thd1(fun,ref(conPro));
	thread thd2(fun2,ref(conPro));
	thd1.join();
	thd2.join();
}
