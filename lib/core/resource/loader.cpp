/*
 * loader.cpp
 *
 *  Created on: 26.1.2012
 *      Author: akin
 */

#include "loader.hpp"
#include <singleton>

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

bool Loader::load( std::string alias , std::string path )
{
	return false;
}

bool Loader::load( std::string alias )
{
	return false;
}

bool load( std::string alias , std::string path )
{
	return bolt::getSingleton<bolt::resource::Loader>()->load( alias , path );
}

bool load( std::string alias )
{
	return bolt::getSingleton<bolt::resource::Loader>()->load( alias );
}

} // namespace resource
} // namespace bolt
