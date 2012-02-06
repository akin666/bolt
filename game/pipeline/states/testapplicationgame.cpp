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

#include <component/pipeline.hpp>
#include <component/common/positionproperty.hpp>

#include <resource/dictionary.hpp>
#include <resource/registry.hpp>
#include <graphics/shader/shaderprogram.hpp>

#include "../simplerenderercontroller.hpp"

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

	bolt::Pipeline *pipeline = bolt::getSingleton<bolt::Pipeline>();

	SimpleRendererController *renderer = new SimpleRendererController();
	renderer->initialize();
	pipeline->attach( renderer );

	renderer->attach( box );

	bolt::PositionProperty::Data& boxData = bolt::getSingleton<bolt::PositionProperty>()->get( box );

	boxData.position.x = 0.0f;
	boxData.position.y = 0.0f;
	boxData.position.z = 0.0f;

	times = 500;

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

