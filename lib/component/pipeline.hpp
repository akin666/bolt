/*
 * pipeline.hpp
 *
 *  Created on: 16.1.2012
 *      Author: akin
 */

#ifndef PIPELINE_HPP_
#define PIPELINE_HPP_

#include <deque>
#include <exception>
#include <thread>
#include "tools/componentnet.hpp"

namespace bolt
{
class Component;
class ComponentNode;
class Pipeline
{
private:
	ComponentNet net;
	std::mutex mutex;

	std::deque<ComponentNode*> temp;
	std::deque<ComponentNode*> nonConcurrent;
	std::deque<ComponentNode*> concurrent;
	TQue<ComponentNode*> waitingQue;
public:
	Pipeline();
	virtual ~Pipeline();

	void attach( Component *component ) throw (std::exception);

	// Run is the heart of the pipeline, it is essentially the main-loop.
	void run() throw (std::exception);
};

} /* namespace bolt */
#endif /* PIPELINE_HPP_ */

