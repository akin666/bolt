/*
 * applicationstate.hpp
 *
 *  Created on: 9.1.2012
 *      Author: akin
 */

#ifndef APPLICATIONSTATE_HPP_
#define APPLICATIONSTATE_HPP_

#include <string>

namespace bolt
{

class ApplicationState
{
protected:
	virtual void processArg( int index , std::string argument );
public:
	ApplicationState();
	virtual ~ApplicationState();

	void processArgs( int argc , char *argv[] );
	virtual bool initialize();

	virtual void suspend();
	virtual void resume();
	virtual void kill();
	virtual void restart();

	virtual bool willContinue();
	virtual bool willRestart();
	virtual bool willSaveState();
	virtual void saveState();

	virtual int getProgramExitState();
};

} /* namespace bolt */
#endif /* APPLICATIONSTATE_HPP_ */
