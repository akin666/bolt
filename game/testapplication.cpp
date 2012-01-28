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
#include <graphics/shader/shaderprogram.hpp>

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
	bolt::resource::link( "GenericShader" );

	// create shaderprogram registry.
	bolt::createSingleton<bolt::resource::Registry<bolt::ShaderProgram> >();

	// instruct to load
	bolt::resource::load( "config" );
	bolt::resource::load( "genericVertexShader" );
	bolt::resource::load( "genericFragmentShader" );

	bolt::createSingleton<SimpleRendererController>()->initialize();
//	bolt::Singleton<NameComponent>::create()->initialize();

	pipeline.attach( bolt::Singleton<SimpleRendererController>::get() );

	initialized = true;
	shaderProgramLoaded = false;

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

	if( !shaderProgramLoaded )
	{
		if( bolt::resource::hasObject<bolt::Shader>( "genericVertexShader" ) &&
			bolt::resource::hasObject<bolt::Shader>( "genericFragmentShader" )  )
		{
			// It has both Shaders.. Create em, Link em and create program!
			bolt::ShaderProgram *program = new bolt::ShaderProgram;

			bolt::Shader *vertex = bolt::resource::getObject<bolt::Shader>( "genericVertexShader" );
			bolt::Shader *fragment = bolt::resource::getObject<bolt::Shader>( "genericFragmentShader" );

			vertex->load();
			fragment->load();

			vertex->compile();
			fragment->compile();

			program->attach( vertex );
			program->attach( fragment );

			program->link();

			if( program->linked() )
			{
				bolt::resource::setObject<bolt::ShaderProgram>( "GenericShader" , program );

				shaderProgramLoaded = true;

				LOG_OUT << "Shader program is loaded! " << std::endl;
			}

			if( !shaderProgramLoaded )
			{
				LOG_OUT << "Failed to load Shader program! " << std::endl;
			}
		}
	}


	if( bolt::createSingleton<bolt::resource::Registry<bolt::TextData> >()->hasObject( "config" ))
	{
		bolt::TextData *dataunit = bolt::getSingleton<bolt::resource::Registry<bolt::TextData> >()->getObject( "config" );

		if( dataunit != NULL )
		{
			// LOG_OUT << dataunit->access() << std::endl;
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

