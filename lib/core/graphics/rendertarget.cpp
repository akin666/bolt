/*
 * rendertarget.cpp
 *
 *  Created on: 11.1.2012
 *      Author: akin
 */

#include "rendertarget.hpp"
#include <singleton>

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

void RenderTarget::bind() throw (GraphicsException)
{
	Singleton<RenderTarget>::set( this );
}

} /* namespace bolt */
