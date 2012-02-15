/*
 * fileconfig.hpp
 *
 *  Created on: 30.1.2012
 *      Author: akin
 */

#ifndef FILECONFIG_HPP_
#define FILECONFIG_HPP_

#include "config.hpp"

#include <map>

namespace bolt
{

class FileConfig : public Config
{
protected:
	std::map< std::string , std::string > pairs;

	std::string get( const std::string& key );
public:
	FileConfig();
	FileConfig( std::string path );
	virtual ~FileConfig();

	void load( std::string path );
	void save( std::string path );

	virtual void set( std::string key , std::string value );
	virtual void remove( std::string key );
	virtual bool isSet( std::string key );

	virtual float get( std::string key , float def );
	virtual bool get( std::string key , bool def );
	virtual int get( std::string key , int def );
	virtual std::string get( std::string key , std::string def );
};

} /* namespace bolt */
#endif /* FILECONFIG_HPP_ */
