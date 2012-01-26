/*
 * defaultloader.cpp
 *
 *  Created on: 26.1.2012
 *      Author: akin
 */

#include "defaultloader.hpp"

#include <singleton>
#include <resource/dictionary.hpp>
#include <resource/loaders/bytedatawork.hpp>
#include <threadpool>

namespace bolt
{
namespace resource
{

DefaultLoader::DefaultLoader()
{
}

DefaultLoader::~DefaultLoader()
{
}

bool DefaultLoader::loadPath( const std::string& alias , const std::string& path )
{
	// Now.. figure out wtf is this.
	// And put it to load, with workers.
	Work *work = NULL;

	// TODO! GLSL Shader loaders, and other dirty specializations.
	// based on the last .XXX letters.

	work = new ByteDataWork( alias , path );
	/*
	switch( ".XXX" )
	{
		case ".txt" : work = new TextDataWork( alias , path ); break;
		case ".fs" : work = new FragmentShaderDataWork( alias , path ); break;
		case ".vs" : work = new VertexShaderDataWork( alias , path ); break;
		case ".xml" : work = new XMLDataWork( alias , path ); break;
		default: work = new ByteDataWork( alias , path ); break;
	}
	*/

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
