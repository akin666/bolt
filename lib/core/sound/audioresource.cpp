/*
 * audioresource.cpp
 *
 *  Created on: 5.2.2012
 *      Author: akin
 */

#include "audioresource.hpp"

namespace bolt
{

AudioResource::AudioResource()
 : length(0),
   channels(0),
   frequency(0),
   bitsPerChannel(0)
{
}

AudioResource::~AudioResource()
{
}

uint AudioResource::getLength()
{
	return channels;
}

uint AudioResource::getFrequency()
{
	return frequency;
}

uint AudioResource::getChannels()
{
	return channels;
}

uint AudioResource::getBitsPerChannel()
{
	return bitsPerChannel;
}

void AudioResource::seek(uint position) throw (std::exception)
{
}

uint AudioResource::read(void *data, uint byteLength) throw (std::exception)
{
	return 0;
}

uint AudioResource::position()
{
	return 0;
}

uint AudioResource::remaining()
{
	return 0;
}

} /* namespace bolt */
