/*
 * positionproperty.hpp
 *
 *  Created on: 20.1.2012
 *      Author: akin
 */

#ifndef POSITIONPROPERTY_HPP_
#define POSITIONPROPERTY_HPP_

#include <component/property.hpp>
#include <map>
#include <generic/position.hpp>

namespace bolt
{
class PositionProperty: public bolt::Property
{
public:
	const static std::string KEY;
protected:
	typedef std::map< uint , Position > PositionMap;

	PositionMap data;
public:
	PositionProperty();
	virtual ~PositionProperty();

	virtual void initialize() throw (std::exception);

	virtual void attach( bolt::Entity& entity );
	virtual void detach( bolt::Entity& entity );

	Position& get( bolt::uint entity );
};
}

#endif /* POSITIONPROPERTY_HPP_ */


