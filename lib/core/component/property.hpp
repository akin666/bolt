/*
 * property.h
 *
 *  Created on: 14.10.2011
 *      Author: akin
 */

#ifndef COMPONENT_PROPERTY_HPP_
#define COMPONENT_PROPERTY_HPP_

#include <string>

namespace bolt
{
	class Entity;

	class Property
	{
	protected:
		static unsigned int sm_id;
		static unsigned int getNewId();

		unsigned int id;
		std::string name;
	public:
		Property( std::string name );
		virtual ~Property();

		virtual bool initialize();

		std::string getName() const;
		unsigned int getId() const;

		virtual void attach( Entity& entity ) = 0;
		virtual void detach( Entity& entity ) = 0;
	};
} /* namespace bolt */
#endif /* COMPONENT_PROPERTY_HPP_ */
