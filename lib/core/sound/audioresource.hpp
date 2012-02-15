/*
 * audioresource.hpp
 *
 *  Created on: 5.2.2012
 *      Author: akin
 *
 *  FLAC
 *  	frequency:	[1Hz , 655 350Hz]
 *  	channels: 	[1 , 8]
 *  	bits:		[4, 32]
 *
 *  MP3
 *  	bitrate:	8, 16, 24, 32, 40, 48, 56, 64, 80, 96, 112, 128, 144, 160, 192, 224, 256, 320 kbit/s + vbr
 *  	frequency:	16, 22.05, 24, 32, 44.1, 48 kHz
 *  	channels: 	[1 , 8]
 *  	bits:		[4, 32]
 */

#ifndef AUDIORESOURCE_HPP_
#define AUDIORESOURCE_HPP_

#include <common>

namespace bolt
{

class AudioResource
{
protected:
	uint length;
	uint channels;
	uint frequency;
	uint bitsPerChannel;
public:
	AudioResource();
	virtual ~AudioResource();

	uint getLength();
	uint getFrequency();
	uint getChannels();
	uint getBitsPerChannel();

	virtual void seek( uint position );
	virtual uint read( void *data , uint byteLength );
	virtual uint position();
	virtual uint remaining();
};

} /* namespace bolt */
#endif /* AUDIORESOURCE_HPP_ */
