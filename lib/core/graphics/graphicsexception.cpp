/*
 * graphicsexception.cpp
 *
 *  Created on: 31.1.2012
 *      Author: akin
 */

#include "graphicsexception.hpp"

namespace bolt
{

GraphicsException::GraphicsException( std::string msg )
: std::runtime_error( msg )
{
}

GraphicsException::~GraphicsException() throw()
{
}

} /* namespace bolt */
