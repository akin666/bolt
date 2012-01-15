
#ifndef TQUE_H_
#define TQUE_H_

#include <iostream>
#include <deque>
#include <thread>

namespace bolt
{

template <class tclass>
class TQue
{
protected:
	std::mutex mutex;
	std::condition_variable condition;
	std::deque< tclass > data;
	unsigned int data_count;
public:
	TQue() : data_count(0) {}
	virtual ~TQue(){}

	// blocking, but pushes as fast as possible
	void push( tclass work );

	// blocking.
	tclass pop();
};

template <class tclass>
void TQue<tclass>::push( tclass work )
{
	std::lock_guard<std::mutex> lock(mutex);

	data.push_back( work );
	++data_count;

	condition.notify_one();
}

template <class tclass>
tclass TQue<tclass>::pop()
{
	std::unique_lock<std::mutex> lock(mutex);

	while( data.empty() )
	{
		condition.wait(lock);
	}

	tclass popped = data.front();
	data.pop_front();
	--data_count;

	return popped;
}

} /* namespace ice */
#endif /* TQUE_H_ */
