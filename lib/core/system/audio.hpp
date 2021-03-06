/*
 * audio.hpp
 *
 *  Created on: 9.1.2012
 *      Author: akin
 *
 *      Current Audio is saved in Singleton class.
 *      getSingleton<Audio>()
 *      setSingleton<Audio>( Audio* )
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

	virtual void initialize();
	virtual void suspend();
	virtual void resume();

	virtual void setVolume( float vol );
	virtual float getVolume();
};

} /* namespace bolt */
#endif /* HARDWAREAUDIO_HPP_ */
