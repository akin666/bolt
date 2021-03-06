/*
 * glfwscreenrendertarget.hpp
 *
 *  Created on: 12.1.2012
 *      Author: akin
 */

#ifndef GLFWSCREENRENDERTARGET_HPP_
#define GLFWSCREENRENDERTARGET_HPP_

#include <graphics/rendertarget.hpp>

namespace bolt
{

class GLFWScreenRenderTarget : public RenderTarget
{
protected:
	bool initialized;
	bool fullscreen;
public:
	GLFWScreenRenderTarget();
	virtual ~GLFWScreenRenderTarget();

	virtual void bind() throw (GraphicsException);

	void setFullscreen( bool val );

	void initialize() throw (GraphicsException);
};

} /* namespace bolt */
#endif /* GLFWSCREENRENDERTARGET_HPP_ */
