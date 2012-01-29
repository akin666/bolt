
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
#include <exception>
#include <stdexcept>

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
	
	HType *getObject( uint key ) throw (std::exception)
	{
		std::lock_guard<std::mutex> lock(mutex);

		typename KeyTypeMap::iterator iter = handles.find( key );
		if( iter == handles.end() )
		{
			// Null Object pattern!
			iter = handles.find( Dictionary::nullId );
			if( iter == handles.end() )
			{
				throw std::runtime_error("No null object set for type!.");
			}
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

	void setObject( uint key , HType *object )
	{
		std::lock_guard<std::mutex> lock(mutex);

		handles[ key ] = object;
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
	HType *getObject( std::string alias ) throw (std::exception)
	{
		uint key = getSingleton<Dictionary>()->resolveKey( alias );
		return getObject( key );
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

	void setObjectFor( std::string alias , HType *object )
	{
		uint key = getSingleton<Dictionary>()->resolveKey( alias );
		setObject( key , object );
	}

	HType *resetObject( std::string alias )
	{
		uint key = getSingleton<Dictionary>()->resolveKey( alias );
		return resetObject( key );
	}
};

// Sugar coating.
template <class CType>
void setObject( std::string alias , CType *object )
{
	getSingleton<Registry<CType> >()->setObjectFor( alias , object );
}
template <class CType>
void setObject( uint key , CType *object )
{
	getSingleton<Registry<CType> >()->setObject( key , object );
}
template <class CType>
CType *getObject( std::string alias ) throw (std::exception)
{
	return getSingleton<Registry<CType> >()->getObject( alias );
}
template <class CType>
CType *getObject( uint key ) throw (std::exception)
{
	return getSingleton<Registry<CType> >()->objectFor( key );
}
template <class CType>
bool hasObject( std::string alias )
{
	return getSingleton<Registry<CType> >()->hasObject( alias );
}
template <class CType>
bool hasObject( uint key )
{
	return getSingleton<Registry<CType> >()->hasObject( key );
}
template <class CType>
CType *resetObject( std::string alias )
{
	return getSingleton<Registry<CType> >()->resetObject( alias );
}
template <class CType>
CType *resetObject( uint key )
{
	return getSingleton<Registry<CType> >()->resetObject( key );
}

} // namespace resource
} // namespace bolt

#endif

