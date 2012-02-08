//============================================================================
// Name        : Bolt.cpp
// Author      : Mikael Korpela
// Version     :
// Copyright   : C
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <system/main.hpp>
#include <application/application.hpp>
#include <system/audio/openalaudio.hpp>
#include <system/video/glfwvideo.hpp>
#include <resource/default/defaultloader.hpp>
#include <resource/default/defaultdictionary.hpp>
#include <log.hpp>

#include "game/testapp/testapplication.hpp"

int main( int argc , char *argv[] )
{
	bolt::Main< TestApplication ,
				bolt::GLFWVideo ,
				bolt::OpenALAudio ,
				bolt::Log ,
				bolt::resource::DefaultLoader ,
				bolt::resource::DefaultDictionary > entity;

	// Application Exception handling not running yet..
	try
	{
		entity.initialize( argc , argv );
	}
	catch( std::exception& e )
	{
		std::cerr << "Failed to initialize application: " << e.what() << std::endl;
		return -1;
	}

	return entity.run();
}
