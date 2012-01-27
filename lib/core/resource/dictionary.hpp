/*
 * dictionary.hpp
 *
 *  Created on: 26.1.2012
 *      Author: akin
 *
 *      Service to create unique ID's to aliases.
 *      Service also includes the service to keep alias-paths.
 */

#ifndef DICTIONARY_HPP_
#define DICTIONARY_HPP_

#include <common>
#include <string>

namespace bolt
{
namespace resource
{

class Dictionary
{
public:
	static const uint nullId;
	static const std::string nullString;
public:
	Dictionary();
	virtual ~Dictionary();

	virtual std::string resolvePath( std::string alias );
	virtual std::string resolvePath( uint key );
	virtual uint 		resolveKey( std::string alias );
	virtual std::string resolveAlias( uint key );

	// Pure runtime key aliases.
	virtual bool add( std::string alias );

	// Path aliases.
	virtual bool add( std::string alias , std::string path );
};

// sugar coating:
bool link( std::string alias );
bool link( std::string alias , std::string path );

} // namespace resource
} // namespace bolt
#endif /* DICTIONARY_HPP_ */
