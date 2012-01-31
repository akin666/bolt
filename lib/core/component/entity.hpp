/*
 * entity.hpp
 *
 *  Created on: 16.1.2012
 *      Author: akin
 */

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <common>

namespace bolt
{
	class Entity
	{
	protected:
		static uint mId;
		static uint createId();

		uint id;
	public:
		Entity();
		Entity( const Entity& other );

		uint getId();
		operator uint();
		Entity& operator =( const Entity& other );
	};
}

#endif /* ENTITY_HPP_ */
