/*
 * glfwscreenrendertarget.cpp
 *
 *  Created on: 12.1.2012
 *      Author: akin
 */

#include "glfwscreenrendertarget.hpp"
#include <log>
#include <opengl>
#include <stdexcept>

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

void GLFWScreenRenderTarget::bind() throw (GraphicsException)
{
	// all rendertargets should call this thing.
	RenderTarget::bind();

	GL_TEST_ERROR("begin");
	glBindFramebuffer( GL_FRAMEBUFFER , 0 );
	GL_TEST_ERROR("end");
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

void GLFWScreenRenderTarget::initialize() throw (GraphicsException)
{
	if( initialized )
	{
		throw GraphicsException("GLFWScreenRenderTarget already initialized!.");
	}

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
		throw GraphicsException("GLFWScreenRenderTarget Failed to open window!.");
	}

	initialized = true;
}

} /* namespace bolt */
