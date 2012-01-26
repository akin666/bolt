/*
 * defaultloader.cpp
 *
 *  Created on: 26.1.2012
 *      Author: akin
 */

#include "defaultloader.hpp"

#include <singleton>
#include <resource/dictionary.hpp>
#include <threadpool>

#include <group>
#include <resource/handler.hpp>
#include <resource/handler/texthandler.hpp>

namespace bolt
{
namespace resource
{

DefaultLoader::DefaultLoader()
{
	Group<Handler>::add( new TextHandler() );
}

DefaultLoader::~DefaultLoader()
{
}

bool DefaultLoader::loadPath( const std::string& alias , const std::string& path )
{
	// Now.. figure out wtf is this.
	// And put it to load, with workers.
	Work *work = NULL;

	size_t dotPos = path.find_last_of( '.' );

	// unknown format, no '.'
	if( dotPos == std::string::npos )
	{
		return false;
	}

	std::string type = path.substr( dotPos );

	// Seek a handler, that can create work package for the file.
	for( Group<Handler>::GroupList::iterator iter = Group<Handler>::begin() ; iter != Group<Handler>::end() ; ++iter )
	{
		if( (*iter)->canHandle( type ) )
		{
			work = (*iter)->handle( alias , path );
		}
	}

	if( work != NULL )
	{
		composite.push( work );

		if( !composite.isRunning() )
		{
			bolt::Singleton<bolt::ThreadPool>::get()->schedule( &composite );
		}
	}

	return work != NULL;
}


bool DefaultLoader::load( std::string alias , std::string path )
{
	Singleton<Dictionary>::get()->add( alias , path );

	return loadPath( alias , path );
}

bool DefaultLoader::load( std::string alias )
{
	std::string path = Singleton<Dictionary>::get()->resolvePath( alias );

	if( path == Dictionary::nullString )
	{
		return false;
	}

	return loadPath( alias , path );
}

}
} /* namespace bolt */
