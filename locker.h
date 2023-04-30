#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<pthread.h>
#include<exception>

using namespace std;


//1.互斥锁
class Locker
{
	public:
		//构造:初始化
		Locker()
		{
			if(pthread_mutex_init(&m_mutex, NULL)!=0)
			{
				throw std::exception();
			}
		}

		//析构：销毁
		~Locker()
		{
			pthread_mutex_destroy(&m_mutex);
		}		
		//加锁
		bool lock()
		{
			return pthread_mutex_lock(&m_mutex) == 0;
		}
		//解锁
		bool unlock()
		{
			return pthread_mutex_unlock(&m_mutex) == 0;
		}
		//获取私有属性
		pthread_mutex_t * get()
		{
			return &m_mutex;
		}

	private:
		pthread_mutex_t m_mutex;
};


//2.条件变量
class Cond
{
	public:
		//构造
		Cond()
		{
			if(pthread_cond_init(&m_cond, NULL) !=0)
			{
				throw std::exception();
			}
		}
		//析构
		~Cond()
		{
			pthread_cond_destroy(&m_cond);
		}

		//阻塞
		bool wait(pthread_mutex_t * m_mutex)
		{
			return pthread_cond_wait(&m_cond, m_mutex)==0;
		}		
		
		//设置超时时长
		bool timewait(pthread_mutex_t * m_mutex, struct timespec t)
		{
			return pthread_cond_timedwait(&m_cond, m_mutex, &t) == 0;
		}
		
		//解除一个线程的被阻塞状态
		bool signal()
		{
			return pthread_cond_signal(&m_cond) == 0;
		}
		//解除等待队列中所有线程的被阻塞状态
		bool broadcast()
		{
			return pthread_cond_broadcast(&m_cond) == 0;
		}
	private:
		pthread_cond_t m_cond;
};



//3.信号量
class Sem
{
	public:
		//默认构造
		Sem()
		{
			if(sem_init(&m_sem, 0, 0) != 0)
			{
				throw exception();
			}
		}
		//有参构造
		Sem(int val)
		{
			if(sem_init(&m_sem, 0, val) != 0)
			{
				throw exception();
			}
		}
		//析构
		~Sem()
		{
			sem_destroy(&m_sem);
		}
	
		//加锁（num--）
		bool wait()
		{
			return sem_wait(&m_sem)==0;
		}
		//解锁（num++）
		bool post()
		{
			return sem_post(&m_sem)==0;
		}
	private:
		sem_t m_sem;
};


