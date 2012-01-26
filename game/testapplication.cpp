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
#include "pipeline/simplerenderercontroller.hpp"
#include <resource/loader.hpp>
#include <resource/dictionary.hpp>
#include <resource/registry.hpp>
#include <resource/data/bytedata.hpp>

TestApplication::TestApplication()
: initialized( false )
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
	if( initialized )
	{
		return true;
	}

	times = 100;

	bolt::Singleton<bolt::resource::Dictionary>::create()->add( "config" , "resources/config/default.cfg" );
	bolt::Singleton<bolt::resource::Loader>::get()->load( "config" );

	bolt::Singleton<SimpleRendererController>::create()->initialize();
//	bolt::Singleton<NameComponent>::create()->initialize();

	pipeline.attach( bolt::Singleton<SimpleRendererController>::get() );

	initialized = true;

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

	if( bolt::Singleton<bolt::resource::Registry<bolt::resource::ByteData> >::create()->hasObject( "config" ))
	{
		bolt::resource::ByteData *dataunit = bolt::Singleton<bolt::resource::Registry<bolt::resource::ByteData> >::create()->objectFor( "config" );

		if( dataunit != NULL )
		{
			LOG_OUT << dataunit->accessData() << std::endl;
		}
	}

	--times;

	// Bind default screen
	if( !bolt::Singleton<bolt::Video>::get()->getRenderTarget().bind() )
	{
		return;
	}

	// Run the currently attached pipeline
	pipeline.run();

	// flip the screen..
	bolt::Singleton<bolt::Video>::get()->flip();
}

