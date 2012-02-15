/*
 * applicationstate.cpp
 *
 *  Created on: 9.1.2012
 *      Author: akin
 */

#include "applicationstate.hpp"

namespace bolt
{

ApplicationState::ApplicationState()
{
}

ApplicationState::~ApplicationState()
{
}

void ApplicationState::processArg( int index , std::string argument )
{
}

void ApplicationState::processArgs( int argc , char *argv[] )
{
	for( int i = 0 ; i < argc ; ++i )
	{
		processArg(  i , std::string( argv[i]) );
	}
}

void ApplicationState::initialize()
{
}

void ApplicationState::suspend()
{
}

void ApplicationState::resume()
{
}

void ApplicationState::exit()
{
}

void ApplicationState::restart()
{
}

void ApplicationState::memoryWarning( uint level )
{
}

bool ApplicationState::willContinue()
{
	return false;
}

bool ApplicationState::willRestart()
{
	return false;
}

bool ApplicationState::willSaveState()
{
	return false;
}

void ApplicationState::saveState()
{
}

int ApplicationState::getProgramExitState()
{
	return 0;
}

} /* namespace bolt */
