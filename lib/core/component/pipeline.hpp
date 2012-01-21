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
#include <tque>
#include "tools/componentnode.hpp"

namespace bolt
{
class Component;
class ComponentNode;
class Pipeline
{
private:
	unsigned int cycle;
	std::mutex mutex;

	NodeSet roots;
	NodeSet nonConcurrent;
	NodeSet concurrent;
	TQue<ComponentNode*> waitingQue;

	std::map<std::string,ComponentNode*> nodeNameMap;
	void addToRoot( ComponentNode *node );
public:
	Pipeline();
	virtual ~Pipeline();

	void setCycle( uint val );
	uint getCycle();

	void attach( Component *component ) throw (std::exception);
	void detach( Component *component ) throw (std::exception);

	void clear();

	// Run is the heart of the pipeline, it is essentially the main-loop.
	void run() throw (std::exception);
};

} /* namespace bolt */
#endif /* PIPELINE_HPP_ */

