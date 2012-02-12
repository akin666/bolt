/*
 * property.h
 *
 *  Created on: 14.10.2011
 *      Author: akin
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
