/*
 * hub.hpp
 *
 *  Created on: 11.2.2012
 *      Author: akin
 */

#ifndef HUB_HPP_
#define HUB_HPP_

#include <entity.hpp>
#include <common>
#include <string>

namespace bolt
{

class Hub
{
public:
	Hub();
	virtual ~Hub();

	// Entity e = get( "camera" );

	virtual Entity get( std::string key );
	virtual void set( std::string key , Entity entity );
};

} /* namespace bolt */
#endif /* HUB_HPP_ */
