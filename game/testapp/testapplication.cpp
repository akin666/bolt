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
#include <system/audio.hpp>
#include <component/common/fencecontroller.hpp>
#include <component/pipeline.hpp>
#include "states/loadcontroller.hpp"
#include "states/testapplicationgame.hpp"
#include <config/fileconfig.hpp>

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

	// Input configuration
	input.initialize();
	bolt::setSingleton<bolt::Keyboard>( &input );
	bolt::setSingleton<bolt::Mouse>( &input );

	// Load Configuration.
	bolt::FileConfig *config = new bolt::FileConfig( "resources/config/default.cfg" );
	bolt::setSingleton<bolt::Config>( config );

	/////////////
	// Setup video
	/////////////
	bolt::Video *video = bolt::getSingleton<bolt::Video>();
	bolt::VideoMode mode;

	mode.setWidth( config->get("screen_width" , 800) );
	mode.setHeight( config->get("screen_height" ,600) );
	mode.setRedBits( config->get("screen_red_bits" ,8) );
	mode.setGreenBits( config->get("screen_green_bits" ,8) );
	mode.setBlueBits( config->get("screen_blue_bits" ,8) );
	mode.setAlphaBits( config->get("screen_alpha_bits" ,8) );
	mode.setDepthBits( config->get("screen_depth_bits" ,24) );
	mode.setStencilBits( config->get("screen_stencil_bits" ,8) );

	video->setTitle( config->get("screen_title" , std::string("Bolt is BOLT") ) );
	video->setWindowed( config->get("screen_windowed" , true ) );
	video->apply( mode );


	/////////////
	// Setup audio
	/////////////
	bolt::Audio *audio = bolt::getSingleton<bolt::Audio>();


	// Setup rest.
	state = 1;

	bolt::Pipeline *pipeline = bolt::getSingleton<bolt::Pipeline>();

	// Create dependency list for fence.
	bolt::StringSet fenceDependencies;
	fenceDependencies.insert( LoadController::KEY );
	fenceDependencies.insert( TestApplicationGame::KEY );

	bolt::FenceController *logicFence = new bolt::FenceController( bolt::FenceController::LOGIC , fenceDependencies );

	LoadController *loader = new LoadController();

	logicFence->initialize();
	loader->initialize();

	pipeline->attach( logicFence );
	pipeline->attach( loader );
	pipeline->attach( &input );

	initialized = true;
}

void TestApplication::suspend()
{
}

void TestApplication::resume()
{
}

void TestApplication::exit()
{
	state = -1;
}

void TestApplication::restart()
{
}

bool TestApplication::willContinue()
{
	return state > 0;
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

	// Bind default screen
	bolt::getSingleton<bolt::Video>()->getRenderTarget().bind();

	// Run the currently attached pipeline
	bolt::getSingleton<bolt::Pipeline>()->run();

	// flip the screen..
	bolt::getSingleton<bolt::Video>()->flip();
}

