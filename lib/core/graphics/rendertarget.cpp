/*
 * rendertarget.cpp
 *
 *  Created on: 11.1.2012
 *      Author: akin
 */

#include "rendertarget.hpp"

namespace bolt
{

RenderTarget::RenderTarget()
{
}

RenderTarget::RenderTarget( VideoMode& mode )
: mode( mode )
{
}

RenderTarget::~RenderTarget()
{
}

VideoMode& RenderTarget::getVideoMode()
{
	return mode;
}

bool RenderTarget::bind()
{
	return false;
}

} /* namespace bolt */
