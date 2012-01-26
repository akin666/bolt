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
{
}

Dictionary::~Dictionary()
{
}

std::string Dictionary::resolvePath( std::string alias )
{
	return nullString;
}

std::string Dictionary::resolvePath( uint key )
{
	return nullString;
}

uint Dictionary::resolveKey( std::string alias )
{
	return nullId;
}

std::string Dictionary::resolveAlias( uint key )
{
	return nullString;
}

bool Dictionary::add( std::string alias , std::string path )
{
	return false;
}

} // namespace resource
} // namespace bolt
