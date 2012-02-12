/*
 * graphicsbackgroundcontroller.cpp
 *
 *  Created on: 1.2.2012
 *      Author: akin
 */

#include "graphicsbackgroundcontroller.hpp"
#include <singleton>
#include <component/property/positionproperty.hpp>
#include <opengl>
#include <graphics/shader/shaderprogram.hpp>
#include <graphics/shader/uniform.hpp>
#include <graphics/rendertarget.hpp>

namespace bolt
{
const std::string GraphicsBackgroundController::KEY("graphicsbackgroundcontroller");

GraphicsBackgroundController::GraphicsBackgroundController( std::string name , bolt::StringSet& dependencies )
: bolt::Controller( name , false ),
  dependencies( dependencies ),
  program( NULL )
{
}

GraphicsBackgroundController::~GraphicsBackgroundController()
{
}

void GraphicsBackgroundController::setShaderProgram( ShaderProgram *app )
{
	program = app;

	resolution = app->getUniform("resolution");
	time = app->getUniform("time");
}

void GraphicsBackgroundController::getDependencies(bolt::StringSet & dep)
{
	dep = dependencies;
}

void GraphicsBackgroundController::initialize() throw (std::exception)
{
	float screen_vertices[12] = {
			-1.0f,	-1.0f,	0.0f,
			-1.0f,	1.0f,	0.0f,
			1.0f,	-1.0f,	0.0f,
			1.0f,	1.0f,	0.0f
	};

	uint screen_indices[4] = {
			0,1,2,3
	};

	vertexBuffer.set( 12*sizeof(float) , screen_vertices , Graphics::arrayBuffer , Graphics::gpu , Graphics::once );
	indexBuffer.set( 4*sizeof(unsigned int) , screen_indices , Graphics::elementArrayBuffer , Graphics::gpu , Graphics::once );
}

void GraphicsBackgroundController::start( bolt::ControllerNode& node )
{
	if( program != NULL )
	{
		// Render a QUAD using shader program..
		program->bind();
		GL_TEST_ERROR("start");


		float currentTime = myTime.getCurrentTime() * 0.001f;
		glm::vec2 windowResolution;

		VideoMode& videomode = Singleton<RenderTarget>::get()->getVideoMode();

		windowResolution.x = videomode.getWidth();
		windowResolution.y = videomode.getHeight();

		time->set( currentTime );
		resolution->set( windowResolution );

		glViewport( 0 , 0 , windowResolution.x , windowResolution.y );

	    glEnableClientState( GL_VERTEX_ARRAY );
	    glEnableClientState( GL_INDEX_ARRAY );

	    vertexBuffer.bind( Graphics::arrayBuffer );
	    indexBuffer.bind( Graphics::elementArrayBuffer );

	    // point to vertex data..
		glVertexPointer( 3, GL_FLOAT , 3*sizeof(float) , 0 );

		glDrawElements(GL_TRIANGLE_STRIP, 4 , GL_UNSIGNED_INT, 0 );
		GL_TEST_ERROR("end");
	}
}

} /* namespace bolt */
