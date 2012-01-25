/*
 * loader.cpp
 *
 *  Created on: 26.1.2012
 *      Author: akin
 */

#include "loader.hpp"
#include <singleton>
#include "dictionary.hpp"

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

bool Loader::loadPath( const std::string& path )
{
	// Now.. figure out wtf is this.
	// And put it to load, with workers.
	return false;
}


bool Loader::load( std::string alias , std::string path )
{
	Singleton<Dictionary>::get()->add( alias , path );

	return loadPath( path );
}

bool Loader::load( std::string alias )
{
	std::string path = Singleton<Dictionary>::get()->resolvePath( alias );

	if( path == Dictionary::nullString )
	{
		return false;
	}

	return loadPath( path );
}

} // namespace resource
} // namespace bolt
