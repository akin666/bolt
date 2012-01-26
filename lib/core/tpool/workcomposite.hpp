/*
 * workcomposite.hpp
 *
 *  Created on: 26.1.2012
 *      Author: akin
 */

#ifndef WORKCOMPOSITE_HPP_
#define WORKCOMPOSITE_HPP_

#include <work>
#include <tque>

namespace bolt
{

class WorkComposite: public bolt::Work
{
protected:
	std::mutex mutex;
	WorkQue work;
	bool running;

	void setRunning( bool state );
	bool getRunning();
public:
	WorkComposite();
	virtual ~WorkComposite();

	virtual bool begin();
	virtual void run();
	virtual void end();

	bool isRunning();
	void push( Work *work );
};

} /* namespace bolt */
#endif /* WORKCOMPOSITE_HPP_ */
