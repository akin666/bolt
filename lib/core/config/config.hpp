/*
 * cfgparser.h
 *
 *  Created on: 14.5.2009
 *      Author: akin
 */

#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <string>

namespace bolt
{
	class Config
	{
	public:
		Config();
		virtual ~Config();

		virtual void set( std::string key , std::string value );
		virtual void remove( std::string key );
		virtual bool isSet( std::string key );

		virtual float get( std::string key , float def );
		virtual bool get( std::string key , bool def );
		virtual int get( std::string key , int def );
		virtual std::string get( std::string key , std::string def );
	};
}

#endif /* ICE_CONFIG_H_ */
