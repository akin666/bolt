/*
 * videomode.cpp
 *
 *  Created on: 10.1.2012
 *      Author: akin
 */

#include "videomode.hpp"

namespace bolt
{

VideoMode::VideoMode()
: width( 0 ),
  height( 0 ),
  redBits( 0 ),
  greenBits( 0 ),
  blueBits( 0 ),
  alphaBits( 0 ),
  stencilBits( 0 ),
  depthBits( 0 )
{
}

VideoMode::VideoMode( const VideoMode& other )
{
	operator=(other);
}

VideoMode::~VideoMode()
{
}

VideoMode& VideoMode::operator = ( const VideoMode& other )
{
	width = other.width;
	height = other.height;
	redBits = other.redBits;
	greenBits = other.greenBits;
	blueBits = other.blueBits;
	alphaBits = other.alphaBits;
	stencilBits = other.stencilBits;
	depthBits = other.depthBits;

	return *this;
}

int VideoMode::getBlueBits() const
{
	return blueBits;
}

int VideoMode::getDepthBits() const
{
	return depthBits;
}

int VideoMode::getGreenBits() const
{
	return greenBits;
}

int VideoMode::getHeight() const
{
	return height;
}

int VideoMode::getRedBits() const
{
	return redBits;
}

int VideoMode::getAlphaBits() const
{
	return alphaBits;
}

int VideoMode::getStencilBits() const
{
	return stencilBits;
}

int VideoMode::getWidth() const
{
	return width;
}

void VideoMode::setBlueBits(int blueBits)
{
	this->blueBits = blueBits;
}

void VideoMode::setDepthBits(int depthBits)
{
	this->depthBits = depthBits;
}

void VideoMode::setGreenBits(int greenBits)
{
	this->greenBits = greenBits;
}

void VideoMode::setHeight(int height)
{
	this->height = height;
}

void VideoMode::setRedBits(int redBits)
{
	this->redBits = redBits;
}

void VideoMode::setAlphaBits(int alphaBits)
{
	this->alphaBits = alphaBits;
}

void VideoMode::setStencilBits(int stencilBits)
{
	this->stencilBits = stencilBits;
}

void VideoMode::setWidth(int width)
{
	this->width = width;
}

} /* namespace bolt */
