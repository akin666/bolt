/*
 * dictionary.hpp
 *
 *  Created on: 26.1.2012
 *      Author: akin
 */

#ifndef DICTIONARY_HPP_
#define DICTIONARY_HPP_

#include <common>
#include <map>
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
protected:

	typedef std::map<std::string,std::string> StringStringMap;
	typedef std::map<std::string,uint> StringKeyMap;
	typedef std::map<uint,std::string> KeyStringMap;

	uint currentId;

	StringStringMap aliasPathMap;
	StringKeyMap aliasKeyMap;
	KeyStringMap keyAliasMap;

	uint newId();
public:
	Dictionary();
	virtual ~Dictionary();

	std::string resolvePath( std::string alias );
	std::string resolvePath( uint key );
	uint 		resolveKey( std::string alias );
	std::string resolveAlias( uint key );

	bool add( std::string alias , std::string path );
};

} // namespace resource
} // namespace bolt
#endif /* DICTIONARY_HPP_ */
