/*
 * testapplicationgame.cpp
 *
 *  Created on: 29.1.2012
 *      Author: akin
 */

#include "testapplicationgame.hpp"
#include <singleton>
#include <log>
#include <application/application.hpp>

#include <resource/dictionary.hpp>
#include <resource/registry.hpp>
#include <graphics/shader/shaderprogram.hpp>

const std::string TestApplicationGame::KEY("testapplication");

TestApplicationGame::TestApplicationGame()
: bolt::Controller( KEY , true ),
  initialized( false ),
  shaderProgram( NULL )
{
}

TestApplicationGame::~TestApplicationGame()
{
}

void TestApplicationGame::initialize() throw (std::exception)
{
	try
	{
		shaderProgram = bolt::resource::getObject<bolt::ShaderProgram>( "GenericShader" );
	}
	catch( std::exception& e )
	{
		// Shit..
		LOG_ERROR << "Failed to get the generic shader! " << e.what() << std::endl;
		shaderProgram = NULL;
	}

	times = 40;

	initialized = true;
}

void TestApplicationGame::start( bolt::ControllerNode& node )
{
	if( --times <= 0 )
	{
		LOG_OUT << "TestApplicationGame exit" << std::endl;
		bolt::getSingleton<bolt::Application>()->exit();
	}
}

