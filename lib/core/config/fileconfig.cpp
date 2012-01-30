/*
 * fileconfig.cpp
 *
 *  Created on: 30.1.2012
 *      Author: akin
 */

#include "fileconfig.hpp"
#include <iterator>
#include <fstream>
#include <sstream>
#include <string>
#include <stringtools>

namespace bolt
{

FileConfig::FileConfig()
{
}

FileConfig::FileConfig( std::string path )
{
	load( path );
}

FileConfig::~FileConfig()
{
}

bool FileConfig::isSet( std::string key )
{
	return ( pairs.find( key ) != pairs.end() );
}

void FileConfig::set( std::string key , std::string value )
{
	pairs[key] = value;
}

void FileConfig::remove( std::string key )
{
	pairs.erase( key );
}

std::string FileConfig::get( const std::string& key )
{
	if( isSet(key) ){
		return pairs[key];
	}
	return "";
}

std::string FileConfig::get( std::string key , std::string def )
{
	if( isSet(key) )
	{
		return pairs[key];
	}
	else
	{
		pairs[key] = def;
	}
	return def;
}

float FileConfig::get( std::string key , float def )
{
	 if( isSet(key) )
	 {
		float tt;

		if( stringtools::from_string<float>(tt, pairs[key] , std::dec))
		{
			return tt;
		}
	}
	else
	{
		pairs[key] = stringtools::to_ot< std::string , float >( def );
	}
	return def;
}

bool FileConfig::get( std::string key , const bool def )
{
	if( isSet(key) )
	{
		if( pairs[key].compare("true") == 0 )
		{
			return true;
		}
		return false;
	}
	else
	{
		pairs[key] = ( def ? "true" : "false" );
	}
	return def;
}

int FileConfig::get( std::string key , int def )
{
	if( isSet(key) )
	{
		int tt;
		if(stringtools::from_string<int>(tt, pairs[key] , std::dec))
		{
			return tt;
		}
	}
	else
	{
		pairs[key] = stringtools::to_ot< std::string , int >( def );
	}
	return def;
}

void FileConfig::load( std::string path ) throw (std::exception)
{
	/*
	 * Load infested configuration that can contain comments etc. extra.
	 *  // [whitespaces,tabs,nothing]#comment
	 *	// [whitespaces,tabs,nothing]key[whitespaces,tabs,spaces]value
	 *	// [empty line]
	 *	//
	 *	// it is illegal to make:
	 *	// key value #comment
	 */

	try
	{
		std::string line;
		int first = 0;
		int second = 0;
		int third = 0;
		int fourth = 0;

		dio.lock();
		while( !dio.empty() )
		{
			dio.readLine(line);
			// Hack to handle CRLF lines.
			if(line.size() > 0 && line[line.size()-1] == '\r')
			{
				line = line.substr(0, line.size()-1);
			}

			// Skip the line if it contains less than 3 values,
			// the smallest possible key-value pair is 'a b'
			if( line.size() < 3 ){
				continue;
			}
			// first not space or tab.
			first = line.find_first_not_of(" \t");

			// Skip comment line
			if( line.at(first) == '#' ){
				continue;
			}

			second = line.find_first_of(" \t" , first );
			third = line.find_first_not_of(" \t" , second );
			fourth = line.find_last_not_of(" \t" , third-1 );

			pairs[line.substr( first , (second-first))] = line.substr( third , (fourth-third));
		}
		dio.unlock();
	}
	catch( ... )
	{
		return false;
	}

	return true;
}

void FileConfig::save( std::string path ) throw (std::exception)
{
	/*
	 * Save to pure configuration, no comments etc.
	 */
	try
	{
		std::ofstream outFile;
		outFile.open ( path.c_str() );
		// unable to open
		if (!outFile) {
			outFile.close();
			return false;
		}

		std::map<std::string,std::string>::iterator iter;
		for( iter = pairs.begin(); iter != pairs.end(); iter++ ) {
			outFile << iter->first << " " << iter->second << std::endl;
		}

		outFile.close();
	}
	catch( ... )
	{
		return false;
	}

	return true;
}

} /* namespace bolt */
