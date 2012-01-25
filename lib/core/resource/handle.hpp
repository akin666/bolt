
#ifndef HANDLE_HPP_
#define HANDLE_HPP_

/*
usage (most likely):

MeshAnimation *currentMuumi = bolt::Singleton<Handle<MeshAnimation> >::get()->objectFor( "Muumi" );

*/

#include <common>
#include <map>
#include <string>
#include <iterator>
#include "dictionary.hpp"
#include <singleton>

namespace bolt
{
namespace resource
{

template <class HType>
class Handle
{
protected:
	typedef std::map<uint, HType*> KeyTypeMap;

	KeyTypeMap handles;
public:
	Handle( HType *nullObject = NULL )
	{
		handles[ Dictionary::nullId ] = nullObject;
	}
	
	HType *objectFor( uint key )
	{
		KeyTypeMap::iterator iter = handles.find( key );
		if( iter == handles.end() )
		{
			return handles[ Dictionary::nullId ];
		}
		return iter->second;
	}
	
	HType *objectFor( std::string alias )
	{
		uint key = Singleton<Dictionary>::get()->resolveKey( alias );

		return objectFor( key );
	}
};

} // namespace resource
} // namespace bolt

#endif

