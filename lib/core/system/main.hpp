/*
 * main.hpp
 *
 *  Created on: 9.1.2012
 *      Author: akin
 *
 * int main( int argc , char *argv[] ) {
 *      Main< MyApplication , GLFWVideo , OpenALAudio > app;
 *      app.initialize( argc , argv );
 *      return app.run();
 * }
 */

#ifndef MAIN_HPP_
#define MAIN_HPP_

#include <singleton>
#include <application/application.hpp>
#include "audio.hpp"
#include "video.hpp"

#include <log.hpp>
#include <event/eventhandler.hpp>
#include <exception/exceptionhandler.hpp>
#include <input/keyboardinputhandler.hpp>
#include <input/mouseinputhandler.hpp>
#include <input/joystickinputhandler.hpp>
#include <threadpool>

namespace bolt
{

template < class ApplicationPolicy , class VideoPolicy , class AudioPolicy >
class Main
{
protected:
	ApplicationPolicy application;
	VideoPolicy video;
	AudioPolicy audio;
	ThreadPool pool;
public:
	Main();
	~Main();
	bool initialize( int argc , char *argv[] );
	int run();
};

template < class ApplicationPolicy , class VideoPolicy , class AudioPolicy >
Main< ApplicationPolicy, VideoPolicy, AudioPolicy >::Main()
{
}

template < class ApplicationPolicy , class VideoPolicy , class AudioPolicy >
Main< ApplicationPolicy, VideoPolicy, AudioPolicy >::~Main()
{
}

template < class ApplicationPolicy , class VideoPolicy , class AudioPolicy >
bool Main< ApplicationPolicy, VideoPolicy, AudioPolicy >::initialize( int argc , char *argv[] )
{
	application.processArgs( argc , argv );

	// _ALL_ expects these to be set
	// especially the logging and exception handling!
	Singleton<Application>::set( &application );
	Singleton<Log>::set( &application );
	Singleton<ExceptionHandler>::set( &application );
	Singleton<EventHandler>::set( &application );
	Singleton<KeyboardInputHandler>::set( &application );
	Singleton<MouseInputHandler>::set( &application );
	Singleton<JoystickInputHandler>::set( &application );

	Singleton<ThreadPool>::set( &pool );

	Singleton<Audio>::set( &audio );
	Singleton<Video>::set( &video );

	// plenty of slaves to do my bidding.
	int workers = ThreadPool::getHardwareThreadCount() * 2 + 1.0;

	return pool.initialize( workers ) && application.initialize() && audio.initialize() && video.initialize();
}

template < class ApplicationPolicy , class VideoPolicy , class AudioPolicy >
int Main< ApplicationPolicy, VideoPolicy, AudioPolicy >::run()
{
	bool restart;

	do
	{
		do
		{
			try
			{
				application.run();
			}
			catch( std::exception& e ) {
				application.handleException( e );
			}
		}
		while( application.willContinue() );

		if( application.willSaveState() )
		{
			application.saveState();
		}

		if( (restart = application.willRestart()) )
		{
			 application.restart();
		}
	}
	while( restart );

	return application.getProgramExitState();
}

} /* namespace bolt */
#endif /* MAIN_HPP_ */
