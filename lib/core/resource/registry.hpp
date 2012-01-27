
#ifndef REGISTRY_HPP_
#define REGISTRY_HPP_

/*
usage (most likely):

MeshAnimation *currentMuumi = getSingleton<Handle<MeshAnimation> >()->objectFor( "Muumi" );

*/

#include <common>
#include <map>
#include <string>
#include <iterator>
#include "dictionary.hpp"
#include <singleton>
#include <thread>

namespace bolt
{
namespace resource
{

template <class HType>
class Registry
{
protected:
	std::mutex mutex;
	typedef std::map<uint, HType*> KeyTypeMap;

	KeyTypeMap handles;
public:
	Registry( HType *nullObject = NULL )
	{
		std::lock_guard<std::mutex> lock(mutex);
		if( nullObject != NULL )
		{
			handles[ Dictionary::nullId ] = nullObject;
		}
	}
	
	HType *objectFor( uint key )
	{
		std::lock_guard<std::mutex> lock(mutex);
		typename KeyTypeMap::iterator iter = handles.find( key );
		if( iter == handles.end() )
		{
			return handles[ Dictionary::nullId ];
		}
		return iter->second;
	}

	bool hasObject( uint key )
	{
		std::lock_guard<std::mutex> lock(mutex);
		typename KeyTypeMap::iterator iter = handles.find( key );
		return iter != handles.end();
	}

	bool setObject( uint key , HType *object )
	{
		std::lock_guard<std::mutex> lock(mutex);

		typename KeyTypeMap::iterator iter = handles.find( key );
		if( iter != handles.end() )
		{
			// already set!
			return false;
		}

		handles[ key ] = object;

		return true;
	}

	HType *resetObject( uint key )
	{
		std::lock_guard<std::mutex> lock(mutex);

		HType *tmp = NULL;
		typename KeyTypeMap::iterator iter = handles.find( key );
		if( iter != handles.end() )
		{
			tmp = iter->second;
			handles.erase( iter );
		}

		return tmp;
	}


	// Convenience functions.
	HType *objectFor( std::string alias )
	{
		uint key = getSingleton<Dictionary>()->resolveKey( alias );
		return objectFor( key );
	}

	bool hasObject( std::string alias )
	{
		uint key = getSingleton<Dictionary>()->resolveKey( alias );
		if( key == Dictionary::nullId )
		{
			return false;
		}
		return hasObject( key );
	}
};

} // namespace resource
} // namespace bolt

#endif

