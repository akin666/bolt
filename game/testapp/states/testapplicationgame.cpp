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
#include <component/common/graphicsdebugcontroller.hpp>

#include <resource/dictionary.hpp>
#include <resource/registry.hpp>
#include <graphics/shader/shaderprogram.hpp>
#include <component/common/fencecontroller.hpp>
#include <component/common/graphicsbackgroundcontroller.hpp>

#include <cmath>

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

	bolt::StringSet depSet;
	depSet.insert( bolt::FenceController::LOGIC );
	depSet.insert( bolt::GraphicsBackgroundController::KEY );

	bolt::GraphicsDebugController *renderer = new bolt::GraphicsDebugController( bolt::GraphicsDebugController::KEY , depSet );
	renderer->initialize();
	pipeline->attach( renderer );

	renderer->attach( box );
	renderer->attach( box2 );

	bolt::PositionProperty::Data& boxData = bolt::getSingleton<bolt::PositionProperty>()->get( box.getId() );
	bolt::PositionProperty::Data& box2Data = bolt::getSingleton<bolt::PositionProperty>()->get( box2.getId() );

	boxData.position.x = 0.0f;
	boxData.position.y = 5.0f;
	boxData.position.z = -10.0f;

	box2Data.position.x = 10.0f;
	box2Data.position.y = 5.0f;
	box2Data.position.z = -10.0f;

	times = 1500;

	bolt::setSingleton<bolt::Mouse>( this );

	initialized = true;
	right = false;
	left = false;
}

void TestApplicationGame::start( bolt::ControllerNode& node )
{
	if( --times <= 0 )
	{
		LOG_OUT << "TestApplicationGame exit" << std::endl;
		bolt::getSingleton<bolt::Application>()->exit();
	}

	bolt::PositionProperty::Data& boxData = bolt::getSingleton<bolt::PositionProperty>()->get( box.getId() );
	bolt::PositionProperty::Data& box2Data = bolt::getSingleton<bolt::PositionProperty>()->get( box2.getId() );

	// Go through mouse events.
	MouseEvent *event;
	while( (event = mouse.pop( bolt::TQue<MouseEvent*>::RETURN_NULL_IF_EMPTY )) != NULL )
	{
		switch( event->type )
		{
			case MouseEvent::MOVE :
			{
				if( right )
				{
					// 2
					box2Data.position.x += event->x *0.05f;
					box2Data.position.y += event->y *0.05f;
				}
				if( left )
				{
					// 1
					boxData.position.x += event->x *0.05f;
					boxData.position.y += event->y *0.05f;
				}
				break;
			}
			case MouseEvent::BUTTON :
			{
				switch( event->button )
				{
				case bolt::LEFT : left = event->state > 0.5f; break;
				case bolt::RIGHT : right = event->state > 0.5f; break;
				default: break;
				}
				break;
			}
			case MouseEvent::WHEEL :
			{
				break;
			}
		}

		// recycle.
		freeMouse.push( event );
	}

	// Modify box position data..
//	boxData.position.x = sin( times * 0.05f ) * 2.0f;
//	boxData.position.y = cos( times * 0.05f ) * 2.0f;
	boxData.rotation = glm::gtc::quaternion::rotate( boxData.rotation , -2.5f , glm::vec3( 1,0,1 ) );

//	box2Data.position.x = -sin( times * 0.1f ) * 2.0f;
	box2Data.position.z = -cos( times * 0.1f ) * 2.0f - 10;
	box2Data.rotation = glm::gtc::quaternion::rotate( box2Data.rotation , -2.5f , glm::vec3( 0,1,0 ) );
}

// Mous
void TestApplicationGame::handleMouseMove( float x , float y )
{
	MouseEvent *e = freeMouse.pop( bolt::TQue<MouseEvent*>::RETURN_NULL_IF_EMPTY );
	if( e == NULL )
	{
		e = new MouseEvent;
	}

	e->type = MouseEvent::MOVE;
	e->x = x;
	e->y = y;
	mouse.push( e );
}

void TestApplicationGame::handleMouseButton( bolt::Button button , float state )
{
	MouseEvent *e = freeMouse.pop( bolt::TQue<MouseEvent*>::RETURN_NULL_IF_EMPTY );
	if( e == NULL )
	{
		e = new MouseEvent;
	}

	e->type = MouseEvent::BUTTON;
	e->button = button;
	e->state = state;
	mouse.push( e );
}

void TestApplicationGame::handleMouseWheel( float val )
{
	MouseEvent *e = freeMouse.pop( bolt::TQue<MouseEvent*>::RETURN_NULL_IF_EMPTY );
	if( e == NULL )
	{
		e = new MouseEvent;
	}

	e->type = MouseEvent::WHEEL;
	e->wheel = val;
	mouse.push( e );
}


