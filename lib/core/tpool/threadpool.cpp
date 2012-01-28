
#include <threadpool>
#include <thread>
#include <stdexcept>

namespace bolt
{

unsigned int ThreadPool::getHardwareThreadCount()
{
	return std::thread::hardware_concurrency();
}

ThreadPool::ThreadPool()
: workers(NULL)
{
}

ThreadPool::~ThreadPool()
{
}

void ThreadPool::initialize( unsigned int count ) throw (std::exception)
{
	if( workers == NULL )
	{
		worker_count = count;
		workers = new Worker[worker_count];

		for( int i = count - 1 ; i >= 0 ; --i )
		{
			workers[i].init( data );
		}
	}
	else
	{
		throw std::runtime_error("ThreadPool Workers already initialized!.");
	}
}

void ThreadPool::kill()
{
	if( workers != NULL )
	{
		for( int i = worker_count - 1 ; i >= 0 ; --i )
		{
			workers[i].terminate();
		}
		delete[] workers;
		workers = NULL;
	}
}

int ThreadPool::getWorkerCount()
{
	return worker_count;
}

void ThreadPool::schedule( Work *work )
{
	data.push( work );
}

}


