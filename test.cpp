#include<iostream>
#include "locker.h"
#include<pthread.h>
#include<time.h>

//实例化互斥锁对象
locker test_lock;
using namespace std;

void * func1(void * args)
{
	while(1)
	{
		test_lock.lock();
		cout << "hello"<< endl;
		sleep(rand()%3);

		test_lock.unlock();
		sleep(rand()%3); 
	}
	pthread_exit(NULL);
}
void * func2(void * args)
{
	while(1)
	{
		test_lock.lock();
		cout << "world"<< endl;
		sleep(rand()%3);

		test_lock.unlock();
		sleep(rand()%3); 
	}
	pthread_exit(NULL);
}
int main()
{
	int ret;
	pthread_t thread1;
	pthread_t thread2;
	srand(time(NULL));


	ret = pthread_create(&thread1, NULL, func1, NULL);

	if(ret != 0)
	{
		cout<<"error:"<< endl;
		return -1;
	}
	
	ret = pthread_create(&thread2, NULL, func2,NULL);
	if(ret!=0)
	{
		cout << "error"<<endl;
		return -1;
	}
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	

	return 0;
}
