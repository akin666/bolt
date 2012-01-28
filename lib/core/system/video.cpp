/*
 * video.cpp
 *
 *  Created on: 9.1.2012
 *      Author: akin
 */

#include "video.hpp"
#include <stdexcept>

namespace bolt
{

Video::Video()
{
}

Video::~Video()
{
}

float Video::getDPI()
{
	return 0.0f;
}

bool Video::isFullscreen()
{
	return !isWindowed();
}

bool Video::isWindowed()
{
	return false;
}

void Video::setDPI(float val)
{
}

void Video::setFullscreen( bool val )
{
	setWindowed( !val );
}

void Video::setWindowed(bool val)
{
}

bool Video::isCursorVisible()
{
	return false;
}

void Video::setCursorVisible( bool val )
{
}

void Video::setMajorVersion(int v)
{
}

void Video::setMinorVersion(int v)
{
}

void Video::initialize() throw (std::exception)
{
	throw std::runtime_error("Default video initializer.");
}

void Video::setTitle(std::string head)
{
}

std::string Video::getTitle()
{
	return "";
}

void Video::apply( const VideoMode& mode ) throw (std::exception)
{
	throw std::runtime_error("Default video apply.");
}

void Video::listVideoModes( std::vector<VideoMode>& modes ) const
{
}

void Video::flip()
{
}

} /* namespace bolt */
