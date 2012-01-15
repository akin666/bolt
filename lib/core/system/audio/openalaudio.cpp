/*
 * openalaudio.cpp
 *
 *  Created on: 9.1.2012
 *      Author: akin
 */

#include "openalaudio.hpp"
#include <cstdio>

namespace bolt
{

OpenALAudio::OpenALAudio()
: device( NULL ),
  context( NULL )
{
}

OpenALAudio::~OpenALAudio()
{
	killContext();
	killDevice();
}

void OpenALAudio::killContext()
{
	AL_TEST_ERROR("begin");
	if( context != NULL )
	{
		alcMakeContextCurrent( NULL );
		alcDestroyContext( context );
		context = NULL;
	}
	AL_TEST_ERROR("end");
}

void OpenALAudio::killDevice()
{
	AL_TEST_ERROR("begin");
	if( device != NULL )
	{
		alcCloseDevice( device );
		device = NULL;
	}
	AL_TEST_ERROR("end");
}

bool OpenALAudio::createContext()
{
	if( context != NULL ) return true;

	if( context == NULL )
	{
		context = alcCreateContext( device , NULL );

		if(  context == NULL )
		{
			LOG_ERROR << "Could not open OpenAL context." << std::endl;
			return false;
		}
	}
	return true;
}

bool OpenALAudio::createDevice()
{
	if( device != NULL ) return true;

	if( device == NULL )
	{
		device = alcOpenDevice( NULL ); // select the "preferred device"

		if( device == NULL )
		{
			LOG_ERROR << "Could not open OpenAL device." << std::endl;
			return false;
		}
	}
	return true;
}

bool OpenALAudio::initialize()
{
	if( device != NULL && context != NULL )
	{
		return true;
	}

	if( !createDevice() )
	{
		return false;
	}
	if( !createContext() )
	{
		return false;
	}

	// At this point context and device exists.
	alcMakeContextCurrent(context);

	// GL Data List logging.
	LOG_OUT << "Audio renderer Data: " << std::endl;
	LOG_OUT << " Vendor:" << alGetString(AL_VENDOR) << std::endl;
	LOG_OUT << " Renderer:" << alGetString(AL_RENDERER) << std::endl;
	LOG_OUT << " Version:" << alGetString(AL_VERSION) << std::endl;
	LOG_OUT << " Extensions:" << alGetString(AL_EXTENSIONS ) << std::endl;

	// Check for EAX n support
	// Extensions:EAX EAX2.0 EAX3.0 EAX4.0 EAX5.0 EAX3.0EMULATED EAX4.0EMULATED AL_EXT_OFFSET AL_EXT_LINEAR_DISTANCE AL_EXT_EXPONENT_DISTANCE
	char eaxTmp[32];

	eax = 0;
	if( alIsExtensionPresent( "EAX" ) )
	{
		eax = 1;
		for( int i = 2 ; i < 10 ; ++i )
		{
			sprintf( eaxTmp , "EAX%i.0" , i );
			if( alIsExtensionPresent( eaxTmp ) )
			{
				if( i > eax ) eax = i;
			}
		}

		eaxEmulated = 1;
		for( int i = 2 ; i < 10 ; ++i )
		{
			sprintf( eaxTmp , "EAX%i.0EMULATED" , i );
			if( alIsExtensionPresent( eaxTmp ) )
			{
				if( i > eaxEmulated ) eaxEmulated = i;
			}
		}
	}

	contextResumeSupported = true;

	AL_TEST_ERROR("end");

	return true;
}

bool OpenALAudio::suspend()
{
	if( device == NULL || context == NULL )
	{
		return true;
	}

	if( contextResumeSupported )
	{
		AL_TEST_ERROR("start");
		alcSuspendContext( context );
		AL_TEST_ERROR("end");

		return true;
	}

	// Suspending not supported, KILL context.
	killContext();

	return true;
}

bool OpenALAudio::resume()
{

	if( contextResumeSupported )
	{
		if( device == NULL || context == NULL )
		{
			return true;
		}

		AL_TEST_ERROR("start");
		alcProcessContext( context );
		AL_TEST_ERROR("end");

		return true;
	}

	// Suspending not supported, create context.
	return createContext();
}

void OpenALAudio::setVolume( float vol )
{
}

float OpenALAudio::getVolume()
{
	return 0;
}

} /* namespace bolt */
