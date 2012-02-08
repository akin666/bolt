/*
 * testapplication.hpp
 *
 *  Created on: 12.1.2012
 *      Author: akin
 */

#ifndef TESTAPPLICATION_HPP_
#define TESTAPPLICATION_HPP_

#include <application/application.hpp>
#include <component/pipeline.hpp>

class TestApplication: public bolt::Application
{
protected:
	int state;

	bool initialized;

	virtual void processArg( int index , std::string argument );
public:
	TestApplication();
	virtual ~TestApplication();

	virtual void initialize() throw (std::exception);
	virtual void suspend();
	virtual void resume();
	virtual void exit();
	virtual void restart();

	virtual bool willContinue();
	virtual bool willRestart();
	virtual bool willSaveState();
	virtual void saveState();

	virtual void run();
};

#endif /* TESTAPPLICATION_HPP_ */


