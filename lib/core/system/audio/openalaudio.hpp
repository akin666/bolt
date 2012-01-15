/*
 * openalaudio.hpp
 *
 *  Created on: 9.1.2012
 *      Author: akin
 */

#ifndef OPENALAUDIO_HPP_
#define OPENALAUDIO_HPP_

#include <system/audio.hpp>
#include <openal>

namespace bolt
{

class OpenALAudio : public Audio
{
protected:
	ALCdevice *device;
	ALCcontext *context;
	int eax;
	int eaxEmulated;
	bool contextResumeSupported;

	void killContext();
	void killDevice();
	bool createContext();
	bool createDevice();
public:
	OpenALAudio();
	virtual ~OpenALAudio();

	virtual bool initialize();
	virtual bool suspend();
	virtual bool resume();

	virtual void setVolume( float vol );
	virtual float getVolume();
};

} /* namespace bolt */
#endif /* OPENALAUDIO_HPP_ */
