/*
 * backgroundrenderer.cpp
 *
 *  Created on: 1.2.2012
 *      Author: akin
 */

#include "backgroundrenderer.hpp"
#include <singleton>
#include <component/common/positionproperty.hpp>
#include <component/common/fencecontroller.hpp>
#include <opengl>
#include <graphics/shader/shaderprogram.hpp>
#include <component/common/fencecontroller.hpp>

namespace bolt
{
const std::string BackgroundRenderer::KEY("backgroundrenderer");

BackgroundRenderer::BackgroundRenderer()
: bolt::Controller( KEY , false ),
  program( NULL )
{
}

BackgroundRenderer::~BackgroundRenderer()
{
}

void BackgroundRenderer::setShaderProgram( ShaderProgram *app )
{
	program = app;
}

void BackgroundRenderer::getDependencies(bolt::StringSet & dep)
{
	dep.clear();
	dep.insert( bolt::FenceController::LOGIC );
}

void BackgroundRenderer::initialize() throw (std::exception)
{
	float screen_vertices[12] = {
			-1.0f,	-1.0f,	0.0f,
			-1.0f,	1.0f,	0.0f,
			1.0f,	-1.0f,	0.0f,
			1.0f,	1.0f,	0.0f
	};

	unsigned int screen_indices[4] = {
			0,1,2,3
	};

	vertexBuffer.set( 12*sizeof(float) , screen_vertices , Graphics::gpu , Graphics::once );
	indexBuffer.set( 4*sizeof(unsigned int) , screen_indices , Graphics::gpu , Graphics::once );
}

void BackgroundRenderer::start( bolt::ControllerNode& node )
{
	if( program != NULL )
	{
		// Render a QUAD using shader program..
		program->bind();

		glDisable( GL_DEPTH_TEST );

	    glLoadIdentity();

	    vertexBuffer.bind( Graphics::arrayBuffer );
	    indexBuffer.bind( Graphics::elementArrayBuffer );

	    // point to vertex data..
		glVertexPointer( 3, GL_FLOAT , 3*sizeof(float) , 0 );

		glDrawElements(GL_TRIANGLE_STRIP, 4 , GL_UNSIGNED_INT, 0 );
	}
}

} /* namespace bolt */
