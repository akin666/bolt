/*
 * resourceloader.cpp
 *
 *  Created on: 22.1.2012
 *      Author: akin
 */

#include "resourceloader.hpp"
#include <iterator>


namespace bolt
{

ResourceLoader::ResourceLoader()
{
}

ResourceLoader::~ResourceLoader()
{
}

bool ResourceLoader::addAlias( std::string name , std::string path )
{
	// Alias and path point to same thing.
	namePathMap[name] = path;
	namePathMap[path] = path;

	return true;
}

ResourceUnit *ResourceLoader::newResourceUnit( std::string path )
{
	if( path == "" )
	{
		return NULL;
	}

	return NULL;
}

ResourceUnit *ResourceLoader::getResourceUnit( const std::string& alias )
{
	// critical area. lock down.
	std::lock_guard<std::mutex> lock( mutex );
	StringUnitMap::iterator iter = nameUnitMap.find( alias );
	if( iter == nameUnitMap.end() )
	{
		// Not loaded!
		// try loading!
		StringStringMap::iterator aliasIter = namePathMap.find( alias );
		std::string path;

		// If alias is really an alias, translate it to path.
		if( aliasIter != namePathMap.end() )
		{
			path = aliasIter->second;
		}
		else
		{
			path = alias;
		}

		// Check if the resolved path is loaded already
		StringUnitMap::iterator unitIter = nameUnitMap.find( path );
		if( unitIter != nameUnitMap.end() )
		{
			// it is really loaded with different name, correct the state & return.
			nameUnitMap[ alias ] = unitIter->second;
			return unitIter->second;
		}

		// Load the resource.
		ResourceUnit *unit = newResourceUnit( path );
		if( unit == NULL )
		{
			return NULL;
		}

		nameUnitMap[ path ] = unit;
		if( path != alias )
		{
			nameUnitMap[ alias ] = unit;
		}
		return unit;
	}

	return iter->second;
}

} /* namespace bolt */

