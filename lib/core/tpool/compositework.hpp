/*
 * CompositeWork.hpp
 *
 *  Created on: 26.1.2012
 *      Author: akin
 */

#ifndef COMPOSITEWORK_HPP_
#define COMPOSITEWORK_HPP_

#include <work>
#include <tque>

namespace bolt
{

class CompositeWork: public bolt::Work
{
protected:
	std::mutex mutex;
	WorkQue work;
	bool running;

	void setRunning( bool state );
	bool getRunning();
public:
	CompositeWork();
	virtual ~CompositeWork();

	virtual bool begin();
	virtual void run();
	virtual void end();

	bool isRunning();
	void push( Work *work );
};

} /* namespace bolt */
#endif /* COMPOSITEWORK_HPP_ */
