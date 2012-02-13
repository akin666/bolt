/*
 * property.h
 *
 *  Created on: 14.10.2011
 *      Author: akin
 *
 *		Property is like the Model from ModelViewController pattern.
 *      Property adds some properties to the entity, once attached, the entity
 *      has as set of data, bound to it, inside the Property..
 *      The arrangement of the data is recommended (for now) to be in array/vector structure,
 *      so that the whatever modifies the data, has access, in a cache friendly way.
 *      The Entity is/should be, totally oblivious to the fact, that it has some data structures attached to it.
 *
 *      Calling attach, multiple times should be allowed, BUT the dataset is only created upon first attach.
 *      Calling detach, should perform detach operation, no matter how many times attach has been called. Detach
 *      should be considered to be operation, that is called upon entity destruction.
 *      Detach can be called multiple times, ultimately whether the property uses reference counting with attach/detach
 *      is the designers decision.
 */

#ifndef COMPONENT_PROPERTY_HPP_
#define COMPONENT_PROPERTY_HPP_

#include <exception>
#include <string>
#include <common>
#include <entity.hpp>

namespace bolt
{
	class Property
	{
	protected:
		static uint sm_id;
		static uint getNewId();

		uint id;
		std::string name;
	public:
		Property( std::string name );
		virtual ~Property();

		virtual void initialize() throw (std::exception);

		std::string getName() const;
		uint getId() const;

		virtual void attach( Entity& entity ) = 0;
		virtual void detach( Entity& entity ) = 0;
	};
} /* namespace bolt */
#endif /* COMPONENT_PROPERTY_HPP_ */
