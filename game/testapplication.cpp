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
#include <component/common/fencecontroller.hpp>
#include <component/pipeline.hpp>
#include "pipeline/simplerenderercontroller.hpp"
#include "pipeline/states/loadcontroller.hpp"
#include "pipeline/states/testapplicationgame.hpp"

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

void TestApplication::initialize() throw (std::exception)
{
	if( initialized )
	{
		return;
	}

	times = 100;

	bolt::Pipeline *pipeline = bolt::getSingleton<bolt::Pipeline>();

	// Create dependency list for fence.
	bolt::StringSet fenceDependencies;
	fenceDependencies.insert( LoadController::KEY );
	fenceDependencies.insert( TestApplicationGame::KEY );

	bolt::FenceController *logicFence = new bolt::FenceController( bolt::FenceController::LOGIC , fenceDependencies );

	SimpleRendererController *renderer = new SimpleRendererController();
	LoadController *loader = new LoadController();

	logicFence->initialize();
	loader->initialize();
	renderer->initialize();

	pipeline->attach( logicFence );
	pipeline->attach( loader );
	pipeline->attach( renderer );

	initialized = true;
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
	/*
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
				bolt::resource::link( "GenericShader" );
				bolt::resource::setObject<bolt::ShaderProgram>( "GenericShader" , program );

				shaderProgramLoaded = true;

				LOG_OUT << "Shader program is loaded! " << std::endl;
			}
			else
			{
				delete program;
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
	*/

	--times;

	// Bind default screen
	bolt::getSingleton<bolt::Video>()->getRenderTarget().bind();

	// Run the currently attached pipeline
	bolt::getSingleton<bolt::Pipeline>()->run();

	// flip the screen..
	bolt::getSingleton<bolt::Video>()->flip();
}

