/*
 * glfwscreenrendertarget.cpp
 *
 *  Created on: 12.1.2012
 *      Author: akin
 */

#include "glfwscreenrendertarget.hpp"
#include <log>
#include <opengl>

namespace bolt
{

GLFWScreenRenderTarget::GLFWScreenRenderTarget()
: initialized(false),
  fullscreen(false)
{
	mode.setWidth( 800 );
	mode.setHeight( 600 );
	mode.setRedBits( 8 );
	mode.setGreenBits( 8 );
	mode.setBlueBits( 8 );
	mode.setAlphaBits( 8 );
	mode.setDepthBits( 24 );
	mode.setStencilBits( 8 );
}

GLFWScreenRenderTarget::~GLFWScreenRenderTarget()
{
}

bool GLFWScreenRenderTarget::bind()
{
	GL_TEST_ERROR("begin");

	glBindFramebuffer( GL_FRAMEBUFFER , 0 );

	GL_TEST_ERROR("end");

	return true;
}

void GLFWScreenRenderTarget::setFullscreen( bool val )
{
	if( !initialized )
	{
		fullscreen = val;
		return;
	}

	// ehm.. initialized already, so, we need to switch?
}

bool GLFWScreenRenderTarget::initialize()
{
	if( initialized ) return true;

	if (glfwOpenWindow(
			mode.getWidth(),
			mode.getHeight(),
			mode.getRedBits(),
			mode.getGreenBits(),
			mode.getBlueBits(),
			mode.getAlphaBits(),
			mode.getDepthBits(),
			mode.getStencilBits(),
			( fullscreen ? GLFW_FULLSCREEN : GLFW_WINDOW ) ) != GL_TRUE )
	{
		LOG_ERROR << "Failed to open window." << std::endl;
		return false;
	}

	initialized = true;

	return true;
}

} /* namespace bolt */
