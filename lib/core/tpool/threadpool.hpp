
#ifndef THREADPOOL_H_
#define THREADPOOL_H_

#include <work>
#include "worker"
#include "tque"
#include <exception>

namespace bolt
{

class ThreadPool
{
protected:
	TQue<Work*> data;
	Worker *workers;
	int worker_count;
public:
	ThreadPool();
	~ThreadPool();

	static unsigned int getHardwareThreadCount();

	bool initialize( unsigned int count ) throw (std::exception);

	void schedule( Work *work );

	int getWorkerCount();

	void kill();
};

} /* namespace ice */
#endif /* THREADPOOL_H_ */
