/*
 * audio.hpp
 *
 *  Created on: 9.1.2012
 *      Author: akin
 *
 *      Current Audio is saved in Singleton class.
 *      Singleton<Audio>::get()
 *      Singleton<Audio>::set( Audio* )
 */

#ifndef AUDIO_HPP_
#define AUDIO_HPP_

namespace bolt
{

class Audio
{
public:
	Audio();
	virtual ~Audio();

	virtual bool initialize();
	virtual bool suspend();
	virtual bool resume();

	virtual void setVolume( float vol );
	virtual float getVolume();
};

} /* namespace bolt */
#endif /* HARDWAREAUDIO_HPP_ */
