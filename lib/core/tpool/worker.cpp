
#include <work>
#include "worker.hpp"
#include <iostream>
#include <stdexcept>


namespace bolt
{

Worker::Worker()
: queu( NULL ),
  thread(NULL)
{
}

Worker::~Worker()
{
	delete thread;
	thread = NULL;
}

void Worker::init( TQue<Work*>& wqueu )  throw (std::exception)
{
	if( thread == NULL )
	{
		// This Sync of worker thread, and initializer, ensures that
		// the worker really is initialized after exiting this function.
		// ! If this is not done, the workers probably will get initialized
		// much later..
		std::unique_lock<std::mutex> lock(mutex);

		if( thread != NULL )
		{
			delete thread;
		}

		queu = &wqueu;

		going = false;
		thread = new std::thread( std::ref(*this) );

		// Ensure that the function returns _after_ the thread has fully initialized
		while( !going )
		{
			condition.wait(lock);
		}
	}
	else
	{
		throw std::runtime_error("Thread is already running.");
	}
}

void Worker::operator()()
{
	// Thread initialization/volatile/sync block
	{
		std::lock_guard<std::mutex> lock(mutex);

		// Do initialization here!

		// Initialization done.
		going = true;
		condition.notify_one();
	}

	Work *current;
	while( going )
	{
		// Pop front. or wait something to pop.
		current = queu->pop();
		if( current != NULL )
		{
			// Is the work ready to be done?
			if( !current->begin() )
			{
				// No? push it back, continue.
				queu->push( current );
				continue;
			}
			current->run();
			current->end();
		}
	}

	// Thread dying/sync block
	{
		std::lock_guard<std::mutex> lock(mutex);

		// Do KILLING here.

		// Initialization done.
		going = true;
		condition.notify_one();
	}
}

void Worker::terminate()
{
	if( going && thread != NULL )
	{
		std::unique_lock<std::mutex> lock(mutex);
		going = false;

		while( !going )
		{
			condition.wait(lock);
		}

		delete thread;
		thread = NULL;
	}
}

}
