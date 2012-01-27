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
#include <data>
#include <graphics/shader/shader.hpp>

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

	// create aliases
	bolt::resource::link( "config" , "resources/config/default.cfg" );
	bolt::resource::link( "genericVertexShader" , "resources/shader/generic.vs" );
	bolt::resource::link( "genericFragmentShader" , "resources/shader/generic.fs" );

	// instruct to load
	bolt::resource::load( "config" );
	bolt::resource::load( "genericVertexShader" );
	bolt::resource::load( "genericFragmentShader" );

	bolt::createSingleton<SimpleRendererController>()->initialize();
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

	if( bolt::createSingleton<bolt::resource::Registry<bolt::TextData> >()->hasObject( "config" ))
	{
		bolt::TextData *dataunit = bolt::getSingleton<bolt::resource::Registry<bolt::TextData> >()->objectFor( "config" );

		if( dataunit != NULL )
		{
			LOG_OUT << dataunit->access() << std::endl;
		}
	}

	--times;

	// Bind default screen
	if( !bolt::getSingleton<bolt::Video>()->getRenderTarget().bind() )
	{
		return;
	}

	// Run the currently attached pipeline
	pipeline.run();

	// flip the screen..
	bolt::getSingleton<bolt::Video>()->flip();
}

