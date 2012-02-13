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

#include <pipeline/pipeline.hpp>
#include <component/property/positionproperty.hpp>
#include <pipeline/controller/graphicsdebugcontroller.hpp>

#include <resource/dictionary.hpp>
#include <resource/registry.hpp>
#include <graphics/shader/shaderprogram.hpp>
#include <pipeline/controller/fencecontroller.hpp>
#include <pipeline/controller/graphicsbackgroundcontroller.hpp>

#include <component/property/cameraproperty.hpp>
#include <graphics/rendertarget.hpp>

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

	bolt::Position& boxData = bolt::getSingleton<bolt::PositionProperty>()->get( box.getId() );
	bolt::Position& box2Data = bolt::getSingleton<bolt::PositionProperty>()->get( box2.getId() );

	boxData.point.x = 0.0f;
	boxData.point.y = 5.0f;
	boxData.point.z = -10.0f;

	box2Data.point.x = 10.0f;
	box2Data.point.y = 5.0f;
	box2Data.point.z = 10.0f;



	// Camera
	bolt::Camera& cameraData = bolt::createSingleton<bolt::CameraProperty>()->get( camera.getId() );
	bolt::Position& cameraPositionData = bolt::getSingleton<bolt::PositionProperty>()->get( camera.getId() );

	cameraPositionData.point.z = 10.0f;

	bolt::createSingleton<bolt::CameraProperty>()->setCurrent( camera );

	glm::vec2 windowResolution;

	bolt::VideoMode& videomode = bolt::Singleton<bolt::RenderTarget>::get()->getVideoMode();

	windowResolution.x = videomode.getWidth();
	windowResolution.y = videomode.getHeight();

	const float aspectRatio = windowResolution.y/windowResolution.x;

	cameraData.lense = glm::frustum(
			-1.0f,
			 1.0f,
			-aspectRatio,
			 aspectRatio,
			1.0f,
			40.0f
			);

	times = 1500;

	bolt::setSingleton<bolt::Mouse>( this );

	initialized = true;
	right = false;
	left = false;
	mid = false;
}

void TestApplicationGame::start( bolt::ControllerNode& node )
{
	if( --times <= 0 )
	{
		LOG_OUT << "TestApplicationGame exit" << std::endl;
		bolt::getSingleton<bolt::Application>()->exit();
	}

	bolt::Position& boxData = bolt::getSingleton<bolt::PositionProperty>()->get( box.getId() );
	bolt::Position& box2Data = bolt::getSingleton<bolt::PositionProperty>()->get( box2.getId() );
	bolt::Position& cameraPositionData = bolt::getSingleton<bolt::PositionProperty>()->get( camera.getId() );

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
					box2Data.point.x -= event->x *0.05f;
					box2Data.point.y -= event->y *0.05f;
				}
				if( left )
				{
					cameraPositionData.orientation = glm::gtc::quaternion::rotate( cameraPositionData.orientation , 1.0f , glm::vec3( event->x,event->y,0 ) );
				}
				if( mid )
				{
					// 1
					cameraPositionData.point.x += event->x * 0.05f;
					cameraPositionData.point.y += event->y * 0.05f;
				}

				break;
			}
			case MouseEvent::BUTTON :
			{
				switch( event->button )
				{
					case bolt::LEFT : left = event->state > 0.5f; break;
					case bolt::RIGHT : right = event->state > 0.5f; break;
					case bolt::MIDDLE : mid = event->state > 0.5f; break;
					default: break;
				}
				break;
			}
			case MouseEvent::WHEEL :
			{
				cameraPositionData.point.z += event->wheel * 0.5f;

				break;
			}
		}

		// recycle.
		freeMouse.push( event );
	}

	// Modify box position data..
//	boxData.position.x = sin( times * 0.05f ) * 2.0f;
//	boxData.position.y = cos( times * 0.05f ) * 2.0f;
	boxData.orientation = glm::gtc::quaternion::rotate( boxData.orientation , -2.5f , glm::vec3( 1,0,1 ) );

//	box2Data.position.x = -sin( times * 0.1f ) * 2.0f;
	box2Data.point.z = -cos( times * 0.1f ) * 2.0f - 10;
	box2Data.orientation = glm::gtc::quaternion::rotate( box2Data.orientation , -2.5f , glm::vec3( 0,1,0 ) );


	LOG_OUT << "CamPos: " << cameraPositionData.point.z << std::endl;
	LOG_OUT << "boxData p: " << boxData.point.z << std::endl;
	LOG_OUT << "box2Data p: " << box2Data.point.z << std::endl;
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


