/*
 * audio.cpp
 *
 *  Created on: 9.1.2012
 *      Author: akin
 */

#include "audio.hpp"

namespace bolt
{

Audio::Audio()
{
}

Audio::~Audio()
{
}

bool Audio::initialize()
{
	return false;
}

bool Audio::suspend()
{
	return false;
}

bool Audio::resume()
{
	return false;
}

void Audio::setVolume( float vol )
{
}

float Audio::getVolume()
{
	return 1.0f;
}

} /* namespace bolt */
