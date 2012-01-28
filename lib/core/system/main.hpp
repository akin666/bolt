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

#include <exception>
#include <singleton>
#include <application/application.hpp>
#include "audio.hpp"
#include "video.hpp"

#include <log.hpp>
#include <event/eventhandler.hpp>
#include <exception/exceptionhandler.hpp>
#include <threadpool>

#include <resource/loader.hpp>
#include <resource/dictionary.hpp>

namespace bolt
{

template < class ApplicationPolicy , class VideoPolicy , class AudioPolicy , class LogPolicy , class ResourceLoader , class ResourceDictionary >
class Main
{
protected:
	ApplicationPolicy application;
	VideoPolicy video;
	AudioPolicy audio;
	LogPolicy log;
	ResourceLoader loader;
	ResourceDictionary dictionary;
	ThreadPool pool;
public:
	Main();
	~Main();
	void initialize( int argc , char *argv[] ) throw (std::exception);
	int run();
};

template < class ApplicationPolicy , class VideoPolicy , class AudioPolicy , class LogPolicy , class ResourceLoader , class ResourceDictionary >
Main< ApplicationPolicy, VideoPolicy, AudioPolicy , LogPolicy , ResourceLoader , ResourceDictionary >::Main()
{
}

template < class ApplicationPolicy , class VideoPolicy , class AudioPolicy , class LogPolicy , class ResourceLoader , class ResourceDictionary >
Main< ApplicationPolicy, VideoPolicy, AudioPolicy , LogPolicy , ResourceLoader , ResourceDictionary >::~Main()
{
}

template < class ApplicationPolicy , class VideoPolicy , class AudioPolicy , class LogPolicy , class ResourceLoader , class ResourceDictionary >
void Main< ApplicationPolicy, VideoPolicy, AudioPolicy , LogPolicy , ResourceLoader , ResourceDictionary >::initialize( int argc , char *argv[] ) throw (std::exception)
{
	application.processArgs( argc , argv );

	// _ALL_ expects these to be set
	// especially the logging and exception handling!
	setSingleton<Application>( &application );
	setSingleton<Log>( &log );
	setSingleton<ExceptionHandler>( &application );
	setSingleton<EventHandler>( &application );

	setSingleton<ThreadPool>( &pool );

	setSingleton<Audio>( &audio );
	setSingleton<Video>( &video );

	setSingleton<resource::Loader>( &loader );
	setSingleton<resource::Dictionary>( &dictionary );

	// plenty of slaves to do my bidding.
	int workers = ThreadPool::getHardwareThreadCount() * 2 + 1.0;

	pool.initialize( workers );
	application.initialize();
	audio.initialize();
	video.initialize();
}

template < class ApplicationPolicy , class VideoPolicy , class AudioPolicy , class LogPolicy , class ResourceLoader , class ResourceDictionary >
int Main< ApplicationPolicy, VideoPolicy, AudioPolicy , LogPolicy , ResourceLoader , ResourceDictionary >::run()
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
