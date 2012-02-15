/*
 * applicationstate.hpp
 *
 *  Created on: 9.1.2012
 *      Author: akin
 */

#ifndef APPLICATIONSTATE_HPP_
#define APPLICATIONSTATE_HPP_

#include <string>
#include <common>

namespace bolt
{

class ApplicationState
{
protected:
	virtual void processArg( int index , std::string argument );
public:
	ApplicationState();
	virtual ~ApplicationState();

	// Video or Audio not yet initialized at this phase.
	// Workers initialized already.
	// Set video mode & audio mode in initialize/process args.
	void processArgs( int argc , char *argv[] );
	virtual void initialize();

	// Commands.
	virtual void suspend(); // suspend the application, going into background.
	virtual void resume();	// resume the application state
	virtual void exit();	// kill instruction
	virtual void restart(); // instruct the application to do hard restart

	virtual void memoryWarning( uint level = 0 ); // running out of memory.

	virtual void saveState(); // save config etc.

	// Questions
	virtual bool willContinue();
	virtual bool willRestart();
	virtual bool willSaveState();

	virtual int getProgramExitState();
};

} /* namespace bolt */
#endif /* APPLICATIONSTATE_HPP_ */
