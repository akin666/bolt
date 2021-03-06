/*
 * rendertarget.hpp
 *
 *  Created on: 11.1.2012
 *      Author: akin
 */

#ifndef RENDERTARGET_HPP_
#define RENDERTARGET_HPP_

#include "videomode.hpp"
#include "graphicsexception.hpp"

namespace bolt
{

class RenderTarget
{
protected:
	VideoMode mode;
public:
	RenderTarget();
	RenderTarget( VideoMode& mode );
	virtual ~RenderTarget();

	VideoMode& getVideoMode();

	virtual void bind() throw (GraphicsException);
};

} /* namespace bolt */
#endif /* RENDERTARGET_HPP_ */
