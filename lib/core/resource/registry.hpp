
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
#include <merge>

namespace bolt
{
namespace resource
{

template <class HType>
class Registry
{
public:
	static const uint EMPTY = 			0x0000;
	static const uint LOADING = 		0x0001;
	static const uint LOADED = 			0x0002;
	static const uint ERROR = 			0x0004;
	static const uint FILE_ERROR =		0x0008;
	static const uint EXCEPTION =		0x0010;
protected:
	typedef std::map<uint, HType*> KeyTypeMap;
	typedef std::map<uint, uint> KeyStatusMap;

	Merge< std::mutex , KeyTypeMap > handles;
	Merge< std::mutex , KeyStatusMap > states;
public:
	Registry( HType *nullObject = NULL )
	{
		std::lock_guard<std::mutex> lock(handles);
		std::lock_guard<std::mutex> lock2(states);

		if( nullObject != NULL )
		{
			handles[ Dictionary::nullId ] = nullObject;
			states[ Dictionary::nullId ] = LOADED;
		}
	}
	
	HType *getObject( uint key ) throw (std::exception)
	{
		std::lock_guard<std::mutex> lock(handles);

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
		std::lock_guard<std::mutex> lock(handles);

		typename KeyTypeMap::iterator iter = handles.find( key );
		return iter != handles.end();
	}

	void setObject( uint key , HType *object )
	{
		std::lock_guard<std::mutex> lock(handles);

		handles[ key ] = object;
	}

	HType *resetObject( uint key )
	{
		std::lock_guard<std::mutex> lock(handles);
		std::lock_guard<std::mutex> lock2(states);

		HType *tmp = NULL;
		typename KeyTypeMap::iterator hiter = handles.find( key );
		if( hiter != handles.end() )
		{
			tmp = hiter->second;
			handles.erase( hiter );
		}
		typename KeyStatusMap::iterator siter = states.find( key );
		if( siter != states.end() )
		{
			states.erase( siter );
		}

		return tmp;
	}

	void setObjectState(  uint key , uint state )
	{
		std::lock_guard<std::mutex> lock(states);

		states[ key ] = state;
	}

	uint getObjectState(  uint key )
	{
		std::lock_guard<std::mutex> lock(states);

		typename KeyStatusMap::iterator siter = states.find( key );
		if( siter != states.end() )
		{
			return siter->second;
		}

		return EMPTY;
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

	void setObjectStateFor( std::string alias , uint state )
	{
		uint key = getSingleton<Dictionary>()->resolveKey( alias );
		setObjectState( key , state );
	}

	uint getObjectStateFor( std::string alias )
	{
		uint key = getSingleton<Dictionary>()->resolveKey( alias );
		return getObjectState( key );
	}
};

// Sugar coating.
template <class CType>
void setObject( std::string alias , CType *object ) throw (std::exception)
{
	getSingleton<Registry<CType> >()->setObjectFor( alias , object );
}
template <class CType>
void setObject( uint key , CType *object ) throw (std::exception)
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
bool hasObject( std::string alias ) throw (std::exception)
{
	return getSingleton<Registry<CType> >()->hasObject( alias );
}
template <class CType>
bool hasObject( uint key ) throw (std::exception)
{
	return getSingleton<Registry<CType> >()->hasObject( key );
}
template <class CType>
CType *resetObject( std::string alias ) throw (std::exception)
{
	return getSingleton<Registry<CType> >()->resetObject( alias );
}
template <class CType>
CType *resetObject( uint key ) throw (std::exception)
{
	return getSingleton<Registry<CType> >()->resetObject( key );
}

} // namespace resource
} // namespace bolt

#endif

