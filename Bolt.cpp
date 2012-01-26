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

#include "game/testapplication.hpp"

int main( int argc , char *argv[] )
{
	bolt::Main< TestApplication ,
				bolt::GLFWVideo ,
				bolt::OpenALAudio ,
				bolt::Log ,
				bolt::resource::DefaultLoader ,
				bolt::resource::DefaultDictionary > entity;

	entity.initialize( argc , argv );

	return entity.run();
}
