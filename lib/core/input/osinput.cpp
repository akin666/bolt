/*
 * OSInput.cpp
 *
 *  Created on: 15.2.2012
 *      Author: akin
 */

#include "osinput.hpp"

namespace bolt
{

OSInput::OSInput()
{
}

OSInput::~OSInput()
{
}

bool OSInput::handleClose()
{
	return true;
}

void OSInput::handleMemoryWarning()
{
}

bool OSInput::handleMinimize()
{
	return true;
}

bool OSInput::handleMaximize()
{
	return true;
}

void OSInput::handleRefresh()
{
}

bool OSInput::handleResize( int width , int height )
{
	return true;
}

} /* namespace bolt */
