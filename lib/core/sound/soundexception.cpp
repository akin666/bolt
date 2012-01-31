/*
 * SoundException.cpp
 *
 *  Created on: 31.1.2012
 *      Author: akin
 */

#include "soundexception.hpp"

namespace bolt
{

SoundException::SoundException( std::string msg )
: std::runtime_error( msg )
{
}

SoundException::~SoundException() throw()
{
}

} /* namespace bolt */
