/*
 * audio.cpp
 *
 *  Created on: 9.1.2012
 *      Author: akin
 */

#include "audio.hpp"
#include <stdexcept>

namespace bolt
{

Audio::Audio()
{
}

Audio::~Audio()
{
}

void Audio::initialize() throw (std::exception)
{
	throw std::runtime_error("default audio initialize!.");
}

void Audio::suspend() throw (std::exception)
{
	throw std::runtime_error("default audio suspend!.");
}

void Audio::resume() throw (std::exception)
{
	throw std::runtime_error("default audio resume!.");
}

void Audio::setVolume( float vol )
{
}

float Audio::getVolume()
{
	return 1.0f;
}

} /* namespace bolt */
