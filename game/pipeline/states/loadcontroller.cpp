/*
 * loadcontroller.cpp
 *
 *  Created on: 29.1.2012
 *      Author: akin
 */

#include "loadcontroller.hpp"
#include <singleton>
#include <log>
#include <component/pipeline.hpp>

#include <resource/loader.hpp>
#include <resource/dictionary.hpp>
#include <resource/registry.hpp>
#include <data>
#include <graphics/shader/shader.hpp>
#include <graphics/shader/shaderprogram.hpp>

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

void LoadController::initialize() throw (std::exception)
{
	bolt::resource::link( "config" , "resources/config/default.cfg" );
	bolt::resource::link( "genericVertexShader" , "resources/shader/generic.vs" );
	bolt::resource::link( "genericFragmentShader" , "resources/shader/generic.fs" );

	// create shaderprogram registry.
	bolt::createSingleton<bolt::resource::Registry<bolt::ShaderProgram> >();

	// instruct to load
	bolt::resource::load( "config" );
	bolt::resource::load( "genericVertexShader" );
	bolt::resource::load( "genericFragmentShader" );

	initialized = true;
	loadComplete = false;
}

void LoadController::start( bolt::ControllerNode& node )
{
	LOG_OUT << "Load phase " << std::endl;
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

	if( loadComplete )
	{
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