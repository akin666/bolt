
#ifndef WORKER_H_
#define WORKER_H_

#include <tque>
#include <thread>
#include <exception>

namespace bolt
{
class WorkQueu;

class Worker
{
protected:
	TQue<Work*> *queu;
	std::thread *thread;

	std::mutex mutex;
	std::condition_variable condition;
	bool going;
public:
	Worker();
	~Worker();

	void init( TQue<Work*>& wqueu ) throw (std::exception);

	void operator()();

	void terminate();
};

} /* namespace ice */
#endif /* WORKER_H_ */
