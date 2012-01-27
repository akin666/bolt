/*
 * defaultdictionary.hpp
 *
 *  Created on: 26.1.2012
 *      Author: akin
 */

#ifndef DEFAULTDICTIONARY_HPP_
#define DEFAULTDICTIONARY_HPP_

#include <resource/dictionary.hpp>
#include <map>

namespace bolt
{
namespace resource
{

class DefaultDictionary : public Dictionary
{
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
	DefaultDictionary();
	virtual ~DefaultDictionary();

	virtual std::string resolvePath( std::string alias );
	virtual std::string resolvePath( uint key );
	virtual uint 		resolveKey( std::string alias );
	virtual std::string resolveAlias( uint key );

	// Pure aliases.
	virtual bool add( std::string alias );
	// Path aliases.
	virtual bool add( std::string alias , std::string path );
};

}
} /* namespace bolt */
#endif /* DEFAULTDICTIONARY_HPP_ */
