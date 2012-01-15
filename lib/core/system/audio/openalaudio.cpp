/*
 * openalaudio.cpp
 *
 *  Created on: 9.1.2012
 *      Author: akin
 */

#include "openalaudio.hpp"

namespace bolt
{

OpenALAudio::OpenALAudio()
{
}

OpenALAudio::~OpenALAudio()
{
}

bool OpenALAudio::initialize()
{
	return true;
}

bool OpenALAudio::suspend()
{
	return true;
}

bool OpenALAudio::resume()
{
	return true;
}

void OpenALAudio::setVolume(float vol)
{
}

float OpenALAudio::getVolume()
{
	return 0;
}

} /* namespace bolt */
