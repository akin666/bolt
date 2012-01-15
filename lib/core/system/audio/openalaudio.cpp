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
: device( NULL ),
  context( NULL )
{
}

OpenALAudio::~OpenALAudio()
{
	AL_TEST_ERROR("begin");
	if( context != NULL )
	{
		alcMakeContextCurrent( NULL );
		alcDestroyContext( context );
		context = NULL;
	}
	if( device != NULL )
	{
		alcCloseDevice( device );
		device = NULL;
	}
	AL_TEST_ERROR("begin");
}

bool OpenALAudio::initialize()
{
	if( device != NULL && context != NULL )
	{
		return true;
	}

	// Device Initialization
	if( device == NULL )
	{
		device = alcOpenDevice( NULL ); // select the "preferred device"

		if( device == NULL )
		{
			LOG_ERROR << "Could not open OpenAL device." << std::endl;
			return false;
		}
	}

	// At this point device is not null
	if( context == NULL )
	{
		context = alcCreateContext( device , NULL );

		if(  context == NULL )
		{
			LOG_ERROR << "Could not open OpenAL context." << std::endl;
			return false;
		}
	}

	// At this point context is not null.
	alcMakeContextCurrent(context);

	// Check for EAX 2.0 support
	eax2 = alIsExtensionPresent("EAX2.0");
	if( eax2 )
	{
		LOG_OUT << "EAX2 OpenAL available." << std::endl;
	}
	else
	{
		LOG_OUT << "EAX2 OpenAL not available." << std::endl;
	}

	// Generate Buffers
	AL_TEST_ERROR("initialize end");

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
