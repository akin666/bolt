/*
 * defaultdictionary.cpp
 *
 *  Created on: 26.1.2012
 *      Author: akin
 */

#include "defaultdictionary.hpp"

namespace bolt
{
namespace resource
{

DefaultDictionary::DefaultDictionary()
: currentId( nullId + 1 )
{
}

DefaultDictionary::~DefaultDictionary()
{
}

uint DefaultDictionary::newId()
{
	return currentId++;
}

std::string DefaultDictionary::resolvePath( std::string alias )
{
	StringStringMap::iterator iter = aliasPathMap.find( alias );

	if( iter == aliasPathMap.end() )
	{
		return nullString;
	}

	return iter->second;
}

std::string DefaultDictionary::resolvePath( uint key )
{
	std::string alias = resolveAlias( key );

	if( alias == nullString )
	{
		return nullString;
	}

	return resolvePath( alias );
}

uint DefaultDictionary::resolveKey( std::string alias )
{
	StringKeyMap::iterator iter = aliasKeyMap.find( alias );

	if( iter == aliasKeyMap.end() )
	{
		return nullId;
	}

	return iter->second;
}

std::string DefaultDictionary::resolveAlias( uint key )
{
	KeyStringMap::iterator iter = keyAliasMap.find( key );

	// duplicate data. update & return
	if( iter == keyAliasMap.end() )
	{
		return nullString;
	}
	return iter->second;
}

bool DefaultDictionary::add( std::string alias )
{
	// just short circuit the alias path..
	// we do not loose much, by doing this.
	return add( alias , alias );
}

bool DefaultDictionary::add( std::string alias , std::string path )
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

}
} /* namespace bolt */
