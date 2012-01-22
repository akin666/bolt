/*
 * resourceloader.hpp
 *
 *  Created on: 22.1.2012
 *      Author: akin
 */

#ifndef RESOURCELOADER_HPP_
#define RESOURCELOADER_HPP_

#include <string>
#include <map>
#include <thread>
#include "resourceunit.hpp"

namespace bolt
{

class ResourceLoader
{
protected:
	std::mutex mutex;
	typedef std::map< std::string , std::string > StringStringMap;
	StringStringMap namePathMap;
	typedef std::map< std::string , ResourceUnit* > StringUnitMap;
	StringUnitMap nameUnitMap;

	virtual ResourceUnit *newResourceUnit( std::string path );
	ResourceUnit *getResourceUnit( const std::string& alias );
public:
	ResourceLoader();
	virtual ~ResourceLoader();

	bool addAlias( std::string name , std::string path );

	template <class resourceUnitType>
	resourceUnitType *get( std::string alias )
	{
		return dynamic_cast<resourceUnitType*>( getResourceUnit( alias ) );
	}
};

} /* namespace bolt */
#endif /* RESOURCELOADER_HPP_ */
