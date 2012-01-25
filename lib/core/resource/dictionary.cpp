/*
 * dictionary.cpp
 *
 *  Created on: 26.1.2012
 *      Author: akin
 */

#include "dictionary.hpp"

namespace bolt
{
namespace resource
{

const uint Dictionary::nullId = 0;
const std::string Dictionary::nullString("");

Dictionary::Dictionary()
: currentId( nullId + 1 )
{
}

Dictionary::~Dictionary()
{
}

uint Dictionary::newId()
{
	return currentId++;
}

std::string Dictionary::resolvePath( std::string alias )
{
	StringStringMap::iterator iter = aliasPathMap.find( alias );

	if( iter == aliasPathMap.end() )
	{
		return nullString;
	}

	return iter->second;
}

std::string Dictionary::resolvePath( uint key )
{
	std::string alias = resolveAlias( key );

	if( alias == nullString )
	{
		return nullString;
	}

	return resolvePath( alias );
}

uint Dictionary::resolveKey( std::string alias )
{
	StringKeyMap::iterator iter = aliasKeyMap.find( alias );

	if( iter == aliasKeyMap.end() )
	{
		return nullId;
	}

	return iter->second;
}

std::string Dictionary::resolveAlias( uint key )
{
	KeyStringMap::iterator iter = keyAliasMap.find( key );

	// duplicate data. update & return
	if( iter == keyAliasMap.end() )
	{
		return nullString;
	}
	return iter->second;
}

bool Dictionary::add( std::string alias , std::string path )
{
	StringStringMap::iterator iter = aliasPathMap.find( alias );

	// duplicate data. update & return
	if( iter != aliasPathMap.end() )
	{
		iter->second = path;
		return true;
	}

	// New Data!! ALL HAIL THE LORD
	aliasPathMap[ alias ] = path;

	uint id = newId();
	aliasKeyMap[ alias ] = id;
	keyAliasMap[ id ] = alias;

	return true;
}

} // namespace resource
} // namespace bolt
