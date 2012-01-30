/*
 * Config.cpp
 *
 *  Created on: 1.8.2008
 *      Author: akin
 */

#include "config.hpp"

namespace bolt
{
Config::Config()
{
}

Config::~Config()
{
}

void Config::set( std::string key , std::string value )
{
}

void Config::remove( std::string key )
{
}

bool Config::isSet( std::string key )
{
	return false;
}

float Config::get( std::string key , float def )
{
	return def;
}

bool Config::get( std::string key , bool def )
{
	return def;
}

int Config::get( std::string key , int def )
{
	return def;
}

std::string Config::get( std::string key , std::string def )
{
	return def;
}

}
