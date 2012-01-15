/*
 * testapplication.cpp
 *
 *  Created on: 12.1.2012
 *      Author: akin
 */

#include "testapplication.hpp"
#include <log>
#include <singleton>
#include <system/video.hpp>

TestApplication::TestApplication()
{
}

TestApplication::~TestApplication()
{
}

void TestApplication::processArg( int index , std::string argument )
{
}

bool TestApplication::initialize()
{
	times = 100;

	return true;
}

void TestApplication::suspend()
{
}

void TestApplication::resume()
{
}

void TestApplication::kill()
{
}

void TestApplication::restart()
{
}

bool TestApplication::willContinue()
{
	return times > 0;
}

bool TestApplication::willRestart()
{
	return false;
}

bool TestApplication::willSaveState()
{
	return false;
}

void TestApplication::saveState()
{
}

void TestApplication::run()
{
//	LOG_OUT << "Hi!\nTestApp. At: " << times << std::endl;
	--times;

	// Bind default screen
	if( !bolt::Singleton<bolt::Video>::get()->getRenderTarget().bind() )
	{
		return;
	}

	// flup teh screen..
	bolt::Singleton<bolt::Video>::get()->flip();
}

