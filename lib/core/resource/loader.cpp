/*
 * loader.cpp
 *
 *  Created on: 26.1.2012
 *      Author: akin
 */

#include "loader.hpp"
#include <singleton>
#include "dictionary.hpp"
#include "loaders/bytedatawork.hpp"
#include <threadpool>

namespace bolt
{
namespace resource
{

Loader::Loader()
{
}

Loader::~Loader()
{
}

bool Loader::loadPath( const std::string& alias , const std::string& path )
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
		bolt::Singleton<bolt::ThreadPool>::get()->schedule( work );
	}

	return work != NULL;
}


bool Loader::load( std::string alias , std::string path )
{
	Singleton<Dictionary>::get()->add( alias , path );

	return loadPath( alias , path );
}

bool Loader::load( std::string alias )
{
	std::string path = Singleton<Dictionary>::get()->resolvePath( alias );

	if( path == Dictionary::nullString )
	{
		return false;
	}

	return loadPath( alias , path );
}

} // namespace resource
} // namespace bolt
