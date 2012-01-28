/*
 * glfwvideo.hpp
 *
 *  Created on: 9.1.2012
 *      Author: akin
 */

#ifndef GLFWVIDEO_HPP_
#define GLFWVIDEO_HPP_

#include <system/video.hpp>
#include "glfwscreenrendertarget.hpp"

namespace bolt
{

class GLFWVideo : public Video
{
protected:
	float dpi;
	bool windowed;
	bool cursorVisible;
	int major;
	int minor;
	std::string title;

	GLFWScreenRenderTarget rendertarget;
public:
	GLFWVideo();
	virtual ~GLFWVideo();

	virtual float getDPI();
	virtual bool isWindowed();

	virtual void setDPI( float val );
	virtual void setWindowed( bool val );

	// OGL: 3.2 => Major: 3 Minor: 2
	virtual void setMajorVersion( int v );
	virtual void setMinorVersion( int v );

	virtual bool isCursorVisible();
	virtual void setCursorVisible( bool val );

	virtual void initialize() throw (std::exception);

	virtual void setTitle( std::string head );
	virtual std::string getTitle();

	virtual void apply( const VideoMode& mode ) throw (std::exception);

	virtual void listVideoModes( std::vector<VideoMode>& modes ) const;

	virtual RenderTarget& getRenderTarget();

	virtual void flip();
};

} /* namespace bolt */
#endif /* GLFWVIDEO_HPP_ */
