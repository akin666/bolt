/*
 * loadcontroller.cpp
 *
 *  Created on: 29.1.2012
 *      Author: akin
 */

#include "loadcontroller.hpp"
#include <singleton>
#include <log>
#include <pipeline/pipeline.hpp>

#include <resource/loader.hpp>
#include <resource/dictionary.hpp>
#include <resource/registry.hpp>
#include <data>
#include <graphics/shader/shader.hpp>
#include <graphics/shader/shaderprogram.hpp>

#include <pipeline/controller/graphicsbackgroundcontroller.hpp>
#include <pipeline/controller/fencecontroller.hpp>

#include "testapplicationgame.hpp"

const std::string LoadController::KEY("loader");

LoadController::LoadController()
: bolt::Controller( KEY , true ),
  initialized( false )
{
}

LoadController::~LoadController()
{
}

void LoadController::initialize()
{
	bolt::resource::link( "config" , "resources/config/default.cfg" );

	initialized = true;

	// create shaderprogram registry.
	bolt::createSingleton<bolt::resource::Registry<bolt::ShaderProgram> >();

	// instruct to load
	bolt::resource::load( "config" );

	bolt::resource::link( "genericVertexShader" , "resources/shader/test/blank.vs" );
	bolt::resource::link( "genericFragmentShader" , "resources/shader/test/blank.fs" );
	bolt::resource::load( "genericVertexShader" );
	bolt::resource::load( "genericFragmentShader" );
	loadComplete = false;

	// Load debugcube shaders
	bolt::resource::link( "debugVertexShader" , "resources/shader/debug/blank.vs" );
	bolt::resource::link( "debugFragmentShader" , "resources/shader/debug/blank.fs" );
	bolt::resource::load( "debugVertexShader" );
	bolt::resource::load( "debugFragmentShader" );
	loadDebugComplete = false;

	// Load the BGRenderer & shaders to it..
	bolt::resource::link( "backgroundVS" , "resources/shader/background/screen.vs" );
	bolt::resource::link( "backgroundFS" , "resources/shader/background/starfield.fs" );
	bolt::resource::load( "backgroundVS" );
	bolt::resource::load( "backgroundFS" );
	loadBGComplete = false;
}

void LoadController::start( bolt::ControllerNode& node )
{
	if( !loadComplete )
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

				loadComplete = true;

				LOG_OUT << "Shader program is loaded! " << std::endl;
			}
			else
			{
				delete program;
			}
		}
	}

	if( !loadDebugComplete )
	{
		if( bolt::resource::hasObject<bolt::Shader>( "debugVertexShader" ) &&
			bolt::resource::hasObject<bolt::Shader>( "debugFragmentShader" )  )
		{
			// It has both Shaders.. Create em, Link em and create program!
			bolt::ShaderProgram *program = new bolt::ShaderProgram;

			bolt::Shader *vertex = bolt::resource::getObject<bolt::Shader>( "debugVertexShader" );
			bolt::Shader *fragment = bolt::resource::getObject<bolt::Shader>( "debugFragmentShader" );

			vertex->load();
			fragment->load();

			vertex->compile();
			fragment->compile();

			program->attach( vertex );
			program->attach( fragment );

			program->link();

			if( program->linked() )
			{
				bolt::resource::link( "DebugShader" );
				bolt::resource::setObject<bolt::ShaderProgram>( "DebugShader" , program );

				loadDebugComplete = true;

				LOG_OUT << "DebugShader program is loaded! " << std::endl;
			}
			else
			{
				delete program;
			}
		}
	}

	if( !loadBGComplete )
	{
		if( bolt::resource::hasObject<bolt::Shader>( "backgroundVS" ) &&
			bolt::resource::hasObject<bolt::Shader>( "backgroundFS" )  )
		{
			// It has both Shaders.. Create em, Link em and create program!
			bolt::ShaderProgram *program = new bolt::ShaderProgram;

			bolt::Shader *vertex = bolt::resource::getObject<bolt::Shader>( "backgroundVS" );
			bolt::Shader *fragment = bolt::resource::getObject<bolt::Shader>( "backgroundFS" );

			vertex->load();
			fragment->load();

			vertex->compile();
			fragment->compile();

			program->attach( vertex );
			program->attach( fragment );

			program->link();

			if( program->linked() )
			{
				bolt::resource::link( "BackgroundShader" );
				bolt::resource::setObject<bolt::ShaderProgram>( "BackgroundShader" , program );

				loadBGComplete = true;

				// Create BackgroundRenderer & attach it also. here.
				bolt::StringSet strings;

				strings.insert( bolt::FenceController::LOGIC );
				bolt::GraphicsBackgroundController *bgrender = new bolt::GraphicsBackgroundController( bolt::GraphicsBackgroundController::KEY , strings );
				bolt::setSingleton<bolt::GraphicsBackgroundController>( bgrender );

				bgrender->initialize();
				bgrender->setShaderProgram( program );

				// attach the backgroundrenderer to the pipeline.
				bolt::getSingleton<bolt::Pipeline>()->attach( bgrender );

				LOG_OUT << "BackgroundShader Shader program is loaded! " << std::endl;
			}
			else
			{
				delete program;
			}
		}
	}

	/*
	if( bolt::createSingleton<bolt::resource::Registry<bolt::TextData> >()->hasObject( "config" ))
	{
		bolt::TextData *dataunit = bolt::getSingleton<bolt::resource::Registry<bolt::TextData> >()->getObject( "config" );

		if( dataunit != NULL )
		{
			LOG_OUT << dataunit->access() << std::endl;
		}
	}
	*/

	if( loadComplete && loadBGComplete && loadDebugComplete )
	{
		LOG_OUT << "Load phase Completed." << std::endl;
		// TestApplication!
		TestApplicationGame *game = new TestApplicationGame();

		try
		{
			game->initialize();

			// Swap the loader & game in pipeline.
			bolt::Pipeline *pipeline = bolt::getSingleton<bolt::Pipeline>();

			pipeline->detach( this );

			pipeline->attach( game );
		}
		catch( std::exception& e )
		{
			LOG_ERROR << "Blody game failed to initialize!, Harakiri is NOGO!" << e.what() << std::endl;
		}
	}
}
