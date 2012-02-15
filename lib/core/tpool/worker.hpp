
#ifndef WORKER_H_
#define WORKER_H_

#include <tque>
#include <thread>
#include <work>

namespace bolt
{
class Worker
{
protected:
	// shared queue with other workers.
	WorkQue *queu;
	std::thread *thread;

	std::mutex mutex;
	std::condition_variable condition;
	bool going;
public:
	Worker();
	~Worker();

	void init( WorkQue& wqueu );

	void operator()();

	void terminate();
};

} /* namespace ice */
#endif /* WORKER_H_ */
